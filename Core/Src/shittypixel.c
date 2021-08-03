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
	if (HAL_I2C_Master_Transmit(hi2c, (PIXEL_CONTROL_ADDR << 1) & 1, data, 2, HAL_MAX_DELAY) != HAL_OK) {
	    printf("Failed to set mode.\r\n");
	}
	printf("Mode set.\r\n");
}

void SetPixelSpeed(size_t port, uint8_t speed) {
    I2C_HandleTypeDef *hi2c = GetSAOI2CPort(port);
    uint8_t buf[2] = {PIXEL_CONTROL_SPEED, speed};
    if (HAL_I2C_Master_Transmit(hi2c, (PIXEL_CONTROL_ADDR << 1) & 1, buf, 2, HAL_MAX_DELAY) != HAL_OK) {
        printf("Failed to set speed.\r\n");
    }
    printf("Speed set.");
}

void SetPixelColor(size_t port, uint8_t color, uint8_t value) {
    I2C_HandleTypeDef *hi2c = GetSAOI2CPort(port);
    uint8_t buf[2] = {color, value};
    if (HAL_I2C_Master_Transmit(hi2c, (PIXEL_CONTROL_ADDR << 1) & 1, buf, 2, HAL_MAX_DELAY) != HAL_OK) {
        printf("Failed to set color intensity.\r\n");
    }
    printf("Color intensity set.");
}

void SavePixelState(size_t port) {
    I2C_HandleTypeDef *hi2c = GetSAOI2CPort(port);
    uint8_t buf[2] = {PIXEL_CONTROL_STATE, PIXEL_STATE_SAVE};
    if (HAL_I2C_Master_Transmit(hi2c, (PIXEL_CONTROL_ADDR << 1) & 1, buf, 2, HAL_MAX_DELAY) != HAL_OK) {
        printf("Failed to save pixel state.\r\n");
    }
    printf("Pixel state saved.");
}

void LoadPixelState(size_t port) {
    I2C_HandleTypeDef *hi2c = GetSAOI2CPort(port);
    uint8_t buf[2] = {PIXEL_CONTROL_STATE, PIXEL_STATE_LOAD};
    if (HAL_I2C_Master_Transmit(hi2c, (PIXEL_CONTROL_ADDR << 1) & 1, buf, 2, HAL_MAX_DELAY) != HAL_OK) {
        printf("Failed to load pixel state.\r\n");
    }
    printf("Pixel state loaded.");
}

int16_t GetPixelData(size_t port, uint8_t data) {
	I2C_HandleTypeDef *hi2c = GetSAOI2CPort(port);
	uint8_t buf[1] = {data};
	if (HAL_I2C_Master_Transmit(hi2c, PIXEL_EEPROM_ADDR << 1, buf, 1, HAL_MAX_DELAY) != HAL_OK) {
	    printf("Failed to transmit address.");
	    return -1;
	}
	buf[0] = 0x00;
	if (HAL_I2C_Master_Receive(hi2c, PIXEL_EEPROM_ADDR << 1, buf, 1, HAL_MAX_DELAY) != HAL_OK) {
	    printf("Failed to receive pixel data.");
	    return -1;
	}
	return (int16_t)buf[0];
}



