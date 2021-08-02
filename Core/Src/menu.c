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
#include "shittypixel.h"

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
        .itemCount = 4,
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
                    .label = "Shitty Pixel",
                    .func = &shittyPixelMenuFunc
            },
            {
                    .key = '4',
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
                    .key = 'x',
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

const menu_t shittyPixelMenu = {
        .title = "Shitty Pixel Menu",
        .itemCount = 3,
        .items = (const menu_item_t []) {
            {
                    .key = '1',
                    .label = "Get Info",
                    .func = &shittyPixelInfoFunc
            },
            {
                    .key = '2',
                    .label = "Set Mode",
                    .func = &shittyPixelModeFunc
            },
            {
                    .key = 'x',
                    .label = "Exit Menu",
                    .func = &mainMenuFunc
            }
       }
};

int promptPortNum() {
	int i;
	if (!sscanf(readline("Enter SAO port > "), "%d", &i) || i > 2 || i < 1) {
		printf("Invalid port number!\r\n");
		return -1;
	}
	return i - 1;
}

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

void shittyPixelMenuFunc() {
    current_menu = (menu_t *)&shittyPixelMenu;
}

void shittyPixelModeFunc() {
	int port = promptPortNum();
	if (port < 0) return;

	int i;
	if (!sscanf(readline("Enter mode > "), "%d", &i)) {
		printf("Invalid number!\r\n");
		return;
	}
	SetPixelMode(port, i);
}

void shittyPixelInfoFunc() {
	int port = promptPortNum();
	if (port < 0) return;

	printf("Made for DEF CON %d\r\n", GetPixelData(port, PIXEL_EEPROM_DC_YEAR));
	printf("Maker ID:  %d\r\n", GetPixelData(port, PIXEL_EEPROM_MAKER));
	printf("SAO Type:  %d\r\n", GetPixelData(port, PIXEL_EEPROM_SAO_TYPE));
	printf("Arbitrary: %d\r\n", GetPixelData(port, PIXEL_EEPROM_ARBITRARY));
}
