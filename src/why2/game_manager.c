#include "why2/game_manager.h"
#include <raylib.h>


GameManager game_manager(GameState * init_state, GameManager_Context * context) {
	return (GameManager) {
		.context = context
		, .state = init_state
	};
}


void game_manager_execute(GameManager * self) {
	self->context->frame_time = GetFrameTime();
	self->state = self->state->callback(self->state, self->context);
}


