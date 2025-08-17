#include "scene.h"
#include <SDL3/SDL_init.h>
#include <SDL3/SDL_log.h>
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

void SceneManager::Draw() {
  if (m_currentScene) {
    m_currentScene->OnDraw();
  }
}

void SceneManager::HandleEvent(SDL_Event *event) {
  if (m_currentScene) {
    m_currentScene->OnEvent(event);
  }
}

MainMenuScene::MainMenuScene() { this->option = 0; }
void MainMenuScene::OnLoad() {}
void MainMenuScene::OnDraw() const {}
void MainMenuScene::OnUnload() {}
void MainMenuScene::OnUpdate(float deltaTime) {}
SDL_AppResult MainMenuScene::OnEvent(SDL_Event *event) {
  switch (event->type) {
  case SDL_EVENT_QUIT:
    return SDL_APP_SUCCESS;
  case SDL_EVENT_KEY_DOWN:
    SDL_Log("%d", event->key.key);
    switch (event->key.key) {}
  }

  return SDL_APP_CONTINUE;
}
