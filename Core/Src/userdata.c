/*
 * userdata.c
 *
 *  Created on: Jul 26, 2021
 *      Author: james
 */

#include "userdata.h"
#include "stm32l1xx_hal.h"
#include <string.h>

uint8_t userdata[1024] __attribute__ ((section(".user_data")));

userconfig_t current_config;

void InitUserConfig() {
    memcpy(&current_config, userdata, sizeof(userconfig_t));
}

uint32_t WriteConfigToFlash()
{
    static FLASH_EraseInitTypeDef EraseInitStruct;
    uint32_t PAGEError;

    HAL_FLASH_Unlock();

    // __HAL_FLASH_CLEAR_FLAG(FLASH_FLAG_EOP | FLASH_FLAG_OPERR | FLASH_FLAG_WRPERR | FLASH_FLAG_PGAERR | FLASH_FLAG_PGSERR );

    /* Fill EraseInit structure*/
    EraseInitStruct.TypeErase   = FLASH_TYPEERASE_PAGES;
    EraseInitStruct.PageAddress = CONFIG_PAGE_ADDR;
    EraseInitStruct.NbPages     = 1;

    if (HAL_FLASHEx_Erase(&EraseInitStruct, &PAGEError) != HAL_OK)
    {
        /*Error occurred while page erase.*/
        uint32_t err = HAL_FLASH_GetError();
        printf("Error erasing flash: %ld\r\n\r\n", err);
        return err;
    }

    uint8_t *data = (uint8_t*)&current_config;
    for (int i = 0; i < sizeof(userconfig_t); i += 4) {
        if (HAL_FLASH_Program(FLASH_TYPEPROGRAMDATA_WORD, CONFIG_PAGE_ADDR + i, data[i]) != HAL_OK) {
            /*Error occurred while page erase.*/
            uint32_t err = HAL_FLASH_GetError();
            printf("Error writing flash @0x%08x: %ld\r\n\r\n", CONFIG_PAGE_ADDR + i, err);
            return err;

        }
    }

    HAL_FLASH_Lock();
    return 0;
}

void SetConfigLedMode(led_mode_t mode) {
    current_config.ledMode = mode;
    WriteConfigToFlash();
}

void SetConfigLedDutyCycle(uint8_t dutyCycle) {
    current_config.ledDutyCycle = dutyCycle;
    WriteConfigToFlash();
}

userconfig_t * GetConfig() {
    return &current_config;
}
