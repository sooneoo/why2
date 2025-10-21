#include "why2/game_state_menu.h"
#include <raylib.h>



static GameState * game_state_menu_callback(
        GameState_Menu * self, GameManager_Context * context) {
    DrawTexturePro(
        self->background
        , (Rectangle) {0, 0, self->background.width, self->background.height}
        , (Rectangle){0, 0, context->monitorWidth, context->monitorHeight}
        , (Vector2){0,0}
        , 0
        , WHITE);
    
    if(IsKeyPressed(KEY_SPACE) == true) {
        return context->state_stack[GameState_ID_Options];        
    } else {
        return context->state_stack[GameState_ID_Menu];        
    }
}


GameState_Menu game_state_menu(Texture2D background, Texture2D button) {
    return (GameState_Menu) {
        .super = {
            .callback = GAME_STATE_CALLBACK(game_state_menu_callback)
        }
        , .background = background
    };
}
