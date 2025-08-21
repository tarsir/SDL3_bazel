#define SDL_MAIN_USE_CALLBACKS 1
#include "engine.h"
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <memory>

#ifndef GAME_LIB_PATH
#define GAME_LIB_PATH ""
#endif

static SDL_Window *window = NULL;

SDL_AppResult SDL_AppInit(void **appstate, int argc, char *argv[]) {
  std::unique_ptr<struct RenderContext> r_context =
      std::make_unique<RenderContext>();

  std::unique_ptr<struct Game> game = std::make_unique<Game>();
  game->isValid = false;
  game->path = GAME_LIB_PATH;

  *appstate = new AppState;
  AppState &state = *static_cast<AppState *>(*appstate);
  state.game = std::move(game);
  state.r_context = std::move(r_context);

  auto result = engine_init(1920, 1080, "SDL3 Bazel Test", &state);
  if (state.game->game_object == nullptr) {
    return SDL_APP_FAILURE;
  }

  debug_pointers(&state, "SDL_AppInit");

  return result;
}

SDL_AppResult SDL_AppEvent(void *appstate, SDL_Event *event) {
  AppState &state = *static_cast<AppState *>(appstate);
  if (event->type == SDL_EVENT_KEY_DOWN && event->key.key == SDLK_F5) {
    if (engine_rebuild_reload_game(&state) != SDL_APP_CONTINUE) {
      SDL_Log("Game reload triggered by keypress failed: %s", SDL_GetError());
      return SDL_APP_FAILURE;
    }
  }
  if (state.game->game_object == nullptr ||
      state.game->game_handle_event == nullptr) {
    debug_pointers(&state, "SDL_AppEvent");
    return SDL_APP_FAILURE;
  }
  if (state.game->game_handle_event != nullptr) {
    return state.game->game_handle_event(event, state.gameState.get());
  }
}

SDL_AppResult SDL_AppIterate(void *appstate) {
  AppState &state = *static_cast<AppState *>(appstate);
  if (state.game->game_object == nullptr) {
    debug_pointers(&state, "SDL_AppIterate");
    return SDL_APP_FAILURE;
  }
  return engine_update(&state);
}

void SDL_AppQuit(void *appstate, SDL_AppResult result) {
  delete static_cast<AppState *>(appstate);
}
