#include "engine.h"
#include "game.h"
#include <SDL3/SDL_init.h>
#include <SDL3/SDL_mouse.h>
#include <SDL3/SDL_render.h>

SDL_AppResult engine_init(const int width, const int height, const char *title,
                          struct AppState *state) {
  auto setMetadata =
      SDL_SetAppMetadata(title, "0.0.1", "com.tarsir.sdl3_bazel_test");
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

  struct RenderContext *r_context = state->r_context;

  if (!SDL_CreateWindowAndRenderer(title, width, height, 0, &r_context->window,
                                   &r_context->renderer)) {
    SDL_Log("Couldn't create window/renderer: %s", SDL_GetError());
    return SDL_APP_FAILURE;
  }

  game_init(&state->gameState);

  state->game->game_object = SDL_LoadObject("./libgame.so");
  if (state->game->game_object == nullptr) {
    SDL_Log("Failed to load game code: %s", SDL_GetError());
    return SDL_APP_FAILURE;
  }

  state->game->game_update =
      GameUpdate(SDL_LoadFunction(state->game->game_object, "game_update"));
  if (state->game->game_update == nullptr) {
    SDL_Log("Failed to load game_update: %s", SDL_GetError());
    return SDL_APP_FAILURE;
  }

  return SDL_APP_CONTINUE;
}

int engine_build_game() { return 0; }

SDL_AppResult engine_update(struct AppState *appState) {
  SDL_Log("Engine update - start");
  const struct RenderContext *r_context = appState->r_context;
  struct Game *game = appState->game;
  SDL_SetRenderDrawColor(r_context->renderer, 0, 0, 0, 255);
  SDL_RenderClear(r_context->renderer);

  if (game->isValid) {
    SDL_Log("Game update - start");
    SDL_Log("Game state: %d", appState->gameState->red);
    game->game_update(r_context->renderer, &(appState->gameState));
    SDL_Log("Game update - finish");
  }

  SDL_RenderPresent(r_context->renderer);

  SDL_Log("Engine update - finish");
  return SDL_APP_CONTINUE;
}
