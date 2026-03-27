#include "pch.h"
#include "Catcher.h"
#include <chrono>
#include <cmath>
#include <cstdlib>





void Catcher::Init()
{
    camera = new sr::Camera(sr::CameraType::PERSPECTIVE);
    camera->SetPosition({ 13.0f, 18.0f, -9.0f });
    camera->SetRotation({ 45.0f, -40.0f, 0.0f });
    camera->SetFOV(gce::PI / 4.0f);
    camera->SetFarPlane(500.0f);
    camera->SetNearPlane(0.001f);


    HpText = new sr::Text(L"HP");
    HpText->SetPosition({ 0, 0 });
    ScoreText = new sr::Text(L"Score");
    ScoreText->SetPosition({ 500, 200 });
   
    floor = new sr::Cube();
    floor->SetPosition({ 0.0f, 0.0f, 0.0f });
    floor->SetScale({ 10.0f, 0.1f, 10.0f });

    player = new sr::Cube();
    player->SetColor({ 0.0f, 1.0f, 0.0f });
    player->SetPosition({ 0.0f, 0.5f, -4.0f });
    player->SetScale({ 1.0f, 1.0f, 1.0f });

    sphere = new sr::Sphere();
    sphere->SetColor({ 0.0f, 1.0f, 0.0f });
    sphere->SetScale({ 0.5f, 0.5f, 0.5f });

    PauseText = new sr::Text(L"PAUSE");
    PauseText->SetPosition({ 700,200 });
    speed = 1.0f;
    hp = 3;
    score = 0;
    radius = 4;
    cameraRadius = 18;
    angleIndex = 180;
    pause = false;
    Loose = false;

    GenerateBalls();
}

void Catcher::Update(float dt)
{
    CheckHp();
    Pause();
    if (Loose == false)
    {
        if (pause == false)
        {
            if (sr::GetKey(sr::Keyboard::D))
            {
                angleIndex--;
                if (angleIndex < 0) angleIndex = 360;
            }
            if (sr::GetKey(sr::Keyboard::Q))
            {
                angleIndex++;
                if (angleIndex > 360) angleIndex = 0;
            }

            Gravity(dt);
            Rotate();
            if (GroundCollider())
            {
                GenerateBalls();
                hp -= 1;
            }
             
            else if (BallCollideToPlayer())
            {
                GenerateBalls();
                score += 100;
                speed += 0.5f;
            }
        }
    }
}


void Catcher::Render(sr::Window& window)
{
    HpText->SetText(L"HP : " + std::to_wstring(hp));
    ScoreText->SetText(std::to_wstring(score));

    window.Begin(*camera);
    if (Loose == false)
    {
        if (pause == true)
        {
            window.DrawText(*PauseText);
        }

        window.Draw(*sphere);
        window.Draw(*floor);
        window.Draw(*player);
        window.DrawText(*ScoreText);
        window.DrawText(*HpText);
    }
    if (Loose == true)
    {
        window.DrawText(*ScoreText);
    }
    window.End();
    window.Display();
}

void Catcher::Pause()
{
    if (sr::GetKey(sr::Keyboard::ESC))
    {
        if (pause == false)
        {
            pause = true;
        }
        else if (pause == true)
        {
            pause = false;
        }
    }
}

void Catcher::Rotate()
{
    float angle = angleIndex * gce::PI / 180;
    float x = std::sin(angle) * radius;
    float z = std::cos(angle) * radius;
    float camX = std::sin(angle) * cameraRadius;
    float camZ = std::cos(angle) * 9;

    player->SetPosition({ x, 0.5f, z });
    camera->SetPosition({ camX, 18 , camZ });

    gce::Vector3f32 dir = { -camX, -18.0f, -camZ };
    float rotate_y = atan2(dir.x, dir.z) * 180.0f / gce::PI;
    float rotate_x = -atan2(dir.y, sqrt(dir.x * dir.x + dir.z * dir.z)) * 180.0f / gce::PI;
    camera->SetRotation({ rotate_x, rotate_y, 0.0f });
}

void Catcher::Gravity(float dt)
{
    gce::Vector3f32 pos = sphere->GetPosition();
    pos.y -= 2.0f * dt *speed ;
    sphere->SetPosition(pos);
}

bool Catcher::GroundCollider()
{
    if (sphere->GetPosition().y <= 0)
    {
        return true;
    }
    else
        return false;
}

void Catcher::CheckHp()
{
    if (hp <= 0)
    {
        Loose = true;
    }
}

void Catcher::GenerateBalls()
{ 
    float i = std::rand() % 360;
    float angle = i * gce::PI / 180;
    float x = std::sin(angle) * radius;
    float z = std::cos(angle) * radius;
    gce::Vector3f32 newPos = { x, 10, z };
    sphere->SetPosition(newPos);
}

bool Catcher::BallCollideToPlayer()
{
    gce::Vector3f32 spherePos = sphere->GetPosition();
    gce::Vector3f32 playerPos = player->GetPosition();
    spherePos.x -= playerPos.x;
    spherePos.y -= playerPos.y;
    spherePos.z -= playerPos.z;

    if (spherePos.x <= 0.5f)
    {
        if (spherePos.y <= 0.5f)
        {
            if (spherePos.z <= 0.5f)
            {
                return true;
            }
        }
        else
            return false;
    }
    else
        return false;
}