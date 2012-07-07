/*
 * fm25l16.c
 *
 *  Created on: 2012-7-1
 *      Author: Administrator
 */
#include "ch.h"
#include "hal.h"
#include "fm25l16.h"
static uint8_t txbuf[512];
static uint8_t rxbuf[512];


#define FM25L16B_CMD_WREN           0x06			/*Set Write Enable Latch*/
#define FM25L16B_CMD_WRDI           0x04			/*Write Disable*/
#define FM25L16B_CMD_RDSR  			0x05			/*Read Status Register*/
#define FM25L16B_CMD_WRSR			0x01			/*Write Status Register*/
#define	FM25L16B_CMD_READ			0x03			/*Read Memory Data*/
#define FM25L16B_CMD_WRITE			0x02			/*Write Memory Data*/

static const SPIConfig hs_spicfg = {
  NULL,
  GPIOA,
  GPIOA_SPI1NSS,
  0
};

static const SPIConfig ls_spicfg = {
  NULL,
  GPIOA,
  GPIOA_SPI1NSS,
  SPI_CR1_BR_2 | SPI_CR1_BR_1  //128perclk
};

static uint8_t tx_ch,rx_ch;
uint8_t fm25l16_write_read(uint8_t cmd)
{
	spiAcquireBus(&SPID1);              /* Acquire ownership of the bus.    */
	spiStart(&SPID1, &hs_spicfg);       /* Setup transfer parameters.       */
	spiSelect(&SPID1);                  /* Slave Select assertion.          */
	tx_ch = cmd;
	spiExchange(&SPID1, 1,
			&tx_ch, &rx_ch);          /* Atomic transfer operations.      */
	spiUnselect(&SPID1);                /* Slave Select de-assertion.       */
    spiReleaseBus(&SPID1);              /* Ownership release.               */
	return rx_ch;
}

uint8_t fm25l16_exchange(int len)
{
	spiAcquireBus(&SPID1);              /* Acquire ownership of the bus.    */
	spiStart(&SPID1, &hs_spicfg);       /* Setup transfer parameters.       */
	spiSelect(&SPID1);                  /* Slave Select assertion.          */
	spiExchange(&SPID1, len,
			txbuf, rxbuf);          /* Atomic transfer operations.      */
	spiUnselect(&SPID1);                /* Slave Select de-assertion.       */
    spiReleaseBus(&SPID1);              /* Ownership release.               */
	return len;
}
uint8_t fm25l16_read_byte(uint16_t addr)
{
	uint8_t data = 0;

	txbuf[0] = FM25L16B_CMD_READ;
	txbuf[1] = addr>>8;
	txbuf[2] = addr&0x00ff;
	txbuf[3] = 0xff;

	fm25l16_exchange(4);

	data = rxbuf[3];

	return data;

}


void fm25l16_write_byte(uint16_t address,uint8_t data)
{

	fm25l16_write_read(FM25L16B_CMD_WREN);			/*Ð´Ê¹ÄÜ*/

	txbuf[0] = FM25L16B_CMD_WRITE;
	txbuf[1] = address>>8;
	txbuf[2] = address&0x00ff;
	txbuf[3] = data;

	fm25l16_exchange(4);

	fm25l16_write_read(FM25L16B_CMD_WRDI);			/*Ð´½ûÖ¹*/

}

