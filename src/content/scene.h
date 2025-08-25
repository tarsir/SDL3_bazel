#ifndef SCENE_H
#define SCENE_H
#include "src/ui/text_manager.h"
#include <SDL3/SDL_events.h>
#include <SDL3/SDL_init.h>
#include <SDL3/SDL_render.h>
#include <cstdint>
#include <memory>

class Scene {
public:
  virtual ~Scene() = default;
  virtual void OnLoad() = 0;
  virtual void OnUpdate(float deltaTime) = 0;
  virtual void OnDraw(SDL_Renderer *renderer,
                      TextManager *textManager) const = 0;
  virtual void OnUnload() = 0;
  virtual SDL_AppResult OnEvent(SDL_Event *event) = 0;
};

class SceneManager {
private:
  std::unique_ptr<Scene> m_currentScene;

public:
  SceneManager();
  void ChangeScene(std::unique_ptr<Scene> newScene);
  void Update(float deltaTime);
  void Draw(SDL_Renderer *renderer, TextManager *textManager);
  void HandleEvent(SDL_Event *event);
};

class MainMenuScene : public Scene {
private:
  uint8_t option;

public:
  MainMenuScene();
  void OnLoad() override;
  void OnDraw(SDL_Renderer *renderer, TextManager *textManager) const override;
  void OnUnload() override;
  void OnUpdate(float deltaTime) override;
  SDL_AppResult OnEvent(SDL_Event *event) override;
};

#endif // !SCENE_H
