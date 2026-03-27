#pragma once
#include "Scene.h"
#include <memory>

class SceneManager
{
private:
    std::shared_ptr<Scene> currentScene;

public:
    void SetScene(std::shared_ptr<Scene> scene);
    void Update(float dt);
    void Render(sr::Window& window);
    void ChangeScene(std::shared_ptr<Scene> newScene);
};