#define SDL_MAIN_USE_CALLBACKS 1
#include "engine.h"
#include <SDL3/SDL3.h>
#include <SDL3/SDL_main.h>

static SDL_Window *window = NULL;

SDL_AppResult SDL_AppInit(void **appstate, int argc, char *argv[]) {
  struct RenderContext r_context{nullptr, nullptr};

  struct Game game{false, "game.so", nullptr};

  *appstate = new AppState;
  AppState &state = *static_cast<AppState *>(*appstate);
  state.game = &game;
  state.r_context = &r_context;

  return engine_init(1920, 1080, "SDL3 Bazel Test", &state);
}

SDL_AppResult SDL_AppEvent(void *appstate, SDL_Event *event) {
  AppState &state = *static_cast<AppState *>(appstate);
  switch (event->type) {
  case SDL_EVENT_QUIT:
    return SDL_APP_SUCCESS;
  }
  return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppIterate(void *appstate) {
  SDL_Log("SDL_AppIterate - precast");
  AppState &state = *static_cast<AppState *>(appstate);
  SDL_Log("SDL_AppIterate - cast");
  return engine_update(&state);
}

void SDL_AppQuit(void *appstate, SDL_AppResult result) {}
