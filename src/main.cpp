#define SDL_MAIN_USE_CALLBACKS 1
#include "engine.h"
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>

static SDL_Window *window = NULL;

SDL_AppResult SDL_AppInit(void **appstate, int argc, char *argv[]) {
  struct RenderContext *r_context = new RenderContext{nullptr, nullptr};

  struct Game *game = new Game{false, "game.so", nullptr, nullptr};

  *appstate = new AppState;
  AppState &state = *static_cast<AppState *>(*appstate);
  state.game = game;
  state.r_context = r_context;

  auto result = engine_init(1920, 1080, "SDL3 Bazel Test", &state);
  if (state.game->game_object == nullptr) {
    return SDL_APP_FAILURE;
  }

  debug_pointers(&state, "SDL_AppInit");

  return result;
}

SDL_AppResult SDL_AppEvent(void *appstate, SDL_Event *event) {
  AppState &state = *static_cast<AppState *>(appstate);
  switch (event->type) {
  case SDL_EVENT_QUIT:
    return SDL_APP_SUCCESS;
  case SDL_EVENT_KEY_DOWN:
    switch (event->key.key) {
    case SDLK_W:
      if (engine_rebuild_reload_game(&state) != SDL_APP_CONTINUE) {
        SDL_Log("Game reload triggered by keypress failed: %s", SDL_GetError());
        return SDL_APP_FAILURE;
      }
      break;
    }
  }
  return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppIterate(void *appstate) {
  AppState &state = *static_cast<AppState *>(appstate);
  if (state.game->game_object == nullptr) {
    debug_pointers(&state, "SDL_AppIterate");
    return SDL_APP_FAILURE;
  }
  return engine_update(&state);
}

void SDL_AppQuit(void *appstate, SDL_AppResult result) {}
