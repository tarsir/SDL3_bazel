#include "scene.h"
#include <SDL3/SDL_init.h>
#include <SDL3/SDL_log.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <cstdlib>
#include <memory>

SceneManager::SceneManager() {
  this->m_currentScene = std::make_unique<MainMenuScene>();

  if (this->m_currentScene) {
    this->m_currentScene->OnLoad();
  }
}

void SceneManager::ChangeScene(std::unique_ptr<Scene> newScene) {
  if (m_currentScene) {
    m_currentScene->OnUnload();
  }

  m_currentScene = std::move(newScene);
  m_currentScene->OnLoad();
}

void SceneManager::Update(float deltaTime) {
  if (m_currentScene) {
    m_currentScene->OnUpdate(deltaTime);
  }
}

void SceneManager::Draw(SDL_Renderer *renderer, TextManager *textManager) {
  if (m_currentScene) {
    m_currentScene->OnDraw(renderer, textManager);
  }
}

void SceneManager::HandleEvent(SDL_Event *event) {
  if (m_currentScene) {
    m_currentScene->OnEvent(event);
  }
}

MainMenuScene::MainMenuScene() { this->option = 0; }
void MainMenuScene::OnLoad() { SDL_Log("Loading the Main Menu scene..."); }
void MainMenuScene::OnDraw(SDL_Renderer *renderer,
                           TextManager *textManager) const {
  SDL_Color color = {255, 255, 255};
  struct TextProperties props = {color, 2.0f, 120, 120};
  textManager->WriteText("Main Menu Scene!", "default", renderer, props);
}

void MainMenuScene::OnUnload() {}
void MainMenuScene::OnUpdate(float deltaTime) {}

SDL_AppResult MainMenuScene::OnEvent(SDL_Event *event) {
  switch (event->type) {
  case SDL_EVENT_QUIT:
    return SDL_APP_SUCCESS;
  case SDL_EVENT_KEY_DOWN:
    switch (event->key.key) {
    case SDLK_1:
      auto newScene = std::make_unique<MainMenuScene>();
    }
  }

  return SDL_APP_CONTINUE;
}
