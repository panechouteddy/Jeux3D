#include "pch.h"
#include "Shuffle.h"
#include <cmath>
#include <chrono>
#include <iostream>




void Shuffle::RefreshText()
{
    time = chronometre;
    ScoreText->SetText(std::to_wstring(BlueScore) + std::wstring(L" : ") + std::to_wstring(RedScore));
    TimeText->SetText(std::wstring(L"temp : ") + std::to_wstring(time));
}

void Shuffle::Init()
{
    camera = new sr::Camera(sr::CameraType::PERSPECTIVE);
    camera->SetPosition({ 0.0f, 15.0f, -48.25f });
    camera->SetRotation({ 20.0f, 0.0f, 0.0f });
    camera->SetFOV(gce::PI / 6.0f);
    camera->SetFarPlane(500.0f);
    camera->SetNearPlane(0.001f);

    floor = new sr::Cube();
    floor->SetPosition({ 0.0f, 0.0f, 0.0f });
    floor->SetScale({ 30.0f, 0.1f, 50.0f });
    floor->SetColor({ 1,1,1 });

    wallright = new sr::Cube();
    wallright->SetPosition({ 15.0f , 0.0f, 0.0f });
    wallright->SetScale({ 50.0f, 0.1f, 7.0f });
    wallright->SetRotation({ 90.0f, 0.0f, 90.0f });
    wallright->SetColor({ 1,0,0 });

    wallleft = new sr::Cube();
    wallleft->SetPosition({ -15.0f , 0.0f, 0.0f });
    wallleft->SetScale({ 50.0f, 0.1f, 7.0f });
    wallleft->SetRotation({ 90.0f, 0.0f, 90.0f });
    wallleft->SetColor({ 0,0,1 });

    WallBot = new sr::Cube();
    WallBot->SetPosition({ 0.0f, 2.0f, -25.0f });
    WallBot->SetScale({ 30.0f, 0.1f, 1.0f });
    WallBot->SetRotation({ 90.0f, 0.0f, 0.0f });
    WallBot->SetColor({ 0,0,1 });

    WallBot_left = new sr::Cube();
    WallBot_left->SetPosition({ -10.0f, -3.0f, -25.0f });
    WallBot_left->SetScale({ 10.0f, 0.1f, 7.0f });
    WallBot_left->SetRotation({ 90.0f, 0.0f, 0.0f });
    WallBot_left->SetColor({ 0,0,1 });

    WallBot_right = new sr::Cube();
    WallBot_right->SetPosition({ 10.0f, -3.0f, -25.0f });
    WallBot_right->SetScale({ 10.0f, 0.1f, 7.0f });
    WallBot_right->SetRotation({ 90.0f, 0.0f, 0.0f });
    WallBot_right->SetColor({ 0,0,1 });

    WallTop = new sr::Cube();
    WallTop->SetPosition({ 0.0f, 2.0f, 25.0f });
    WallTop->SetScale({ 30.0f, 0.1f, 1.0f });
    WallTop->SetRotation({ 90.0f, 0.0f, 0.0f });
    WallTop->SetColor({ 1,0,0 });

    WallTop_left = new sr::Cube();
    WallTop_left->SetPosition({ -10.0f, -3.0f, 25.0f });
    WallTop_left->SetScale({ 10.0f, 0.1f, 7.0f });
    WallTop_left->SetRotation({ 90.0f, 0.0f, 0.0f });
    WallTop_left->SetColor({ 1,0,0 });

    WallTop_right = new sr::Cube();
    WallTop_right->SetPosition({ 10.0f, -3.0f, 25.0f });
    WallTop_right->SetScale({ 10.0f, 0.1f, 7.0f });
    WallTop_right->SetRotation({ 90.0f, 0.0f, 0.0f });
    WallTop_right->SetColor({ 1,0,0 });

    pallet = new sr::Cylinder();
    pallet->SetScale({ 2.0f, 1.0f, 2.0f });
    pallet->SetColor({ 0,0,0 });

    player = new sr::Cube();
    player->SetScale({ 2.0f, 2.0f, 2.0f });
    player->SetColor({ 0,0,1 });

    ennemi = new sr::Cube();
    ennemi->SetPosition({ 0,0,15 });
    ennemi->SetScale({ 2.0f, 2.0f, 2.0f });
    ennemi->SetColor({ 1,0,0 });

    ScoreText = new sr::Text(L"score");
    ScoreText->SetText(L"Score");
    ScoreText->SetPosition({ 740.0f, 0.0f });

    TimeText = new sr::Text(L"Time");
    TimeText->SetText(L"Time");
    TimeText->SetPosition({ 0.0f, 0.0f });

    BallTrajectory.x = 0;
    BallTrajectory.y = 0;


    Balldirection.x = 0;
    Balldirection.y = 0;

    chronometre = 120.0f;
    BlueScore = 0;
    RedScore = 0;
    mousedir.x = 777;
    mousedir.y = 536;

    Victory = false;
    Pause = false;
    gce::Vector2f32 mousedir({ 777, 536 });
    sr::SetMousePosition({ mousedir });
    player->SetPosition({ mousedir.x,0.0f,mousedir.y });

    VictoryText = new sr::Text(L"Match");
    VictoryText->SetPosition({ 700,200 });
    PauseText = new sr::Text(L"PAUSE");
    PauseText->SetPosition({ 700,200 });

    SetPlayer();
}

