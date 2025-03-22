#include <iostream>

#define SDL_MAIN_USE_CALLBACKS 1
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>

static SDL_Window *window = NULL;
static SDL_Renderer *renderer = NULL;
static Uint8 blue = 0;

SDL_AppResult SDL_AppInit(void **appstate, int argc, char *argv[]) {
    auto setMetadata = SDL_SetAppMetadata("SDL3 Bazel Test", "0.0.1", "com.tarsir.sdl3_bazel_test");
    if (!setMetadata) {
      SDL_Log("SDL Metadata failed to set: %s", SDL_GetError());
    }

    auto flags = SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_GAMEPAD;
    auto ret = SDL_InitSubSystem(flags);
    std::cout << "SDL init returned: " << ret << std::endl;
    if (!ret) {
      SDL_Log("SDL Init failed with: %s", SDL_GetError());
    }

    if (!SDL_CreateWindowAndRenderer("SDL3 Bazel Test", 640, 480, 0, &window, &renderer)) {
      SDL_Log("Couldn't create window/renderer: %s", SDL_GetError());
      return SDL_APP_FAILURE;
    }

    return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppEvent(void *appstate, SDL_Event *event) {
  if (event->type == SDL_EVENT_QUIT) {
    return SDL_APP_SUCCESS;
  }
  return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppIterate(void *appstate) {
  blue += 1;
  SDL_SetRenderDrawColor(renderer, 0, 0, blue, 0);
  SDL_RenderClear(renderer);
  SDL_RenderPresent(renderer);
  return SDL_APP_CONTINUE;
}

void SDL_AppQuit(void *appstate, SDL_AppResult result) {}
