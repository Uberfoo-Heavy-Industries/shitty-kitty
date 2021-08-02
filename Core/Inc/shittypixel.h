/*
 * shittypixel.h
 *
 *  Created on: Jul 29, 2021
 *      Author: james
 */

#ifndef INC_SHITTYPIXEL_H_
#define INC_SHITTYPIXEL_H_

#include <stdio.h>

#define PIXEL_CONTROL_ADDR  0x42
#define PIXEL_CONTROL_MODE  0x00
#define PIXEL_CONTROL_SPEED 0x01
#define PIXEL_CONTROL_RED   0x02
#define PIXEL_CONTROL_GREEN 0x03
#define PIXEL_CONTROL_BLUE  0x04
#define PIXEL_CONTROL_STATE 0x05

#define PIXEL_STATE_SAVE    0x57
#define PIXEL_STATE_LOAD    0x52

#define PIXEL_EEPROM_ADDR      0x50
#define PIXEL_EEPROM_DC_YEAR   0x00
#define PIXEL_EEPROM_MAKER     0x01
#define PIXEL_EEPROM_SAO_TYPE  0x02
#define PIXEL_EEPROM_ARBITRARY 0x03

void SetPixelMode(size_t port, uint8_t mode);
void SetPixelSpeed(size_t port, uint8_t speed);
void SetPixelColor(size_t port, uint8_t color, uint8_t value);
void SavePixelState(size_t port);
void LoadPixelState(size_t port);

uint8_t GetPixelData(size_t port, uint8_t data);

#endif /* INC_SHITTYPIXEL_H_ */
