#include "game.h"
#include "ui/ui.h"

void game_update(SDL_Renderer *renderer, GameState *state) {
  SDL_FRect rect;
  float x, y;
  auto mouseState = SDL_GetMouseState(&x, &y);
  rect.x = x;
  rect.y = y;
  rect.w = 100;
  rect.h = 200;

  SDL_SetRenderDrawColor(renderer, 0, state->red, 0, 0);
  draw_button(renderer, vec2_f{x, y}, vec2{100, 200});
}

GameState *game_init() {
  SDL_Log("Game init - start");
  auto state = new GameState();
  state->red = 128;
  state->sceneManager = SceneManager();
  SDL_Log("Game init - finish");
  return state;
}
