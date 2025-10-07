#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <raylib.h>

typedef struct GameState GameState;


typedef struct {
	GameState ** state_stack;
} GameManager_Context;


typedef enum {
    GameState_ID_Menu
    , GameState_ID_Options
    , GameState_ID_Pause
    , GameState_ID_GameControl
    , GameState_ID_GameOver
    , GameState_ID_Info
    , GameState_ID_N
} GameState_ID ;


struct GameState {
	struct GameState * (*callback)(struct GameState *, GameManager_Context *, float);
};


typedef struct {
    GameState super;
} GameState_Menu;


#define GAME_STATE_MENU ((T)(GameState_Menu*))


static GameState * game_state_menu_callback(
        GameState * self, GameManager_Context * context, float frame_time) {
    DrawText("Menu", 400, 300, 40, BLACK);
    if(IsKeyPressed(KEY_SPACE) == true) {
        return context->state_stack[GameState_ID_Options];        
    } else {
        return context->state_stack[GameState_ID_Menu];        
    }
}


GameState_Menu game_state_menu(void) {
    return (GameState_Menu) {
        .super = {
            .callback = game_state_menu_callback
        }
    };
}


typedef struct {
    GameState super;
} GameState_Options;


static GameState * game_state_options_callback(
        GameState * self, GameManager_Context * context, float frame_time) {
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
        GameState * self, GameManager_Context * context, float frame_time) {
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
        GameState * self, GameManager_Context * context, float frame_time) {
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
        GameState * self, GameManager_Context * context, float frame_time) {
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
        GameState * self, GameManager_Context * context, float frame_time) {
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


typedef struct {
	GameManager_Context context;
	GameState * state;	
} GameManager;


GameManager game_manager(GameState * init_state, GameState ** state_stack) {
	return (GameManager) {
		.context = {
			.state_stack = state_stack
		}
		, .state = init_state
	};
}


void game_manager_execute(GameManager * self) {
	float frame_time = GetFrameTime();
	self->state = self->state->callback(self->state, &self->context, frame_time);
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

GameManager game_manager_instance;

#include "version.h"


#define WINDOW_TITLE "Froggy Hop"


int main(void) {
    Why2_Version version = why2_version();
    char wtitle[64];
    sprintf(wtitle, "%s %d.%d.%d", WINDOW_TITLE, version.major, version.minor, version.patch);

	InitWindow(800, 600, wtitle);
    SetConfigFlags(FLAG_VSYNC_HINT | FLAG_WINDOW_HIGHDPI);
	SetTargetFPS(144);
    
    state_menu = game_state_menu();
    state_options = game_state_options();
    state_game_control = game_state_game_control();
    state_pause = game_state_pause();
    state_game_over = game_state_game_over();
    state_info = game_state_info();
	game_manager_instance = game_manager(&state_menu.super, state_buff_mem);

	while(WindowShouldClose() == false) {
		BeginDrawing();
		ClearBackground(WHITE);
        game_manager_execute(&game_manager_instance);
		DrawFPS(10, 10);
		EndDrawing();
	}

	CloseWindow();

	printf("program exit..\n");
	return EXIT_SUCCESS;
}




