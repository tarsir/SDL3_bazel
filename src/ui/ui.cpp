#include "ui.h"
#include <SDL3/SDL.h>
#include <SDL3/SDL_oldnames.h>
#include <SDL3/SDL_rect.h>
#include <SDL3/SDL_render.h>

void draw_button(SDL_Renderer *renderer, vec2_f pos, vec2 dims) {
  SDL_FRect rect;
  rect.x = pos.x;
  rect.y = pos.y;
  rect.w = dims.x;
  rect.h = dims.y;
  SDL_RenderRect(renderer, &rect);
}
