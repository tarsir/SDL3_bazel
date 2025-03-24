#ifndef GAME_H
#define GAME_H
#include <SDL3/SDL3.h>
#include <SDL3/SDL_init.h>
#include <SDL3/SDL_render.h>
#include <cstdint>

struct GameState {
  uint8_t red;
};

extern "C" void game_update(SDL_Renderer *renderer, GameState **state);
extern "C" void game_init(GameState **state);

#endif
