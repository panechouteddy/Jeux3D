#pragma once
#include "SceneManager.h"
#include "Scene.h"
#include "lib/Window.h"
#include "lib/Inputs/InputsMethods.h"
#include "lib/Geometries/Geometries.h"
#include "lib/Camera.h"
#include "lib/Texture.h"
#include "lib/Text.h"

class Tron : public Scene
{
private:
    bool Pause;
    bool Alive;
    int Hp;
    int Score;
    SceneManager* m_sceneManager;
    sr::Text* HpText;
    sr::Text* ScoreText;
    sr::Text* PauseText;
    sr::Text* QuitText;
    sr::Cube* floor;
    sr::Window* window;
    sr::Camera* camera;
    sr::Cube* wallleft;
    sr::Cube* wallright;
    sr::Cube* WallBot;
    sr::Cube* WallTop;
    sr::Cube* Player;
    sr::Cube* Ennemi [2];
    sr::Cube* PlayerFollow[6];
    sr::Cube* EnnemiFollow[2][6];
    sr::Cube* StaticWall[4];
    gce::Vector2f32 P_direction;
    gce::Vector2f32* P_direction_Follow[6];
    gce::Vector2f32* E_dirrection_Follow[2][6];
public:
    Tron(SceneManager* sm, sr::Window* win) : window(win) { m_sceneManager = sm; }
    void Init() override;
    void Update(float dt) override;
    void CheckCollison();
    void Render(sr::Window& window) override;
    void KeypadDetect();
    void FollowMove(float dt);
    void MovePlayer(float dt);
    gce::Vector3f32 ConvertColor(float r, float g, float b);
    void WallCheck();
    void ennemiMoove(float dt);
    void EnnemiFollowMove(float dt);
    void CollideWithFollow();
    void CollideWithEnnemi();
    void pauseGame();
    void CheckAlive();
    void QuitScene();
private:

};