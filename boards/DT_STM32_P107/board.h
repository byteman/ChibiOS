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

#ifndef _BOARD_H_
#define _BOARD_H_

/*
 * Setup for the STMicroelectronics STM3210C-EVAL evaluation board.
 */

/*
 * Board identifier.
 */
#define BOARD_START01_STM32_P107
#define BOARD_NAME              "Start01 STM32-P107"

/*
 * Board frequencies.
 */
#define STM32_LSECLK            32768
#define STM32_HSECLK            25000000

/*
 * MCU type, supported types are defined in ./os/hal/platforms/hal_lld.h.
 */
#define STM32F10X_CL

/*
 * Ethernet PHY type.
 */
#define BOARD_PHY_ID            MII_DM9161B_ID
#define BOARD_PHY_RMII

/*
 * IO pins assignments.
 */
#define GPIOA_SPI1NSS           4

#define GPIOE_LED_STATUS1       2
#define GPIOE_LED_STATUS2       3
#define GPIOE_LED_STATUS3       4
#define GPIOE_LED_STATUS4       5
#define GPIOE_SWITCH_TAMPER     6

/*
 * I/O ports initial setup, this configuration is established soon after reset
 * in the initialization code.
 *
 * The digits have the following meaning:
 *   0 - Analog input.
 *   1 - Push Pull output 10MHz.
 *   2 - Push Pull output 2MHz.
 *   3 - Push Pull output 50MHz.
 *   4 - Digital input.
 *   5 - Open Drain output 10MHz.
 *   6 - Open Drain output 2MHz.
 *   7 - Open Drain output 50MHz.
 *   8 - Digital input with PullUp or PullDown resistor depending on ODR.
 *   9 - Alternate Push Pull output 10MHz.
 *   A - Alternate Push Pull output 2MHz.
 *   B - Alternate Push Pull output 50MHz.
 *   C - Reserved.
 *   D - Alternate Open Drain output 10MHz.
 *   E - Alternate Open Drain output 2MHz.
 *   F - Alternate Open Drain output 50MHz.
 * Please refer to the STM32 Reference Manual for details.
 */

/*
 * Port A setup.
 * Everything input with pull-up except:
 * PA0  - Normal input      (WKUP BUTTON).
 * PA1  - Normal input      (ETH_RMII_REF_CLK).
 * PA2  - Alternate output  (ETH_RMII_MDIO).
 * PA3  - Push Pull output    (FM25L16 WP).
 * PA4  - Alternate output  (FM25L16 CS).
 * PA5  - Alternate output     (SPI1 SCK).
 * PA6  - Input with PU     (SPI1 MISO).
 * PA7  - Alternate output       (SPI1 MOSI).
 * PA8  - Alternate output  (MCO).
 * PA9  - Alternate output      (usart1 tx).
 * PA10 - Normal input      (usart1 rx).
 * PA11 - Normal input      (OTG_DM).
 * PA12 - Normal input      (OTG_DP).
 * PA13 - Normal input      (TMS).
 * PA14 - Normal input      (TCK).
 * PA15 - Normal input      (TDI).
 */
#define VAL_GPIOACRL            0xB8BB3B44      /*  PA7...PA0 */
#define VAL_GPIOACRH            0x444444BB      /* PA15...PA8 */
#define VAL_GPIOAODR            0xFFFFFFBF

/*
 * Port B setup:
 * PB0  - Input with PU     (unconnected).
 * PB1  - Input with PU     (unconnected).
 * PB2  - Normal input      (BOOT1).
 * PB3  - Normal input      (TDO).
 * PB4  - Normal input      (TRST).
 * PB5  - Input with PU     (unconnected).
 * PB6  - Input with PU     (unconnected).
 * PB7  - Input with PU     (unconnected).
 * PB8  - Input with PU    (unconnected).
 * PB9  - Input with PU    (unconnected).
 * PB10 - Input with PU     (unconnected).
 * PB11 - Alternate output  (ETH_RMII_TX_EN).
 * PB12 - Alternate output  (ETH_RMII_TXD0).
 * PB13 - Alternate output  (ETH_RMII_TXD1).
 * PB14 - Input with PU     (unconnected).
 * PB15 - Input with PU     (unconnected).
 */
