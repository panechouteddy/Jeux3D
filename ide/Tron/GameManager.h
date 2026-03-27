#pragma once
#include "SceneManager.h"
#include "lib/Window.h"
#include "lib/Camera.h"

class GameManager
{
private:
    static GameManager* instance;
    sr::Window* window;
    sr::Camera* camera;
    SceneManager sceneManager;

public:
    GameManager();
    static GameManager* GetInstance();

    void Init(int choice);
    void Run();
    sr::Window& GetWindow() { return *window; }
};