#ifndef GAME_H
#define GAME_H
#include "content/state.h"
#include <SDL3/SDL_render.h>

extern "C" void game_update(SDL_Renderer *renderer, GameState *state);
extern "C" void game_init(GameState **state);

#endif
