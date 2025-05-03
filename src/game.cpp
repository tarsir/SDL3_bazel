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

void game_init(GameState **state) {
  SDL_Log("Game init - start");
  *state = new GameState;
  (*state)->red = 128;
  SDL_Log("Game init - finish");
}
