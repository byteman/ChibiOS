/*
    ChibiOS/RT - Copyright (C) 2006,2007,2008,2009,2010,
                 2011,2012 Giovanni Di Sirio.

    This file is part of ChibiOS/RT.

    ChibiOS/RT is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 3 of the License, or
    (at your option) any later version.

    ChibiOS/RT is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "ch.h"
#include "hal.h"
#include "test.h"

#include "lwipthread.h"

#include "web/web.h"
#include "fm25l16.h"
#include "datetime.h"
#include "chprintf.h"
/*
 * Green LED blinker thread, times are in milliseconds.
 */
static WORKING_AREA(waThread1, 128);
uint8_t byte_01;
TDateTime dt;
static BaseSequentialStream *chp;
static msg_t Thread1(void *arg) {

  (void)arg;
  chRegSetThreadName("blinker");
  dt.year = 2012;
  dt.mon = 7;
  dt.day = 3;
  dt.hour= 16;
  dt.min = 9;
  dt.sec = 12;
  set_datetime(&dt);
  while (TRUE) {
    palClearPad(GPIOE, GPIOE_LED_STATUS1);
    chThdSleepMilliseconds(500);
    palSetPad(GPIOE, GPIOE_LED_STATUS1);
    chThdSleepMilliseconds(500);

	fm25l16_write_byte(1,1);
	byte_01 = fm25l16_read_byte(1);

	get_datetime(&dt);

    chprintf(chp,"%d/%d/%d %d:%d:%d\r\n",dt.year,dt.mon,dt.day,dt.hour,dt.min,dt.sec);


  }
}
#define IP_ADDR(ip,a,b,c,d) \
						 ip=((uint32_t)((d) & 0xff) << 24) | \
                         ((uint32_t)((c) & 0xff) << 16) | \
                         ((uint32_t)((b) & 0xff) << 8)  | \
                          (uint32_t)((a) & 0xff)
uint8_t mac_addr[6] = {0x0,0x11,0x22,0x33,0x44,0x55};
struct lwipthread_opts net_opts;

/*
 * Application entry point.
 */
extern int stm32_rtc_init();

int main(void) {

  /*
   * System initializations.
   * - HAL initialization, this also initializes the configured device drivers
   *   and performs the board-specific initializations.
   * - Kernel initialization, the main() function becomes a thread and the
   *   RTOS is active.
   */
  halInit();
  chSysInit();
  stm32_rtc_init();

  /*
   * Activates the serial driver 3 using the driver default configuration.
   */
  sdStart(&SD1, NULL);
  chp = (BaseSequentialStream *)&SD1;
  /*
   * Creates the blinker thread.
   */
  chThdCreateStatic(waThread1, sizeof(waThread1), NORMALPRIO, Thread1, NULL);

  /*
   * Creates the LWIP threads (it changes priority internally).
   */
  net_opts.macaddress = mac_addr;

  IP_ADDR(net_opts.address,192,168,50,222);
  IP_ADDR(net_opts.netmask,255,255,255,0);
  IP_ADDR(net_opts.gateway,192,168,50,1);

  chThdCreateStatic(wa_lwip_thread, LWIP_THREAD_STACK_SIZE, NORMALPRIO + 1,
                    lwip_thread, &net_opts);

  /*
   * Creates the HTTP thread (it changes priority internally).
   */
  chThdCreateStatic(wa_http_server, sizeof(wa_http_server), NORMALPRIO + 1,
                    http_server, NULL);

  /*
   * Normal main() thread activity, in this demo it does nothing except
   * sleeping in a loop and check the button state.
   */
  while (TRUE) {
    if (palReadPad(GPIOE, GPIOE_SWITCH_TAMPER) == 0)
      TestThread(&SD1);
    chThdSleepMilliseconds(500);
  }
}
