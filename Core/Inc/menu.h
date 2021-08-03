/*
 * menu.h
 *
 *  Created on: Jul 17, 2021
 *      Author: james
 */

#ifndef INC_MENU_H_
#define INC_MENU_H_

typedef void (* menu_func_t)();

typedef struct {
    const char * const key;
    const char * const label;
    const menu_func_t func;
} menu_item_t;

typedef struct {
    const char * const title;
    const int itemCount;
    const menu_item_t * const items;
} menu_t;

void displayMenu(menu_t * menu);
menu_func_t findMenuFunc(char * c, menu_t * menu);

void mainMenuFunc();
void aboutMenuFunc();
void adventureMenuFunc();
void ledMenuFunc();
void ledModeMenuFunc();
void ledModeOnFunc();
void ledModeOffFunc();
void ledModeBlinkFunc();
void shittyPixelMenuFunc();
void shittyPixelModeFunc();
void shittyPixelInfoFunc();
void shittyPixelRedFunc();
void shittyPixelGreenFunc();
void shittyPixelBlueFunc();
void shittyPixelSpeedFunc();
void shittyPixelLoadFunc();
void shittyPixelSaveFunc();

extern menu_t * current_menu;

extern const menu_t mainMenu;

#endif /* INC_MENU_H_ */
