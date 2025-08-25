#ifndef TEXT_MANAGER_H
#define TEXT_MANAGER_H

#include <SDL3_ttf/SDL_ttf.h>
#include <map>
#include <string>

/**
 * Loaded fonts along with companion data like point size.
 */
struct FontInfo {
  float size;
  TTF_Font *font;
};

struct TextProperties {
  SDL_Color color;
  float scale;
  int x, y;
};

class TextManager {
private:
  std::map<std::string, FontInfo> labeled_fonts;

public:
  // load a font and return the current count of loaded fonts
  int AddFont(const char *filename, const char *label, float size);

  // write the given text with the font matching label at given position with
  // optional max width and scale
  bool WriteText(const char *text, const char *label, SDL_Renderer *renderer,
                 struct TextProperties properties);
};

#endif // !TEXT_MANAGER_H
