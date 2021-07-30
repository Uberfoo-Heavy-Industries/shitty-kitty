/*
 * sao.h
 *
 *  Created on: Jul 29, 2021
 *      Author: james
 */

#ifndef INC_SAO_H_
#define INC_SAO_H_

#include <stdio.h>
#include "stm32l1xx_hal.h"

typedef struct {
	I2C_HandleTypeDef *i2cPort;
	UART_HandleTypeDef *uart;
} sao_port_t;

void SAOPortInit(size_t index, I2C_HandleTypeDef *i2cPort, UART_HandleTypeDef *uart);
I2C_HandleTypeDef * GetSAOI2CPort(size_t index);
UART_HandleTypeDef * GetSAOUART(size_t index);

#endif /* INC_SAO_H_ */
