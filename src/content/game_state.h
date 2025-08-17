#ifndef STATE_H
#define STATE_H
#include "scene.h"
#include <cstdint>

struct GameState {
  uint8_t red;
  SceneManager sceneManager;
};

#endif // !STATE_H
