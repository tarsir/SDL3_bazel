#include "text_manager.h"

int TextManager::AddFont(const char *filename, const char *label, float size) {
  TTF_Font *font = TTF_OpenFont(filename, size);
  if (!font) {
    SDL_Log("Couldn't open font: %s\n", SDL_GetError());
    exit(1);
  }

  struct FontInfo fontInfo = {size, font};
  this->labeled_fonts.insert(std::make_pair(label, fontInfo));
  return this->labeled_fonts.size();
}

bool TextManager::WriteText(const char *text, const char *font_label,
                            SDL_Renderer *renderer,
                            struct TextProperties properties) {
  SDL_Color color = {255, 255, 255};
  TTF_Font *font = this->labeled_fonts[font_label].font;
  SDL_Surface *text_surface = TTF_RenderText_Blended(font, text, 0, color);

  if (text_surface) {
    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, text_surface);
    SDL_DestroySurface(text_surface);
    if (!texture) {
      SDL_Log("Couldn't create text: %s\n", SDL_GetError());
      exit(1);
    }
    SDL_FRect dst;

    int w = 0, h = 0;
    SDL_GetRenderOutputSize(renderer, &w, &h);
    SDL_GetTextureSize(texture, &dst.w, &dst.h);
    dst.x = properties.x;
    dst.y = properties.y;
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderTexture(renderer, texture, NULL, &dst);
  }
  return true;
}
