#include "engine.h"
#include "game.h"
#include <SDL3/SDL_init.h>
#include <SDL3/SDL_mouse.h>
#include <SDL3/SDL_render.h>
#include <csignal>
#include <cstdio>
#include <cstdlib>

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
    SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,
                 "Couldn't create window/renderer: %s", SDL_GetError());
    return SDL_APP_FAILURE;
  }

  game_init(&state->gameState);

  state->game->isValid = false;

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

  state->game->isValid = true;

  debug_pointers(state, "engine_init");
  return SDL_APP_CONTINUE;
}

SDL_AppResult engine_build_game(struct AppState *state) {
  const char *pwd = std::getenv("BUILD_WORKING_DIRECTORY");
  SDL_Log("Working directory: %s", pwd);
  char cmd[200];
  auto n = snprintf(cmd, 200, "cd %s && bazel build //:game", pwd);
  SDL_Log("Rebuilding game code with command: %s", cmd);
  const int result = std::system(cmd);
  if (result != 0) {
    SDL_Log("Failed to rebuild game code, exiting");
    return SDL_APP_FAILURE;
  }

  return SDL_APP_CONTINUE;
}

SDL_AppResult engine_rebuild_reload_game(struct AppState *state) {
  SDL_Log("Rebuilding game...");
  state->game->isValid = false;

  if (state->game->game_object != nullptr) {
    engine_free_code_instance(state->game);
  }

  if (engine_build_game(state) != 0) {
    return SDL_APP_FAILURE;
  }

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

  state->game->isValid = true;
  SDL_Log("Game rebuild complete!");
  return SDL_APP_CONTINUE;
}

void engine_free_code_instance(struct Game *game) {
  SDL_Log("Free and reset game code - start");
  SDL_UnloadObject(game->game_object);
  game->game_update = nullptr;
  game->game_object = nullptr;
  game->isValid = false;
  SDL_Log("Free and reset game code - finish");
}

SDL_AppResult engine_update(struct AppState *appState) {
  // SDL_Log("Engine update - start");
  const struct RenderContext *r_context = appState->r_context;
  struct Game *game = appState->game;
  SDL_SetRenderDrawColor(r_context->renderer, 0, 0, 0, 255);
  SDL_RenderClear(r_context->renderer);

  if (game->isValid) {
    // SDL_Log("Game update - start");
    game->game_update(r_context->renderer, &(appState->gameState));
    // SDL_Log("Game update - finish");
  }

  SDL_RenderPresent(r_context->renderer);

  // SDL_Log("Engine update - finish");
  return SDL_APP_CONTINUE;
}

/**
 * Log a bunch of pointers related to app state, the render context, and the
 * game info pointer.
 *
 * This can't be used in release builds as-is since we don't do anything with
 * the game info pointer.
 */
void debug_pointers(const struct AppState *appState, const char *label) {
  SDL_Log("-- %s START", label);
  SDL_Log("appState pointer: %d", appState);
  SDL_Log("r_context pointer: %d", appState->r_context);
  SDL_Log("r_context->renderer pointer: %d", appState->r_context->renderer);
  SDL_Log("r_context->window pointer: %d", appState->r_context->window);
  SDL_Log("game pointer: %d", appState->game);
  SDL_Log("game->isValid pointer: %d", appState->game->isValid);
  SDL_Log("game_object pointer: %d", appState->game->game_object);
  SDL_Log("game_update pointer: %d", appState->game->game_update);
  SDL_Log("game_state pointer: %d", appState->gameState);
  SDL_Log("-- %s END", label);
}
