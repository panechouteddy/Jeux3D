#pragma once
#include "Scene.h"
#include "lib/Inputs/InputsMethods.h"
#include "lib/Geometries/Geometries.h"
#include "lib/Camera.h"
#include "lib/Texture.h"
#include "lib/Window.h"
#include "lib/Text.h"
#include "SceneManager.h"

class Shuffle : public Scene
{
private :
    bool Pause;
    bool Victory;
    SceneManager* m_sceneManager;
    sr::Camera* camera;
    sr::Cube* wallleft;
    sr::Cube* wallright;
    sr::Cube* WallBot;
    sr::Cube* WallBot_left;
    sr::Cube* WallBot_right;
    sr::Cube* WallTop;
    sr::Cube* WallTop_left;
    sr::Cube* WallTop_right;
    sr::Cube* floor;
    sr::Cylinder* pallet;
    sr::Cube* player;
    sr::Cube* ennemi;
    sr::Text* ScoreText;
    sr::Text* TimeText;
    sr::Text* PauseText;
    sr::Text* VictoryText;
    sr::Window* window;
    gce::Vector2i32 BallTrajectory;
    gce::Vector2f32 Balldirection;
    gce::Vector2i32 mousedir ;
public:
    int BlueScore;
    int RedScore;
    float chronometre;
    int time;
    Shuffle(SceneManager* sm, sr::Window* win) : window(win) { m_sceneManager = sm; }
    void RefreshText();
    void Init() override;
    void Update(float dt) override;
    void Render(sr::Window& window) override;
    void CheckColide();
    void ColideX(sr::Cube* Wall);
    void ColideY(sr::Cube* Wall);
    bool CheckPlayersCollide(sr::Cube* Raquette);;
    void SetDirectionPallet();
    void Checklimit();
    void SetPlayer();
    void ScoreVerify();
    void EndVerify();
    void SetEnnemiAndBall(float Dt);
    void SetPause();
private:
    void SetDirection(sr::Cylinder* ball, sr::Cube* Raquette);

   

};