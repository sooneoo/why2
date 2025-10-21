#ifndef _GAME_STATE_MENU_H_
#define _GAME_STATE_MENU_H_

#include "game_context.h"
#include "menu_button.h"

typedef struct {
    GameState super;

    Texture2D background;
    MenuButton menu_button;
} GameState_Menu;


#define GAME_STATE_MENU ((T)(GameState_Menu*))


GameState_Menu game_state_menu(Texture2D background, Texture2D button);


#endif


