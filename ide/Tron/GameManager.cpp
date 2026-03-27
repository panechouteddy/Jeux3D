#include "pch.h"
#include "GameManager.h"
#include "MenuScene.h"
#include "Tron.h"
#include "Shuffle.h"
#include "Catcher.h"
#include "Tron.h"
#include <chrono>

GameManager* GameManager::instance = nullptr;

GameManager::GameManager()
{

}

GameManager* GameManager::GetInstance()
{
    if (!instance)
        instance = new GameManager();
    return instance;
}

void GameManager::Init(int choice)
{
    window = new sr::Window(L"Test", 1920, 1080);
    camera = new sr::Camera((sr::CameraType::PERSPECTIVE));
    switch (choice)
    {
        case (1):
          sceneManager.SetScene(std::make_shared<Catcher>(&sceneManager, window));
          break;
        case (2):
            sceneManager.SetScene(std::make_shared<Shuffle>(&sceneManager, window));
            break;
        case (3):
            sceneManager.SetScene(std::make_shared<Tron>(&sceneManager, window));
        break;
    }
}

void GameManager::Run()
{
    using namespace std::chrono;
    auto lastTime = steady_clock::now();

    while (window->IsOpen())
    {
        auto currentTime = steady_clock::now();
        duration<float> dt = duration_cast<duration<float>>(currentTime - lastTime);
        lastTime = currentTime;
      
        sceneManager.Render(*window);       
        sceneManager.Update(dt.count());
    }
}
