/*
 * fm25l16.h
 *
 *  Created on: 2012-7-1
 *      Author: Administrator
 */

#ifndef FM25L16_H_
#define FM25L16_H_


void fm25l16_write_byte(uint16_t address,uint8_t data);
uint8_t fm25l16_read_byte(uint16_t addr);

#endif /* FM25L16_H_ */
