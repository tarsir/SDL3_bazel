#define SDL_MAIN_USE_CALLBACKS 1
#include "engine.h"
#include "game.h"
#include <SDL3/SDL.h>
#include <SDL3/SDL_log.h>
#include <SDL3/SDL_main.h>

static SDL_Window *window = NULL;

SDL_AppResult SDL_AppInit(void **appstate, int argc, char *argv[]) {
  *appstate = new AppState;
  AppState &state = *static_cast<AppState *>(*appstate);

  const char *title = "SDL Game";
  int width = 1920, height = 1080;
  auto setMetadata =
      SDL_SetAppMetadata(title, "0.0.1", "com.tarsir.sdl3_bazel_skeleton");
  if (!setMetadata) {
    SDL_Log("SDL Metadata failed to set: %s", SDL_GetError());
    return SDL_APP_FAILURE;
  }

  auto flags = SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_GAMEPAD;
  auto ret = SDL_InitSubSystem(flags);
  if (!ret) {
    SDL_Log("SDL Init failed with: %s", SDL_GetError());
    return SDL_APP_FAILURE;
  }

  state.r_context = std::make_unique<struct RenderContext>();

  if (!SDL_CreateWindowAndRenderer(title, width, height, 0,
                                   &state.r_context->window,
                                   &state.r_context->renderer)) {
    SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,
                 "Couldn't create window/renderer: %s", SDL_GetError());
    return SDL_APP_FAILURE;
  }

  state.gameState.reset(game_init());

  return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppEvent(void *appstate, SDL_Event *event) {
  AppState &state = *static_cast<AppState *>(appstate);
  switch (event->type) {
  case SDL_EVENT_QUIT:
    return SDL_APP_SUCCESS;
  case SDL_EVENT_KEY_DOWN:
    return SDL_APP_CONTINUE;
  }
  return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppIterate(void *appstate) {
  AppState &state = *static_cast<AppState *>(appstate);
  SDL_Log("App iterate - start");
  const RenderContext *r_context = state.r_context.get();
  SDL_SetRenderDrawColor(r_context->renderer, 0, 0, 0, 255);
  SDL_RenderClear(r_context->renderer);

  game_update(state.r_context->renderer, state.gameState.get());

  SDL_RenderPresent(r_context->renderer);
  SDL_Log("App iterate - finish");
  return SDL_APP_CONTINUE;
}

void SDL_AppQuit(void *appstate, SDL_AppResult result) {
  delete static_cast<AppState *>(appstate);
}
