/*
 * sao.c
 *
 *  Created on: Jul 29, 2021
 *      Author: james
 */


#include "sao.h"

sao_port_t saoPort[2];

void SAOPortInit(size_t index, I2C_HandleTypeDef *i2cPort, UART_HandleTypeDef *uart) {
	saoPort[index].i2cPort = i2cPort;
	saoPort[index].uart = uart;
}

I2C_HandleTypeDef * GetSAOI2CPort(size_t index) {
	return saoPort[index].i2cPort;
}

UART_HandleTypeDef * GetSAOUART(size_t index) {
	return saoPort[index].uart;
}
