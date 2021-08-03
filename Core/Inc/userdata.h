/*
 * userdata.h
 *
 *  Created on: Jul 26, 2021
 *      Author: james
 */

#ifndef INC_USERDATA_H_
#define INC_USERDATA_H_

#include <stdio.h>

#define CONFIG_PAGE_ADDR 0x0803FC00
typedef enum {
    LED_MODE_ON,
    LED_MODE_OFF,
    LED_MODE_BLINK
} led_mode_t;

typedef struct {
    led_mode_t ledMode;
    uint8_t    ledDutyCycle;
} userconfig_t;

void InitUserConfig();
void SetConfigLedMode(led_mode_t mode);
void SetConfigLedDutyCycle(uint8_t dutyCycle);
userconfig_t * GetConfig();

#endif /* INC_USERDATA_H_ */
