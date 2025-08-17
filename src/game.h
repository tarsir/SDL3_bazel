#ifndef GAME_H
#define GAME_H
#include "content/game_state.h"
#include "content/scene.h"
#include <SDL3/SDL_render.h>

extern "C" void game_update(SDL_Renderer *renderer, GameState *state);
extern "C" GameState *game_init();

#endif
