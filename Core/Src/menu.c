/*
 * menu.c
 *
 *  Created on: Jul 17, 2021
 *      Author: james
 */

#include <stdio.h>
#include "menu.h"
#include "readline.h"
#include "advent.h"
#include "userdata.h"

/* Definitions for adventureTask */
osThreadId_t adventureTaskHandle;
const osThreadAttr_t adventureTask_attributes = {
  .name = "adventureTask",
  .stack_size = 2872 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};


menu_t * current_menu = (menu_t *)&mainMenu;

void displayMenu(menu_t * menu) {
    printf("   %s\r\n\r\n", menu->title);
    for (int i = 0; i < menu->itemCount; i++) {
        printf(" %c. %s\r\n\r\n", menu->items[i].key, menu->items[i].label);
    }
}

menu_func_t findMenuFunc(char c, menu_t * menu) {
    for (int i = 0; i < sizeof(menu->itemCount); i++) {
        if (menu->items[i].key == c) {
            return menu->items[i].func;
        }
    }
    return NULL;
}

const menu_t mainMenu = {
        .title = "Main Menu",
        .itemCount = 3,
        .items = (const menu_item_t []) {
            {
                    .key = '1',
                    .label = "About",
                    .func = &aboutMenuFunc
            },
            {
                    .key = '2',
                    .label = "LED",
                    .func = &ledMenuFunc
            },
            {
                    .key = '3',
                    .label = "Game",
                    .func = &adventureMenuFunc
            }
        }
};

const menu_t ledMenu = {
        .title = "LED Menu",
        .itemCount = 2,
        .items = (const menu_item_t []) {
            {
                    .key = '1',
                    .label = "Set LED Mode",
                    .func = &ledModeMenuFunc
            },
            {
                    .key = '2',
                    .label = "Exit Menu",
                    .func = &mainMenuFunc
            }
        }
};

const menu_t ledModeMenu = {
        .title = "LED Mode Menu",
        .itemCount = 3,
        .items = (const menu_item_t []) {
            {
                    .key = '1',
                    .label = "ON",
                    .func = &ledModeOnFunc
            },
            {
                    .key = '2',
                    .label = "OFF",
                    .func = &ledModeOffFunc
            },
            {
                    .key = '3',
                    .label = "BLINK",
                    .func = &ledModeBlinkFunc
            }
        }
};

void aboutMenuFunc() {
    printf("\r\n ** Shitty OS version 1.69bis ** \r\n\r\n");
    readline("-PRESS ENTER-");
}

void mainMenuFunc() {
    current_menu = (menu_t *)&mainMenu;
}

void adventureMenuFunc() {
    adventureTaskHandle = osThreadNew(StartAdventureTask, NULL, &adventureTask_attributes);
    osThreadExit();
}

void ledMenuFunc() {
    current_menu = (menu_t *)&ledMenu;
}

void ledModeMenuFunc() {
    current_menu = (menu_t *)&ledModeMenu;
}

void ledModeOnFunc() {
    SetConfigLedMode(LED_MODE_ON);
    current_menu = (menu_t *)&ledMenu;
}

void ledModeOffFunc() {
    SetConfigLedMode(LED_MODE_OFF);
    current_menu = (menu_t *)&ledMenu;
}

void ledModeBlinkFunc() {
    SetConfigLedMode(LED_MODE_BLINK);
    current_menu = (menu_t *)&ledMenu;
}
