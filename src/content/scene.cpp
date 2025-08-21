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

void SceneManager::Draw(SDL_Renderer *renderer) {
  if (m_currentScene) {
    m_currentScene->OnDraw(renderer);
  }
}

void SceneManager::HandleEvent(SDL_Event *event) {
  if (m_currentScene) {
    m_currentScene->OnEvent(event);
  }
}

MainMenuScene::MainMenuScene() { this->option = 0; }
void MainMenuScene::OnLoad() {}
void MainMenuScene::OnDraw(SDL_Renderer *renderer) const {
  TTF_Font *font = TTF_OpenFont("assets/LTSuperiorSerif-Regular.otf", 18);
  if (!font) {
    SDL_Log("Couldn't open font: %s\n", SDL_GetError());
    exit(1);
  }

  SDL_Color color = {255, 255, 255};
  SDL_Surface *text =
      TTF_RenderText_Blended(font, "Main Menu Scene!", 0, color);
  if (text) {
    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, text);
    SDL_DestroySurface(text);
    if (!texture) {
      SDL_Log("Couldn't create text: %s\n", SDL_GetError());
      exit(1);
    }
    SDL_FRect dst;
    const float scale = 4.0f;

    int w = 0, h = 0;
    SDL_GetRenderOutputSize(renderer, &w, &h);
    SDL_GetTextureSize(texture, &dst.w, &dst.h);
    dst.x = ((w / scale) - dst.w) / 2;
    dst.y = ((h / scale) - dst.h) / 2;
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    SDL_RenderTexture(renderer, texture, NULL, &dst);
    SDL_RenderPresent(renderer);
  }
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
