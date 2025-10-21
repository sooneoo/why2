#ifndef _GAME_CONTEXT_H_
#define _GAME_CONTEXT_H_

#include <raylib.h>


#define VIRTUAL_WIDTH 1280
#define VIRTUAL_HEIGHT 720


typedef struct GameState GameState;


typedef struct {
	GameState ** state_stack;
    float frame_time;

    int monitorWidth;
    int monitorHeight;

    Camera2D camera;
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
	struct GameState * (*callback)(struct GameState *, GameManager_Context *);
};

#define GAME_STATE_CALLBACK(T) ((GameState*(*)(GameState*, GameManager_Context*)) (T))


#endif


