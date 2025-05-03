#ifndef STATE_H
#include "scene.h"
#include <cstdint>

struct GameState {
  uint8_t red;
  Scene *scene;
};

#endif // !STATE_H
