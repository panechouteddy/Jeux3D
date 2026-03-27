#pragma once
#include "Scene.h"
#include "lib/Inputs/InputsMethods.h"
#include "lib/Geometries/Geometries.h"
#include "lib/Camera.h"
#include "lib/Texture.h"
#include "lib/Window.h"
#include "lib/Text.h"
#include "SceneManager.h"

class Catcher : public Scene
{
private:
    sr::Window* window;
    sr::Camera* camera;
    sr::Cube* floor;
    sr::Cube* trace;
    sr::Cube* player;
    sr::Sphere* sphere;
    sr::Text* ScoreText;
    sr::Text* HpText;
    sr::Text* PauseText;
    SceneManager* m_scenemanager;
    
    int hp;
    int score;
    float radius;
    float cameraRadius;
    float angleIndex;
    bool pause;
    bool Loose;
    float speed;
public:
    Catcher(SceneManager* sm, sr::Window* win) { m_scenemanager = sm; };

    void Init() override;
    void Update(float dt) override;
    void Render(sr::Window& window) override;
    void Pause();
    bool GroundCollider();
    void CheckHp();

private:
    void Rotate();
    void Gravity(float dt);
    void GenerateBalls();
    bool BallCollideToPlayer();
};