#define VAL_GPIOBCRL            0x88844488      /*  PB7...PB0 */
#define VAL_GPIOBCRH            0x88BBB888      /* PB15...PB8 */
#define VAL_GPIOBODR            0xFFFFFFFF

/*
 * Port C setup:
 * PC0  - Input with PU     (unconnected).
 * PC1  - Alternate output  (ETH_MDC).
 * PC2  - Input with PU     (unconnected).
 * PC3  - Input with PU     (unconnected).
 * PC4  - Input with PU      (unconnected).
 * PC5  - Input with PU      (MII_INT).
 * PC6  - Input with PU  	(unconnected).
 * PC7  - Input with PU  	(unconnected).
 * PC8  - Input with PU     (unconnected).
 * PC9  - Input with PU     (unconnected).
 * PC10 - Alternate output  (usart3 tx).
 * PC11 - Normal input     (usart3 rx).
 * PC12 - Push Pull output   (cmbus tx|rx|en).
 * PC13 - Normal input      (unconnected).
 * PC14 - Normal input      (OSC32 IN).
 * PC15 - Normal input      (OSC32 OUT).
 */
#define VAL_GPIOCCRL            0x888888B8      /*  PC7...PC0 */
#define VAL_GPIOCCRH            0x44434B88      /* PC15...PC8 */
#define VAL_GPIOCODR            0xFFFFFF3F

/*
 * Port D setup:
 * PD0  - Input with PU     (unconnected).
 * PD1  - Input with PU     (unconnected).
 * PD2  - Input with PU     (unconnected).
 * PD3  - Input with PU     (unconnected).
 * PD4  - Input with PU     (unconnected).
 * PD5  - Alternate output  (USART2 TX, UEXT).
 * PD6  - Input with PU     (USART2 RX, UEXT).
 * PD7  - Input with PU  	(unconnected).
 * PD8  - Normal input   	(ETH CRS_DV, remapped).
 * PD9  - Normal input      (ETH RXD0,   remapped).
 * PD10 - Normal input      (ETH RXD1,   remapped).
 * PD11 - Input with PU     (unconnected).
 * PD12 - Input with PU  	(unconnected).
 * PD13 - Input with PU     (unconnected).
 * PD14 - Push Pull output     (RST anybus).
 * PD15 - Push Pull output     (MD anybus).
 */
#define VAL_GPIODCRL            0x88B88888      /*  PD7...PD0 */
#define VAL_GPIODCRH            0x338B4444      /* PD15...PD8 */
#define VAL_GPIODODR            0xFFFFFFFF
/*
 * Port E setup:
 * PE0  - Input with PU     (unconnected).
 * PE1  - Input with PU     (unconnected).
 * PE2  - Push Pull output     (LED1).
 * PE3  - Push Pull output     (LED2).
 * PE4  - Push Pull output     (LED3).
 * PE5  - Push Pull output  (LED4).
 
 * PE6  - Normal input      (KEY).
 * PE7 - Input with PU     (unconnected).
 * PE8 - Input with PU     (unconnected).
 * PE9 - Input with PU     (unconnected).
 * PE10 - Input with PU     (unconnected).
 * PE11 - Input with PU     (unconnected).
 * PE12 - Input with PU     (unconnected).
 * PE13 - Input with PU     (unconnected).
 * PE14 - Input with PU     (unconnected).
 * PE15 - Input with PU     (unconnected).
 */
#define VAL_GPIOECRL            0x84333388      /*  PE7...PE0 */
#define VAL_GPIOECRH            0x88888888      /* PE15...PE8 */
#define VAL_GPIOEODR            0xFFFFFFFF

#if !defined(_FROM_ASM_)
#ifdef __cplusplus
extern "C" {
#endif
  void boardInit(void);
#ifdef __cplusplus
}
#endif
#endif /* _FROM_ASM_ */

#endif /* _BOARD_H_ */
