#include "pch.h"
#include "SceneManager.h"
#include "Tron.h"
#include "Shuffle.h"
#include "Catcher.h"

void SceneManager::SetScene(std::shared_ptr<Scene> scene)
{
    currentScene = scene;
    currentScene->Init();
}

void SceneManager::Update(float dt)
{

    if (currentScene)
        currentScene->Update(dt);
}

void SceneManager::Render(sr::Window& window)
{
    if (currentScene)
        currentScene->Render(window);
}

void SceneManager::ChangeScene(std::shared_ptr<Scene> newScene)
{
    if (currentScene)
        currentScene.reset(); 

    currentScene = newScene;
    currentScene->Init();
}
