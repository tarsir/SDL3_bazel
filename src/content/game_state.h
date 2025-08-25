#ifndef STATE_H
#define STATE_H
#include "scene.h"
#include "src/ui/text_manager.h"

struct GameState {
  SceneManager sceneManager;
  TextManager textManager;
};

#endif // !STATE_H
