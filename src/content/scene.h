#ifndef SCENE_H
#define SCENE_H
#include <SDL3/SDL_events.h>
#include <SDL3/SDL_init.h>
#include <cstdint>
#include <memory>

class Scene {
public:
  virtual ~Scene() = default;
  virtual void OnLoad() = 0;
  virtual void OnUpdate(float deltaTime) = 0;
  virtual void OnDraw() const = 0;
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
  void Draw();
  void HandleEvent(SDL_Event *event);
};

class MainMenuScene : public Scene {
private:
  uint8_t option;

public:
  MainMenuScene();
  void OnLoad() override;
  void OnDraw() const override;
  void OnUnload() override;
  void OnUpdate(float deltaTime) override;
  SDL_AppResult OnEvent(SDL_Event *event) override;
};

#endif // !SCENE_H