void Shuffle::SetDirection(sr::Cylinder* ball, sr::Cube* Raquette)
{
    gce::Vector2f32 centreBalle = { ball->GetPosition().x + 2 ,ball->GetPosition().z + 2 };
    gce::Vector2f32 centreObjet = { Raquette->GetPosition().x + 2 ,Raquette->GetPosition().z + 2 };
    centreObjet -= centreBalle;
    float v = std::sqrt(centreObjet.x * centreObjet.x + centreObjet.y * centreObjet.y);
    if (v != 0.f)
    {
        Balldirection.x = centreObjet.x / v;
        Balldirection.y = centreObjet.y / v;
    }
    else
    {
        Balldirection.x = 0.f;
        Balldirection.y = 0.f;
    }
}

void Shuffle::Update(float dt)
{
    SetPause();
    if (Pause == false)
    {
        if (Victory == false)
        {
            chronometre -= 1 * dt;
            RefreshText();
            Checklimit();
            CheckColide();
            SetDirectionPallet();
            SetEnnemiAndBall(dt);
            SetPlayer();
            ScoreVerify();
            EndVerify();
        }
    }
}

void Shuffle::Render(sr::Window& window)
{
    ScoreText->SetText(std::to_wstring(BlueScore) + L" : " + std::to_wstring(RedScore));
    TimeText->SetText(L"Temp : " + std::to_wstring(int(chronometre)));


    window.Begin(*camera);
    if (Pause == true)
    {
        window.DrawText(*PauseText);
    }
    if (Victory == false)
    {
        window.Draw(*WallBot);
        window.Draw(*WallTop);
        window.Draw(*wallright);
        window.Draw(*wallleft);
        window.Draw(*pallet);
        window.Draw(*floor);
        window.Draw(*player);
        window.Draw(*ennemi);
        window.Draw(*WallBot_right);
        window.Draw(*WallBot_left);
        window.Draw(*WallTop_right);
        window.Draw(*WallTop_left);
        window.DrawText(*TimeText);
        window.DrawText(*ScoreText);
    }
    if (Victory == true)
    {
        window.DrawText(*PauseText);
    }
    window.End();
    window.Display();
}
void Shuffle::CheckColide()
{
 
        ColideX(wallleft);
    
        ColideX(wallright);
    

    if (BallTrajectory.y == 1)
    {
        ColideY(WallTop_right);
    }
     if (BallTrajectory.y == -1)
    {
        ColideY(WallBot_right);

    }

}
void Shuffle::ColideX(sr::Cube* Wall)
{
    gce::Vector3f32 ballPosition = pallet->GetPosition();
    gce::Vector3f32 t_Wall = Wall->GetPosition();

    ballPosition.x -= t_Wall.x;

    if (ballPosition.x <= 0.5f && ballPosition.x >= -0.5f)
    {
        BallTrajectory.x *= -1;
    }
    else
        return;

}
void Shuffle::ColideY(sr::Cube* Wall)
{ 
    gce::Vector3f32 ballPosition = pallet->GetPosition();
    gce::Vector3f32 t_Wall = Wall->GetPosition();
    if (t_Wall.z <= 25 )
    {

        ballPosition.z += t_Wall.z;

    }
    else  if (t_Wall.z >= -25)
    {

        ballPosition.z -= t_Wall.z * -1;

    }
    if (ballPosition.z <= 0.5f && ballPosition.z >= -0.5f)
    {
        std::cout << "Test";
        if (ballPosition.x < -5 || ballPosition.x > 5)
        {
            BallTrajectory.y *= -1;
        }
        else
            return;
    }
    else
        return;

}
bool Shuffle::CheckPlayersCollide(sr::Cube* Raquette)
{
    gce::Vector3f32 ballPosition = pallet->GetPosition();
    gce::Vector3f32 raquettePosition = Raquette->GetPosition();
    ballPosition.x -= raquettePosition.x;
    ballPosition.z -= raquettePosition.z;
    if (ballPosition.x <= 1.0f && ballPosition.x >= -1.0f)
    {
        if (ballPosition.z <= 1.0f && ballPosition.z >= -1.0f)
        {
            return true;
        }
        else
            return false;
    }
    else
    {
        return false;
    }
}
void Shuffle::SetDirectionPallet()
{
    gce::Vector3f32 Dir_Player = player->GetPosition();
    gce::Vector3f32 Dir_Ennemi = ennemi->GetPosition();
    gce::Vector3f32 Dir_Pallet = pallet->GetPosition();

    if (CheckPlayersCollide(player))
    {
        if (Dir_Player.x < Dir_Pallet.x)
        {
            BallTrajectory.x = -1;
        }
        else if (Dir_Player.x > Dir_Pallet.x)
        {
            BallTrajectory.x = -1;
        }
        else if (Dir_Player.x - Dir_Pallet.x < 1.5f)
        {
            BallTrajectory.x = 0;
        }
        else if (Dir_Player.x - Dir_Pallet.x > -1.5f)
        {
            BallTrajectory.x = 0;
        }
        SetDirection(pallet, player);
        BallTrajectory.y = -1;
    }
    if (CheckPlayersCollide(ennemi))
    {
        if (Dir_Ennemi.x < Dir_Pallet.x)
        {
            BallTrajectory.x = 1;
        }
        else if (Dir_Ennemi.x > Dir_Pallet.x)
        {
            BallTrajectory.x = -1;
        }
        else if (Dir_Ennemi.x - Dir_Pallet.x < 1.5f)
        {
            BallTrajectory.x = 0;
        }
        else if (Dir_Ennemi.x - Dir_Pallet.x > -1.5f)
        {
            BallTrajectory.x = 0;
        }
        SetDirection(pallet, player);
        BallTrajectory.y = 1;
    }

}
void Shuffle::Checklimit()
{
    gce::Vector3f32 Dir_Player = player->GetPosition();
    gce::Vector3f32 Dir_Ennemi = ennemi->GetPosition();

    if (Dir_Player.x < -15)
    {
        player->SetPosition({ -15,0.0f,Dir_Player.z });
    }
    else if (Dir_Player.x > 15)
    {
        player->SetPosition({ 0.0f,0.0f,Dir_Player.z });
    }
    else if (Dir_Player.z < -25)
    {
        player->SetPosition({ Dir_Player.x,0.0f,-25 });
    }
    else if (Dir_Player.z >= 0)
    {
        player->SetPosition({ Dir_Player.x,0.0f,-5 });
    }
    else if (Dir_Ennemi.x < -15)
    {
        ennemi->SetPosition({ -15,0.0f,Dir_Ennemi.z });
    }
    else if (Dir_Ennemi.x > 15)
    {
        ennemi->SetPosition({ 0.0f,0.0f,Dir_Ennemi.z });
    }
    else if (Dir_Ennemi.z > 25)
    {
        ennemi->SetPosition({ Dir_Ennemi.x,0.0f, 25 });
    }
    else if (Dir_Ennemi.z <= 0)
    {
        ennemi->SetPosition({ Dir_Ennemi.x,0.0f,5 });
    }
    else
        return;
}
void Shuffle::SetPlayer()
{
    mousedir = sr::GetMousePosition();
    float middleX = 375;
    float middleY = 778;

    float p_Pos_X = (mousedir.x / middleY) * 15 - 15;
    float p_Pos_Z = (mousedir.y - middleX + 218) / (802 - middleX + 218) * -25;
    player->SetPosition({ p_Pos_X , 0.0f, p_Pos_Z });
}
void Shuffle::ScoreVerify()
{
    if (pallet->GetPosition().z < -25)
    {    
        RedScore++;
            pallet->SetPosition({ 0,0,0 });
            BallTrajectory.x = 0;
            BallTrajectory.y = 0;
            ennemi->SetPosition({ 0,0,15 });
    }
    else if (pallet->GetPosition().z >25)
    {
        BlueScore++;
            pallet->SetPosition({ 0,0,0 });
            BallTrajectory.x = 0;
            BallTrajectory.y = 0;
            ennemi->SetPosition({ 0,0,15 });
    }
}
void Shuffle::EndVerify()
{
    if (RedScore == 5)
    {
        VictoryText->SetText(L"Loose");
    }
    if (BlueScore == 5)
    {
        VictoryText->SetText(L"Victory");
    }
    if (time < 0)
    {
        if (BlueScore > RedScore)
        {
            VictoryText->SetText(L"Victory");
        }
        else
        {
        VictoryText->SetText(L"Loose");
        }
    }
}
void Shuffle::SetEnnemiAndBall(float Dt)
{
    if (pallet->GetPosition().x > 15)
    {
        Balldirection.x = -1;
    }
    if (pallet->GetPosition().x < -15)
    {
        Balldirection.x = 1;
    }
    float b_x = pallet->GetPosition().x + Balldirection.x * Dt * 13 * BallTrajectory.x;
    float b_z = pallet->GetPosition().z + Balldirection.y * Dt * 13 * BallTrajectory.y;
    float e_x = ennemi->GetPosition().x + Balldirection.x * Dt * 9 * BallTrajectory.x;
    float e_z = ennemi->GetPosition().z + Balldirection.y * Dt * 9 * BallTrajectory.y;
    pallet->SetPosition({ b_x,0,b_z });
    ennemi->SetPosition({ e_x,0,e_z });
}

void Shuffle::SetPause()
{
    if (sr::GetKey(sr::Keyboard::ESC))
    {
        if (Pause == false)
        {
            Pause = true;
        }
        else if (Pause == true)
        {
            Pause = false;
        }
    }
}
