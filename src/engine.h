#ifndef ENGINE_H
#define ENGINE_H

#include "game.h"
#include <SDL3/SDL.h>
#include <SDL3/SDL_init.h>
#include <memory>

typedef void (*GameUpdate)(SDL_Renderer *renderer, GameState *gameState);
typedef GameState *(*GameInit)();

struct RenderContext {
  SDL_Window *window;
  SDL_Renderer *renderer;
};

struct Game {
  bool isValid;
  const char *path;
  SDL_SharedObject *game_object;
  GameUpdate game_update;
  GameInit game_init;
};

struct AppState {
  std::unique_ptr<struct RenderContext> r_context;
  std::unique_ptr<struct Game> game;
  std::unique_ptr<struct GameState> gameState;
};

SDL_AppResult engine_init(int width, int height, const char *title,
                          struct AppState *appState);
SDL_AppResult engine_build_game(struct AppState *appState);
SDL_AppResult engine_rebuild_reload_game(struct AppState *appState);

void engine_free_code_instance(struct Game *game);
SDL_AppResult engine_update(struct AppState *appState);
void debug_pointers(const struct AppState *appState, const char *label);

#endif
