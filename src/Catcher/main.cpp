#include "pch.h"
#include "lib/Inputs/InputsMethods.h"
#include "lib/Geometries/Geometries.h"
#include "lib/Camera.h"
#include "lib/Texture.h"
#include "lib/Window.h"
#include "lib/Geometries/Geometry.h"
#include "lib/Text.h"
#include <chrono>
#include <math.h>
#include <cstdlib>
#include <string>
void Gravity(sr::Sphere* sphere, float dt)
{
    float x = sphere->GetPosition().x;
    float y = sphere->GetPosition().y;
    float z = sphere->GetPosition().z;
    y -= 2.0f * dt;
    sphere->SetPosition({ x, y,z });
}
bool GroundCollider(sr::Sphere* sphere)
{
    float y = sphere->GetPosition().y;
    if (y <= 0)
    {
        return true;
    }
}
void GenerateBalls(sr::Sphere* sphere, sr::Cube* cube)
{
    float i = std::rand() % 360;
    float radius = 4;
    float angle = i * gce::PI / 180;
    float x = std::sin(angle) * radius;
    float z = std::cos(angle) * radius;
    gce::Vector3f32 sphereNewPosition({ x,10,z });
    sphere->SetPosition(sphereNewPosition);
    cube->SetPosition(sphereNewPosition);

}
bool BallCollideToPlayer(sr::Sphere* sphere, sr::Cube* cube)
{
    gce::Vector3f32 spherePosition = sphere->GetPosition();
    gce::Vector3f32 cubePosition = cube->GetPosition();
    spherePosition.x -= cubePosition.x;
    spherePosition.y -= cubePosition.y;
    spherePosition.z -= cubePosition.z;

    if (spherePosition.x <= 0.5f)
    {
        if (spherePosition.y <= 0.5f)
        {
            if (spherePosition.z <= 0.5f)
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
void Catcher()
{
    sr::Window window(L"Test", 1920, 1080);

    sr::Camera camera(sr::CameraType::PERSPECTIVE);
    camera.SetPosition({ 13.0f, 18.0f, -9.0f });
    camera.SetRotation({ 45.0f, -40.0f, 0.0f });
    camera.SetFOV(gce::PI / 4.0f);
    camera.SetFarPlane(500.0f);
    camera.SetNearPlane(0.001f);

    sr::Texture texture("res/Textures/uv.png");
    sr::Text HpText(L"HP");
    HpText.SetPosition({ 0, 0 });
    sr::Cube floor;
    floor.SetTexture(texture);
    floor.SetPosition({ 0.0f, 0.0f, 0.0f });
    floor.SetScale({ 10.0f, 0.1f, 10.0f });

    sr::Cube trace;
    trace.SetColor({ 0.0f, 1.0f, 0.0f });
    trace.SetScale({ 0.1f, 18.0f, 0.1f });

    sr::Cube player;
    player.SetColor({ 0.0f, 1.0f, 0.0f });
    player.SetPosition({ 0.0f, 0.5f, -4.0f });
    player.SetScale({ 1.0f, 1.0f, 1.0f });

    sr::Sphere sphere;
    sphere.SetColor({ 0.0f, 1.0f, 0.0f });
    sphere.SetScale({ 0.5f, 0.5f, 0.5f });

    sr::Text ScoreText(L"Score");
    ScoreText.SetPosition({ 500.0f, 200.0f });

    GenerateBalls(&sphere, &trace);

    float32 testf = 0.0f;
    int hp = 3;
    int score = 0;
    float Dt = 0.0f;
    float radius = 4;
    float cameraRadius = 18;
    using namespace std::chrono;
    steady_clock::time_point lastTime = steady_clock::now();

    float i = 180;
    while (window.IsOpen())
    {
        steady_clock::time_point currentTime = steady_clock::now();
        duration<float> deltatime = duration_cast<duration<float>>(currentTime - lastTime);
        lastTime = currentTime;
        Dt = deltatime.count();
        HpText.SetText(std::wstring(L"HP : ") + std::to_wstring(hp));
        ScoreText.SetText(std::to_wstring(score));
        window.Begin(camera);
        window.Draw(trace);
        window.Draw(sphere);
        window.Draw(floor);
        window.Draw(player);
        window.DrawText(ScoreText);
        window.DrawText(HpText);
        window.End();
        window.Display();
        Gravity(&sphere, Dt);
        float angle = i * gce::PI / 180;
        float x = std::sin(angle) * radius;
        float z = std::cos(angle) * radius;
        float camX = std::sin(angle) * cameraRadius;
        float camZ = std::cos(angle) * 9;
        if (sr::GetKey(sr::Keyboard::D))
        {
            i--;
            if (i < 0)
            {
                i = 360;
            }
        }
        if (sr::GetKey(sr::Keyboard::Q))
        {
            i++;
            if (i > 360)
            {
                i = 0;
            }
        }
        player.SetPosition({ x, 0.5f,z });
        camera.SetPosition({ camX, 18 ,camZ });

        gce::Vector3f32 dir = { -camX, -18.0f, -camZ };
        float rotate_y = atan2(dir.x, dir.z) * 180.0f / gce::PI;
        float rotate_x = -atan2(dir.y, sqrt(dir.x * dir.x + dir.z * dir.z)) * 180.0f / gce::PI;
        camera.SetRotation({ rotate_x, rotate_y, 0.0f });
        if (GroundCollider(&sphere) == true)
        {
            GenerateBalls(&sphere, &trace);
            hp -= 1;
        }
        if (BallCollideToPlayer(&sphere, &player) == true)
        {
            GenerateBalls(&sphere, &trace);
            score += 100;
        }
        if (hp == 0)
        {
            window.End();
        }
    }
}
int main()
{
    Catcher();
    return 0;
}
