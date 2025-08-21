#include "game.h"
#include "ui/ui.h"
#include <memory>

void game_update(SDL_Renderer *renderer, GameState *state) {
  state->sceneManager.Draw(renderer);
}

GameState *game_init() {
  GameState *state = new GameState();
  state->sceneManager = SceneManager();
  return state;
}

SDL_AppResult game_handle_event(SDL_Event *event, GameState *state) {
  switch (event->type) {
  case SDL_EVENT_QUIT:
    return SDL_APP_SUCCESS;
  case SDL_EVENT_KEY_DOWN:
    SDL_Log("%d", event->key.key);
    switch (event->key.key) {}
  }

  return SDL_APP_CONTINUE;
}
