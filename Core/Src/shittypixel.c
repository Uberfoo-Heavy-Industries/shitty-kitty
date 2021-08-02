/*
 * shittypixel.c
 *
 *  Created on: Jul 29, 2021
 *      Author: james
 */

#include "stm32l1xx_hal.h"

#include "shittypixel.h"
#include "sao.h"

void SetPixelMode(size_t port, uint8_t mode) {
	I2C_HandleTypeDef *hi2c = GetSAOI2CPort(port);
	uint8_t data[2] = {PIXEL_CONTROL_MODE, mode};
	HAL_I2C_Master_Transmit(hi2c, (PIXEL_CONTROL_ADDR << 1) & 1, data, 2, HAL_MAX_DELAY);
}

void SetPixelSpeed(size_t port, uint8_t speed);
void SetPixelColor(size_t port, uint8_t color, uint8_t value);
void SavePixelState(size_t port);
void LoadPixelState(size_t port);

uint8_t GetPixelData(size_t port, uint8_t data) {
	I2C_HandleTypeDef *hi2c = GetSAOI2CPort(port);
	uint8_t buf[] = {data};
	HAL_I2C_Master_Transmit(hi2c, PIXEL_EEPROM_ADDR << 1, buf, 1, HAL_MAX_DELAY);
	HAL_I2C_Master_Receive(hi2c, PIXEL_EEPROM_ADDR << 1, buf, 1, HAL_MAX_DELAY);
	return buf[0];
}



