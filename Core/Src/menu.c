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
  .stack_size = 2250 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};


menu_t * current_menu = (menu_t *)&mainMenu;

void displayMenu(menu_t * menu) {
    printf("\r\n   %s\r\n\r\n", menu->title);
    for (int i = 0; i < menu->itemCount; i++) {
        printf(" %s. %s\r\n", menu->items[i].key, menu->items[i].label);
    }
    printf("\r\n");
}

menu_func_t findMenuFunc(char * c, menu_t * menu) {
    for (int i = 0; i < menu->itemCount; i++) {
        if (strcmp(menu->items[i].key, c) == 0) {
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
                    .key = "1",
                    .label = "About",
                    .func = &aboutMenuFunc
            },
            {
                    .key = "2",
                    .label = "LED",
                    .func = &ledMenuFunc
            },
            {
                    .key = "3",
                    .label = "Shitty Pixel",
                    .func = &shittyPixelMenuFunc
            },
            {
                    .key = "4",
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
                    .key = "1",
                    .label = "Set LED Mode",
                    .func = &ledModeMenuFunc
            },
            {
                    .key = "x",
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
                    .key = "1",
                    .label = "ON",
                    .func = &ledModeOnFunc
            },
            {
                    .key = "2",
                    .label = "OFF",
                    .func = &ledModeOffFunc
            },
            {
                    .key = "3",
                    .label = "BLINK",
                    .func = &ledModeBlinkFunc
            }
        }
};

const menu_t shittyPixelMenu = {
        .title = "Shitty Pixel Menu",
        .itemCount = 9,
        .items = (const menu_item_t []) {
            {
                    .key = "1",
                    .label = "Get Info",
                    .func = &shittyPixelInfoFunc
            },
            {
                    .key = "2",
                    .label = "Set Mode",
                    .func = &shittyPixelModeFunc
            },
            {
                    .key = "3",
                    .label = "Set Speed",
                    .func = &shittyPixelSpeedFunc
            },
            {
                    .key = "4",
                    .label = "Set Red",
                    .func = &shittyPixelRedFunc
            },
            {
                    .key = "5",
                    .label = "Set Green",
                    .func = &shittyPixelGreenFunc
            },
            {
                    .key = "6",
                    .label = "Set Blue",
                    .func = &shittyPixelBlueFunc
            },
            {
                    .key = "7",
                    .label = "Save Pixel Settings",
                    .func = &shittyPixelSaveFunc
            },
            {
                    .key = "8",
                    .label = "Load Pixel Settings",
                    .func = &shittyPixelLoadFunc
            },
            {
                    .key = "x",
                    .label = "Exit Menu",
                    .func = &mainMenuFunc
            }
       }
};

int promptPortNum() {
	int i;
	if (!sscanf(readline("Enter SAO port (1-2)> "), "%d", &i) || i > 2 || i < 1) {
		printf("Invalid port number!\r\n");
		return -1;
	}
	return i - 1;
}

int promptNumber(const char * prompt) {
    int i;
    if (!sscanf(readline(prompt), "%d", &i)) {
        printf("Invalid number!\r\n");
        return -1;
    }
    return i;
}

int checkNumber(int min, int max, int value) {
    if (value < min) {
        printf("Invalid number. Number must be greater than %d\r\n", min);
        return -1;
    }
    if (value > max) {
        printf("Invalid number. Number must be less than %d\r\n", max);
        return -1;
    }
    return 0;
}

void aboutMenuFunc() {
    printf("\r\n ** Shitty OS version 1.69bis ** \r\n\r\n (c)2021 Uberfoo Heavy Industries\r\n\r\n");
    readline("-PRESS ENTER-\r\n");
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

	int i = promptNumber("Enter mode number (0-255)> ");
	SetPixelMode(port, i);
}

void shittyPixelRedFunc() {
    int port = promptPortNum();
    if (port < 0) return;

    int i = promptNumber("Enter red intensity (0-255)> ");
    if (checkNumber(0, 255, i)) return;

    SetPixelColor(port, PIXEL_CONTROL_RED, i);
}

void shittyPixelGreenFunc() {
    int port = promptPortNum();
    if (port < 0) return;

    int i = promptNumber("Enter green intensity (0-255)> ");
    if (checkNumber(0, 255, i)) return;

    SetPixelColor(port, PIXEL_CONTROL_GREEN, i);
}

void shittyPixelBlueFunc() {
    int port = promptPortNum();
    if (port < 0) return;

    int i = promptNumber("Enter blue intensity (0-255)> ");
    if (checkNumber(0, 255, i)) return;

    SetPixelColor(port, PIXEL_CONTROL_BLUE, i);
}

void shittyPixelSpeedFunc() {
    int port = promptPortNum();
    if (port < 0) return;

    int i = promptNumber("Enter speed (0-255)> ");
    if (checkNumber(0, 255, i)) return;

    SetPixelSpeed(port, i);
}

void shittyPixelSaveFunc() {
    int port = promptPortNum();
    if (port < 0) return;

    SavePixelState(port);
}

void shittyPixelLoadFunc() {
    int port = promptPortNum();
    if (port < 0) return;

    LoadPixelState(port);
}

void shittyPixelInfoFunc() {
	int port = promptPortNum();
	if (port < 0) return;

	int16_t i = GetPixelData(port, PIXEL_EEPROM_DC_YEAR);

	if (i < 0) {
	    printf("\r\nShitty Pixel not detected on SAO port %d.\r\n", port + 1);
	    return;
	}
	printf("\r\nMade for DEF CON %d\r\n", i);
	printf("Maker ID:  %d\r\n", GetPixelData(port, PIXEL_EEPROM_MAKER));
	printf("SAO Type:  %d\r\n", GetPixelData(port, PIXEL_EEPROM_SAO_TYPE));
	printf("Arbitrary: %d\r\n", GetPixelData(port, PIXEL_EEPROM_ARBITRARY));
}
