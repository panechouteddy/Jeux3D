#include "pch.h"
#include "main.h"
#include "lib/Inputs/InputsMethods.h"
#include "lib/Geometries/Geometries.h"
#include "lib/Camera.h"
#include "lib/Texture.h"
#include "lib/Window.h"
#include "lib/Text.h"
#include <chrono>

void Setdirection(sr::Cylinder* ball, sr::Cube* Raquette, gce::Vector2f32* balldir)
{
    gce::Vector2f32 centreBalle = { ball->GetPosition().x+2 ,ball->GetPosition().z + 2 };
    gce::Vector2f32 centreObjet = { Raquette->GetPosition().x+2 ,Raquette->GetPosition().z+2 };
    centreObjet -= centreBalle;
    float v = std::sqrt(centreObjet.x * centreObjet.x + centreObjet.y * centreObjet.y);
    if (v != 0.f)
    {
        balldir->x = centreObjet.x / v;
        balldir->y = centreObjet.y / v;
    }
    else
    {
        balldir->x = 0.f;
        balldir->y = 0.f;
    }
}
bool ColideTop(sr::Cylinder* ball, sr::Cube* wall_top_left, gce::Vector2i32* trajectory)
{   
    gce::Vector3f32 ballPosition = ball->GetPosition();
    gce::Vector3f32 LeftWall = wall_top_left->GetPosition();

    ballPosition.z -=  LeftWall.z * -1 ;

    if (ballPosition.z <= 0.5f && ballPosition.z >= -0.5f)
    {
        if (ballPosition.x <= -5)
            return true;

        else if (ballPosition.x >= 5)
            return true;

        else
            return false;
    }
    else
        return false;
        
}
bool ColideBot(sr::Cylinder* ball, sr::Cube* wall_Down_left, gce::Vector2i32* trajectory)
{
    
    gce::Vector3f32 ballPosition = ball->GetPosition();
    gce::Vector3f32 LeftWall = wall_Down_left->GetPosition();

    ballPosition.z += LeftWall.z;

    if (ballPosition.z <= 0.5f && ballPosition.z >= - 0.5f)
    {
        if (ballPosition.x <= -5)
            return true;

        else if (ballPosition.x >= 5)
            return true;

        else
            return false;
    }
    else
        return false;
}
bool ColideLeft(sr::Cylinder* ball, sr::Cube* wall_left , gce::Vector2i32* trajectory)
{

    gce::Vector3f32 ballPosition = ball->GetPosition();
    gce::Vector3f32 LeftWall = wall_left->GetPosition();

    ballPosition.x -= LeftWall.x ;

    if (ballPosition.x <= 0.5f && ballPosition.x >= -0.5f)
    {
        return true;
    }
    else
        return false;
}
bool ColideRight(sr::Cylinder* ball, sr::Cube* wall_right, gce::Vector2i32* trajectory)
{
   // std::cout << " traj x : " << trajectory->x << " traj y :" << trajectory->y << std::endl;

    gce::Vector3f32 ballPosition = ball->GetPosition();
    gce::Vector3f32 RightWall = wall_right->GetPosition();

    ballPosition.x -= RightWall.x;


    if (ballPosition.x <= 0.5f && ballPosition.x >= - 0.5f)
    {
        return true;
    }
    else 
        return false;
}
bool ColidePalleteToPallet(sr::Cylinder* ball, sr::Cube* raquette)
{
    gce::Vector3f32 ballPosition = ball->GetPosition();
    gce::Vector3f32 raquettePosition = raquette->GetPosition();
    ballPosition.x -= raquettePosition.x;
    ballPosition.z -= raquettePosition.z;
    if (ballPosition.x <= 1.0f && ballPosition.x >= - 1.0f)
    {
        if (ballPosition.z <= 1.0f && ballPosition.z >=- 1.0f)
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
void Shuffle()
{
    float height = 1080;
    float width = 1920;
    //Window creation
    sr::Window window(L"Test", width, height);

    //Camera creation
    sr::Camera camera(sr::CameraType::PERSPECTIVE);
    camera.SetPosition({ 0.0f, 15.0f, -48.25f });
    camera.SetRotation({ 20.0f, 0.0f, 0.0f });
    camera.SetFOV(gce::PI / 6.0f);
    camera.SetFarPlane(500.0f);
    camera.SetNearPlane(0.001f);

    //Texture loading
    sr::Texture texture("res/Textures/uv.png");

    //Mesh creation
    sr::Cube floor;
    floor.SetPosition({ 0.0f, 0.0f, 0.0f });
    floor.SetScale({ 30.0f, 0.1f, 50.0f });
    floor.SetColor({ 1,1,1 });

    sr::Cube wallright;
    wallright.SetPosition({ 15.0f , 0.0f, 0.0f });
    wallright.SetScale({ 50.0f, 0.1f, 7.0f });
    wallright.SetRotation({ 90.0f, 0.0f, 90.0f });
    wallright.SetColor({ 1,0,0 });

    sr::Cube wallleft;
    wallleft.SetPosition({ -15.0f , 0.0f, 0.0f });
    wallleft.SetScale({ 50.0f, 0.1f, 7.0f });
    wallleft.SetRotation({ 90.0f, 0.0f, 90.0f });
    wallleft.SetColor({ 0,0,1 });
    sr::Cube WallUp;
    WallUp.SetPosition({ 0.0f, 2.0f, -25.0f });
    WallUp.SetScale({ 30.0f, 0.1f, 1.0f });
    WallUp.SetRotation({ 90.0f, 0.0f, 0.0f });
    WallUp.SetColor({ 0,0,1 });

    sr::Cube WallUp_right;
    WallUp_right.SetPosition({ 10.0f, -3.0f, -25.0f });
    WallUp_right.SetScale({ 10.0f, 0.1f, 7.0f });
    WallUp_right.SetRotation({ 90.0f, 0.0f, 0.0f });
    WallUp_right.SetColor({ 0,0,1 });
    sr::Cube WallUp_left;
    WallUp_left.SetPosition({ -10.0f, -3.0f, -25.0f });
    WallUp_left.SetScale({ 10.0f, 0.1f, 7.0f });
    WallUp_left.SetRotation({ 90.0f, 0.0f, 0.0f });
    WallUp_left.SetColor({ 0,0,1 });

    sr::Cube WallDown;
    WallDown.SetPosition({ 0.0f, 2.0f, 25.0f });
    WallDown.SetScale({ 30.0f, 0.1f, 1.0f });
    WallDown.SetRotation({ 90.0f, 0.0f, 0.0f });
    WallDown.SetColor({ 1,0,0 });

    sr::Cube WallDown_right;
    WallDown_right.SetPosition({ 10.0f, -3.0f, 25.0f });
    WallDown_right.SetScale({ 10.0f, 0.1f, 7.0f });
    WallDown_right.SetRotation({ 90.0f, 0.0f, 0.0f });
    WallDown_right.SetColor({ 1,0,0 });

    sr::Cube WallDown_left;
    WallDown_left.SetPosition({ -10.0f, -3.0f, 25.0f });
    WallDown_left.SetScale({ 10.0f, 0.1f, 7.0f });
    WallDown_left.SetRotation({ 90.0f, 0.0f, 0.0f });
    WallDown_left.SetColor({ 1,0,0 });
   

    sr::Cylinder pallet;
    pallet.SetPosition({ 0.0f, 0.0f, 0.0f });
    pallet.SetScale({ 2.0f, 1.0f, 2.0f });
    pallet.SetRotation({ 0.0f, 0.0f, 0.0f });
    pallet.SetColor({ 0.0f, 0.0f, 0.0f });

    sr::Cube player;
    player.SetScale({ 2.0f, 2.0f, 2.0f });
    player.SetColor({ 0.0f, 0.0f, 1.0f });

    sr::Cube ennemi;
    ennemi.SetPosition({ 0,0, 15 });
    ennemi.SetScale({ 2.0f, 2.0f, 2.0f });
    ennemi.SetColor({ 1.0f, 0.0f, 0.0f });

    sr::Text ScoreText(L"Score");
    ScoreText.SetPosition({740.0f, 0.0f});

    sr::Text TimeText(L"Temp");
    TimeText.SetPosition({0.0f, 0.0f });

    int time = 0;
    int BlueScore = 0;
    int RedScore = 0;
    float chronometre = 120;
    gce::Vector2i32 mousedir({777, 536});
    sr::SetMousePosition({ mousedir });
    int dirb_x = 0;
    float b_x = pallet.GetPosition().x;
    float b_y = pallet.GetPosition().y;
    float middleX = 375;
    float middleY = 778;
    float p_Pos_X = (777 / middleY) *15 -15;
    float p_Pos_Z = (532-middleX+218)/(802-middleX+218) * - 25  ;
    player.SetPosition({ p_Pos_X , 0.0f, p_Pos_Z });
    gce::Vector2i32 BallTrajectory({ 0,0 });
    gce::Vector2f32 Balldirection({ 0,0 });
    float Dt = 0.0f;

    using namespace std::chrono;
    steady_clock::time_point lastTime = steady_clock::now();
    while (window.IsOpen())
    {
        steady_clock::time_point currentTime = steady_clock::now();
        duration<float> deltatime = duration_cast<duration<float>>(currentTime - lastTime);
        lastTime = currentTime;
        Dt = deltatime.count();

        ScoreText.SetText(std::to_wstring(BlueScore) + std::wstring(L" : ") + std::to_wstring(RedScore));
        TimeText.SetText(std::wstring(L"temp : ") + std::to_wstring(time));
        window.Begin(camera);
        window.Draw(WallUp);
        window.Draw(WallDown);
        window.Draw(wallright);
        window.Draw(wallleft);
        window.Draw(pallet);
        window.Draw(floor);
        window.Draw(player);
        window.Draw(ennemi);
        window.Draw(WallUp_right);
        window.Draw(WallUp_left);
        window.Draw(WallDown_right);
        window.Draw(WallDown_left);
        window.DrawText(TimeText);
        window.DrawText(ScoreText);
        window.End();
        window.Display();

       
        if (ColideTop(&pallet, &WallUp_left, &BallTrajectory))
        {
            BallTrajectory.y *= -1; 
        }


        if (ColideBot(&pallet, &WallDown_left, &BallTrajectory))
        {
            BallTrajectory.y *= -1; 
        }

        if (ColideRight(&pallet, &wallright, &BallTrajectory))
        {
            BallTrajectory.x *= -1; 
        }

        if (ColideLeft(&pallet, &wallleft, &BallTrajectory))
        {
            BallTrajectory.x *= -1; 
        }

        if (ColidePalleteToPallet(&pallet,&player)== true)
        {          
            if (player.GetPosition().x < pallet.GetPosition().x)
            {
                BallTrajectory.x = -1;
                std::cout << "  x : 1 " << std::endl;
            }
            else if (player.GetPosition().x > pallet.GetPosition().x)
            {
                BallTrajectory.x = -1;
                std::cout << "  x : -1 " << std::endl;
            }
            else if (player.GetPosition().x - pallet.GetPosition().x < 1.5f)
            {
                BallTrajectory.x = 0;
                std::cout << "  x : 0 " << std::endl;
            }
            else if (player.GetPosition().x - pallet.GetPosition().x > -1.5f)
            {
                BallTrajectory.x = 0;
                std::cout << "  x : 0 " << std::endl;
            }
            Setdirection(&pallet, &player, &Balldirection);
            BallTrajectory.y = -1;
        }
        if (ColidePalleteToPallet(&pallet, &ennemi) == true)
        {
            if (ennemi.GetPosition().x < pallet.GetPosition().x)
            {
                BallTrajectory.x = 1;
                std::cout << "  x : 1 " << std::endl;
            }
            else if (ennemi.GetPosition().x > pallet.GetPosition().x)
            {
                BallTrajectory.x = -1;
                std::cout << "  x : -1 " << std::endl;
            }
            else if (ennemi.GetPosition().x - pallet.GetPosition().x < 1.5f)
            {
                BallTrajectory.x = 0;
                std::cout << "  x : 0 " << std::endl;
            }
            else if (ennemi.GetPosition().x - pallet.GetPosition().x > -1.5f)
            {
                BallTrajectory.x = 0;
                std::cout << "  x : 0 " << std::endl;
            }
            Setdirection(&pallet, &player, &Balldirection);
            BallTrajectory.y = 1;
        }
        float b_x = pallet.GetPosition().x + Balldirection.x *Dt *13 *BallTrajectory.x;
        float b_z = pallet.GetPosition().z + Balldirection.y *Dt *13 *BallTrajectory.y;
        float e_x = ennemi.GetPosition().x + Balldirection.x * Dt * 7 * BallTrajectory.x;
        float e_z = ennemi.GetPosition().z + Balldirection.y * Dt * 7 * BallTrajectory.y;

        ennemi.SetPosition({ e_x,0,e_z });
        pallet.SetPosition({ b_x,0,b_z });

  
        float p_Pos_X = (mousedir.x / middleY) * 15 - 15;
        float p_Pos_Z = (mousedir.y - middleX + 218) / (802 - middleX + 218) * -25;
        player.SetPosition({ p_Pos_X , 0.0f, p_Pos_Z });
        chronometre -= 1* Dt;
        time = chronometre;
        if (pallet.GetPosition().z > 25)
        {
            BlueScore++;
            pallet.SetPosition({ 0,0,0 });
            BallTrajectory.x = 0;
            BallTrajectory.y = 0;
        }
        if (pallet.GetPosition().z < -25)
        {
            RedScore++;
            pallet.SetPosition({ 0,0,0 });
            BallTrajectory.x = 0;
            BallTrajectory.y = 0;
        }
        if (player.GetPosition().x < -15)
        {
            player.SetPosition({ -15,0.0f,player.GetPosition().z });
        }
        if (player.GetPosition().x > 15)
        {
            player.SetPosition({ 0.0f,0.0f,player.GetPosition().z });
        }
        if (player.GetPosition().z < -25)
        {
            player.SetPosition({ player.GetPosition().x,0.0f,-25 });
        }
        if (player.GetPosition().z >= 0)
        {
            player.SetPosition({ player.GetPosition().x,0.0f,-5 });
        }
        if (ennemi.GetPosition().x < -15)
        {
            ennemi.SetPosition({ -15,0.0f,ennemi.GetPosition().z });
        }
        if (ennemi.GetPosition().x > 15)
        {
            ennemi.SetPosition({ 0.0f,0.0f,ennemi.GetPosition().z });
        }
        if (ennemi.GetPosition().z < 25)
        {
            ennemi.SetPosition({ ennemi.GetPosition().x,0.0f, 25 });
        }
        if (ennemi.GetPosition().z >= 0)
        {
            ennemi.SetPosition({ ennemi.GetPosition().x,0.0f,5 });
        }
        if (RedScore == 5)
        {
            window.End();
        }
        if (BlueScore == 5)
        {
            window.End();
        }
        if (time < 0)
        {
            window.End();
        }
    }

}
int main()
{
    Shuffle();
    return 0;
}