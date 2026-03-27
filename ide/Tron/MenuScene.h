#pragma once
#include "Scene.h"
#include "SceneManager.h"
#include "lib/Window.h"
#include "lib/Inputs/InputsMethods.h"
#include "lib/Geometries/Geometries.h"
#include "lib/Camera.h"
#include "lib/Texture.h"
#include "lib/Text.h"

class MenuScene : public Scene
{
private:
    int choice;
    sr::Camera* camera;
    SceneManager* sceneManager;
    sr::Window* window;
    sr::Text* Catcher;
    sr::Text* Shuffle;
    sr::Text* Tron;
    sr::Text* CHoiceText;
    sr::Cube* choiceCube[3];
public:
    MenuScene(SceneManager* sm, sr::Window* win);
    void Init() override;
    void Update(float dt) override;
    void Render(sr::Window& window) override;
    void KeypadChoice();
    void UpdateColors();
    void SceneChange();
};
