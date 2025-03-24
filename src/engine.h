#ifndef ENGINE_H
#define ENGINE_H

#include "game.h"
#include <SDL3/SDL3.h>
#include <SDL3/SDL_init.h>
#include <SDL3/SDL_main.h>

typedef void (*GameUpdate)(SDL_Renderer *renderer, GameState **gameState);

struct RenderContext {
  SDL_Window *window;
  SDL_Renderer *renderer;
};

struct Game {
  bool isValid;
  const char *path;
  SDL_SharedObject *game_object;
  GameUpdate game_update;
};

struct AppState {
  RenderContext *r_context;
  Game *game;
  GameState *gameState;
};

SDL_AppResult engine_init(int width, int height, const char *title,
                          struct AppState *appState);
int engine_build_game();
// int engine_update_game(struct Game *game);

void engine_free_code_instance(struct Game *game);
SDL_AppResult engine_update(struct AppState *appState);

#endif
