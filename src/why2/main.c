#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <raylib.h>

#include "why2/game_manager.h"
#include "why2/game_state_menu.h"


typedef struct {
    GameState super;
} GameState_Options;


static GameState * game_state_options_callback(
        GameState * self, GameManager_Context * context) {
    DrawText("Options", 400, 300, 40, BLACK);
    if(IsKeyPressed(KEY_SPACE) == true) {
        return context->state_stack[GameState_ID_GameControl];
    } else {
        return context->state_stack[GameState_ID_Options];
    }
}


GameState_Options game_state_options(void) {
    return (GameState_Options) {
        .super = {
            .callback = game_state_options_callback
        }     
    };
}


typedef struct {
    GameState super;
} GameState_Pause;


static GameState * game_state_pause_callback(
        GameState * self, GameManager_Context * context) {
    DrawText("Pause", 400, 300, 40, BLACK);
    if(IsKeyPressed(KEY_SPACE) == true) {
        return context->state_stack[GameState_ID_GameOver];
    } else {
        return context->state_stack[GameState_ID_Pause];
    }
}


GameState_Pause game_state_pause(void) {
    return (GameState_Pause) {
        .super = {
            .callback = game_state_pause_callback
        }
    };
}


typedef struct {
    GameState super;
} GameState_GameControl;


static GameState * game_state_game_control_callback(
        GameState * self, GameManager_Context * context) {
    DrawText("Game Control", 400, 300, 40, BLACK);
    if(IsKeyPressed(KEY_SPACE) == true) {
        return context->state_stack[GameState_ID_Pause];
    } else {
        return context->state_stack[GameState_ID_GameControl];
    }
}


GameState_GameControl game_state_game_control(void) {
    return (GameState_GameControl) {
        .super = {
            .callback = game_state_game_control_callback
        }
    };
}


typedef struct {
    GameState super;
} GameState_GameOver;


static GameState * game_state_game_over_callback(
        GameState * self, GameManager_Context * context) {
    DrawText("Game Over", 400, 300, 40, BLACK);
    if(IsKeyPressed(KEY_SPACE) == true) {
        return context->state_stack[GameState_ID_Info];
    } else {
        return context->state_stack[GameState_ID_GameOver];
    }
}

 
GameState_GameOver game_state_game_over(void) {
    return (GameState_GameOver) {
        .super = {
            .callback = game_state_game_over_callback
        }
    };
}


typedef struct {
    GameState super;
} GameState_Info;


static GameState * game_state_info_callback(
        GameState * self, GameManager_Context * context) {
    DrawText("Game Info", 400, 300, 40, BLACK);
    if(IsKeyPressed(KEY_SPACE) == true) {
        return context->state_stack[GameState_ID_Menu];
    } else {
        return context->state_stack[GameState_ID_Info];
    }
}


GameState_Info game_state_info(void) {
    return (GameState_Info) {
        .super = {
            .callback = game_state_info_callback
        }
    };
}


static GameState_Menu state_menu;
static GameState_Options state_options;
static GameState_GameControl state_game_control;
static GameState_Pause state_pause;
static GameState_GameOver state_game_over;
static GameState_Info state_info;


static GameState* state_buff_mem[GameState_ID_N] = {
    &state_menu.super
    , &state_options.super
    , &state_pause.super
    , &state_game_control.super
    , &state_game_over.super
    , &state_info.super
};

GameManager_Context context;
GameManager manager;

#include "version.h"

#define IMG "assets/img/"
#define WINDOW_TITLE "Why2"


int main(void) {
    Why2_Version version = why2_version();
    char wtitle[64];
    sprintf(wtitle, "%s %d.%d.%d", WINDOW_TITLE, version.major, version.minor, version.patch);

	InitWindow(VIRTUAL_WIDTH, VIRTUAL_HEIGHT, wtitle);

    int display = GetCurrentMonitor();
    int monitorWidth = GetMonitorWidth(display);
    int monitorHeight = GetMonitorHeight(display);
    //SetWindowSize(monitorWidth, monitorHeight);


    SetConfigFlags(FLAG_VSYNC_HINT | FLAG_WINDOW_HIGHDPI);
	SetTargetFPS(144);
    ToggleFullscreen();
    
    Texture2D texture_background = LoadTexture(IMG "background.png");

    state_menu = game_state_menu(texture_background, (Texture2D){0});
    state_options = game_state_options();
    state_game_control = game_state_game_control();
    state_pause = game_state_pause();
    state_game_over = game_state_game_over();
    state_info = game_state_info();

    context = (GameManager_Context) {
        .state_stack = state_buff_mem
        , .monitorWidth = monitorWidth
        , .monitorHeight = monitorHeight
        , .camera = {
            .target = (Vector2){ VIRTUAL_WIDTH/2.0f, VIRTUAL_HEIGHT/2.0f }
            , .offset = (Vector2){ monitorWidth/2.0f, monitorHeight/2.0f }
            , .rotation = 0.0f
            , .zoom = 1.0f
        }
    };

	manager = game_manager(&state_menu.super, &context);

	while(WindowShouldClose() == false) {
		BeginDrawing();
		ClearBackground(WHITE);
        game_manager_execute(&manager);
		DrawFPS(10, 10);
		EndDrawing();
	}

    UnloadTexture(texture_background);
	CloseWindow();

	return EXIT_SUCCESS;
}




