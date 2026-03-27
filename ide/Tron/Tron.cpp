#include "pch.h"
#include "Tron.h"
#include "MenuScene.h"

void Tron::Init()
{
    camera = new sr::Camera(sr::CameraType::PERSPECTIVE);
    camera->SetPosition({ 0.0f, 105.0f, 0.0f });
    camera->SetRotation({ 90.0f, 0.0f, 0.0f });
    camera->SetFOV(gce::PI / 6.0f);
    camera->SetFarPlane(500.0f);
    camera->SetNearPlane(0.001f);

    floor = new sr::Cube();
    floor->SetPosition({ 0.0f, 0.0f, 0.0f });
    floor->SetScale({ 50.0f, 0.1f, 50.0f });
    floor->SetColor(ConvertColor(9, 0, 77));

    wallright = new sr::Cube();
    wallright->SetPosition({ 25.0f , 0.0f, 0.0f });
    wallright->SetScale({ 50.0f, 0.1f, 50 });
    wallright->SetRotation({ 90.0f, 0.0f, 90.0f });
    wallright->SetColor(ConvertColor(9, 0, 77));

    wallleft = new sr::Cube();
    wallleft->SetPosition({ -25.0f , 0.0f, 0.0f });
    wallleft->SetScale({ 50, 0.1f, 50 });
    wallleft->SetRotation({ 90.0f, 0.0f, 90.0f });
    wallleft->SetColor(ConvertColor(9, 0, 77));

    WallBot = new sr::Cube();
    WallBot->SetPosition({ 0.0f, 0.0f, -25.0f });
    WallBot->SetScale({ 50.0f, 0.1f, 50.0f });
    WallBot->SetRotation({ 90.0f, 0.0f, 0.0f });
    WallBot->SetColor(ConvertColor(9, 0, 77));


    WallTop = new sr::Cube();
    WallTop->SetPosition({ 0.0f, 0.0f, 25.0f });
    WallTop->SetScale({ 50.0f, 0.1f, 50.0f });
    WallTop->SetRotation({ 90.0f, 0.0f, 0.0f });
    WallTop->SetColor(ConvertColor(9, 0, 77));

    Player = new sr::Cube();
    Player->SetPosition({ 0.0f, 4.0f, 0.0f });
    Player->SetScale({ 1.5f, 1.5f, 1.5f });
    Player->SetRotation({ 00.0f, 0.0f, 0.0f });
    Player->SetColor(ConvertColor(0, 0, 255));


    for (int i = 0;i < 6;i++)
    {
        PlayerFollow[i] = new::sr::Cube();
        PlayerFollow[i]->SetPosition({ 0.0f, 4.0f, 0.0f });
        PlayerFollow[i]->SetScale({ 1.0f, 1.0f, 1.0f });
        PlayerFollow[i]->SetRotation({ 00.0f, 0.0f, 0.0f });
        PlayerFollow[i]->SetColor(ConvertColor(0, 229, 255));

        P_direction_Follow[i] = new gce::Vector2f32({ 0,0 });
    }
   
    for (int i = 0;i < 4;i++)
    {
        if (i < 2)
        {
            StaticWall[i] = new::sr::Cube();
            StaticWall[i]->SetScale({ 17.0f, 1.1f, 20.0f });
            StaticWall[i]->SetRotation({ 90.0f, 0.0f, 90.0f });
            StaticWall[i]->SetColor(ConvertColor(200, 0, 0));
        }
        else
        {
            StaticWall[i] = new::sr::Cube();
            StaticWall[i]->SetScale({ 25.0f, 1.1f, 20.0f });
            StaticWall[i]->SetRotation({ 90.0f, 0.0f, 0.0f });
            StaticWall[i]->SetColor(ConvertColor(200, 0, 0));
        }
    }
    for (int x = 0;x < 2; x++)
    {
        Ennemi[x] = new sr::Cube();
        Ennemi[x]->SetScale({ 1.5f, 1.5f, 1.5f });
        Ennemi[x]->SetRotation({ 00.0f, 0.0f, 0.0f });
        Ennemi[x]->SetColor(ConvertColor(247, 0, 0));
        if (x == 0)
        {
            Ennemi[x]->SetPosition({ -22.0f, 4.0f ,-22.0f });
        }
        else
        {
            Ennemi[x]->SetPosition({ 22.0f, 4.0f ,22.0f });
        }
        float E_x = Ennemi[x]->GetPosition().x;
        float E_z = Ennemi[x]->GetPosition().z;
        for (int y = 0;y < 6;y++)
        {
  

                EnnemiFollow[x][y] = new::sr::Cube();
            EnnemiFollow[x][y]->SetPosition({ E_x, 4.0f, E_z });
            EnnemiFollow[x][y]->SetScale({ 1.0f, 1.0f, 1.0f });
            EnnemiFollow[x][y]->SetRotation({ 00.0f, 0.0f, 0.0f });
            EnnemiFollow[x][y]->SetColor(ConvertColor(227, 17, 81));
            P_direction_Follow[x][y] = {0,0};
        }

    }

    HpText = new sr::Text(L"Hp");
    ScoreText  = new sr::Text(L"score");
    HpText->SetPosition({ 0, 0 });
    ScoreText->SetPosition({ 700, 0 });

    PauseText = new sr::Text(L"PAUSE");
    PauseText->SetPosition({ 700,200 });
    QuitText = new sr::Text(L"Appuyer sur ENTRER pour changer de jeux");
    QuitText->SetPosition({ 500, 400 });

    StaticWall[0]->SetPosition({ 0,0,-18 });
    StaticWall[1]->SetPosition({ 15,0, 18 });
    StaticWall[2]->SetPosition({ 3,0, 10 });
    StaticWall[3]->SetPosition({ 0 ,0, -10 });
    P_direction = { 1, 0 };
    Hp = 5;
    Score = 0;
    Pause = false;
    Alive = true;


}

void Tron::Update(float dt)
{

    CheckAlive();
    pauseGame();
    if (Pause == false)
    {
        if (Alive == true)
        {
            MovePlayer(dt);
            ennemiMoove(dt);
            CheckCollison();
            WallCheck();
            CollideWithFollow();
            CollideWithEnnemi();
        }
    }
    QuitScene();

}

void Tron::CheckCollison()
{
    gce::Vector3f32 PlayerPosition = Player->GetPosition();

    if (PlayerPosition.x >= 25 ||PlayerPosition.x <= -25 )
    {
        Player->SetPosition({ 0,4.0f,0 });
        Hp -= 1;
    }
    else if (PlayerPosition.z >= 25 || PlayerPosition.z <= -25)
    {
        Player->SetPosition({ 0,4.0f,0 });
        Hp -= 1;
    }
}

void Tron::Render(sr::Window& window)
{
    HpText->SetText(L"HP : " + std::to_wstring(Hp));
    ScoreText->SetText(L"SCORE : " + std::to_wstring(Score));
    window.Begin(*camera);
    if (Alive == true)
    {
        if (Pause == true)
        {
            window.DrawText(*PauseText);
        }   
        window.Draw(*floor);
        window.Draw(*wallleft);
        window.Draw(*wallright);
        window.Draw(*WallBot);
        window.Draw(*WallTop);
        window.Draw(*Player);
        window.DrawText(*HpText);

        for (int i = 0; i < 4;i++)
        {
            window.Draw(*StaticWall[i]);
        }
        for (int i = 0; i < 6;i++)
        {
            window.Draw(*PlayerFollow[i]);
        }
        for (int x = 0; x < 2; x++)
        {
            window.Draw(*Ennemi[x]);

            for (int y = 0; y < 6;y++)
            {
                window.Draw(*EnnemiFollow[x][y]);
            }
        }
    }
    window.DrawText(*ScoreText);
    if (Alive == false)
    {
        window.DrawText(*QuitText);
    }
    window.End();
    window.Display();  
}

void Tron::KeypadDetect()
{
    if (sr::GetKey(sr::Keyboard::Z))
    {
        if(P_direction.y == 0)
        P_direction = { 0,1 };
       
    }
    else if (sr::GetKey(sr::Keyboard::S))
    {
        if (P_direction.y == 0)
        P_direction = { 0,-1 };
    }
    else if (sr::GetKey(sr::Keyboard::Q))
    {
        if (P_direction.x == 0)
        P_direction = { -1,0 };
    }
    else if (sr::GetKey(sr::Keyboard::D))
    {
        if (P_direction.x == 0)
        P_direction = { 1,0 };
    }

}

void Tron::FollowMove(float dt)
{

    for (int i = 5; i > 0; --i)
    {
        gce::Vector3f32 current = PlayerFollow[i]->GetPosition();
        gce::Vector3f32 target = PlayerFollow[i - 1]->GetPosition();
        PlayerFollow[i]->SetPosition(current + (target - current) * dt * 10);
    }

    gce::Vector3f32 current0 = PlayerFollow[0]->GetPosition();
    gce::Vector3f32 target0 = Player->GetPosition();
    PlayerFollow[0]->SetPosition(current0 + (target0 - current0) * dt * 10);
}
void Tron::MovePlayer(float dt)
{
    FollowMove(dt);
    KeypadDetect();
    float x = P_direction.x * dt * 10;
    float z = P_direction.y * dt * 10;

    Player->Translate({ x, 0, z });
}

gce::Vector3f32 Tron::ConvertColor(float r, float g, float b)
{
    gce::Vector3f32 color = { r / 255,g / 255,b / 255 };

    return color;
}

void Tron::WallCheck()
{
    gce::Vector3f32 WallStaticPosition;
    gce::Vector3f32 PlayerPosition = Player->GetPosition();
    gce::Vector3f32 WallMoovablePosition;
    float Scale ;
    for (int i = 0;i < 4; i++)
    {
     WallStaticPosition = StaticWall[i]->GetPosition();
     if (i <2)
     { 
         if (PlayerPosition.x <= WallStaticPosition.x + 0.5f && PlayerPosition.x >= WallStaticPosition.x - 0.5f)
         {
             Scale = StaticWall[i]->GetScale().z /2;
             if (PlayerPosition.z <= WallStaticPosition.z + Scale && PlayerPosition.z >= WallStaticPosition.z - Scale)
             {
                 Player->SetPosition({ 0,4.0f,0 });
                 Hp -= 1;
             }
         }
     }
     else
     {
         if (PlayerPosition.z <= WallStaticPosition.z + 0.5f && PlayerPosition.z >= WallStaticPosition.z - 0.5f)
         {
             Scale = StaticWall[i]->GetScale().x / 2;
             if (PlayerPosition.x <= WallStaticPosition.x + Scale && PlayerPosition.x >= WallStaticPosition.x - Scale)
             {
                 Player->SetPosition({ 0,4.0f,0 });
                 Hp -= 1;
             }
         }
     }   
    }
}

void Tron::ennemiMoove(float dt)
{
    float speed = 6.0f;
    float offset = 10.0f;
    gce::Vector3f32 playerPos = Player->GetPosition();

    for (int i = 0; i < 2; i++)
    {
        gce::Vector3f32 enemyPos = Ennemi[i]->GetPosition();
        gce::Vector3f32 dir = playerPos - enemyPos;

        float length = sqrt(dir.x * dir.x + dir.z * dir.z);
        if (length > 0.001f)
        {
            dir.x /= length;
            dir.z /= length;
        }
        float angleOffset = (i == 0 ? -90.0f : 90.0f) * (3.1415926f / 180.0f);
        float sinA = sin(angleOffset);
        float cosA = cos(angleOffset);

        gce::Vector3f32 sideDir;
        sideDir.x = dir.x * cosA - dir.z * sinA;
        sideDir.z = dir.x * sinA + dir.z * cosA;

        gce::Vector3f32 finalDir = dir * 0.7f + sideDir * 0.3f;

        float fLen = sqrt(finalDir.x * finalDir.x + finalDir.z * finalDir.z);
        if (fLen > 0.001f)
        {
            finalDir.x /= fLen;
            finalDir.z /= fLen;
        }

        gce::Vector3f32 move = { finalDir.x * dt * speed, 0, finalDir.z * dt * speed };
        Ennemi[i]->Translate(move);
    }
    EnnemiFollowMove(dt);
}

void Tron::EnnemiFollowMove(float dt)
{
    for (int x = 0; x < 2; x++)
    {
        gce::Vector3f32 current0 = EnnemiFollow[x][0]->GetPosition();
        gce::Vector3f32 target0 = Ennemi[x]->GetPosition();
        EnnemiFollow[x][0]->SetPosition(current0 + (target0 - current0) * dt * 6);

        for (int y = 5; y > 0; --y)
        {
            gce::Vector3f32 current = EnnemiFollow[x][y]->GetPosition();
            gce::Vector3f32 target = EnnemiFollow[x][y - 1]->GetPosition();
            EnnemiFollow[x][y]->SetPosition(current + (target - current) * dt * 6);
        }
    }
}

void Tron::CollideWithFollow()
{
    float hitRadius = 1.0f; 

    for (int x = 0; x < 2; x++)
    {
        gce::Vector3f32 enemyPos = Ennemi[x]->GetPosition();

        for (int y = 0; y < 6; y++)
        {
            gce::Vector3f32 followPos = PlayerFollow[y]->GetPosition();

            float dx = enemyPos.x - followPos.x;
            float dz = enemyPos.z - followPos.z;
            float dist2 = dx * dx + dz * dz;

            if (dist2 < hitRadius * hitRadius)
            {
                if (x == 0)
                {
                    Ennemi[0]->SetPosition({ -22.0f, 4.0f ,-22.0f });

                    for (int y = 0; y < 6; y++)
                    {
                        EnnemiFollow[0][y]->SetPosition({ -22.0f, 4.0f ,-22.0f });
                        
                    }
                    Score += 200;
                }
                else
                {
                    Ennemi[1]->SetPosition({ 22.0f, 4.0f ,22.0f });
                    
                    for (int y = 0; y < 6; y++)
                    {
                        EnnemiFollow[1][y]->SetPosition({ 22.0f, 4.0f ,22.0f });
                        
                    }
                    Score += 200;   
                }

            }
        }
    }
}

void Tron::CollideWithEnnemi()
{
    float hitRadius = 1.0f;

    for (int x = 0; x < 2; x++)
    {
        gce::Vector3f32 PlayerPos = Player->GetPosition();

        for (int y = 0; y < 6; y++)
        {
            gce::Vector3f32 followPos = EnnemiFollow[x][y]->GetPosition();

            float dx = PlayerPos.x - followPos.x;
            float dz = PlayerPos.z - followPos.z;
            float dist2 = dx * dx + dz * dz;

            if (dist2 < hitRadius * hitRadius)
            {
                Player->SetPosition({ 0,4.0f,0 });
                Hp -= 1;
            }
        }
    }
}

void Tron::pauseGame()
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

void Tron::CheckAlive()
{
    if (Hp <= 0)
    {
        Alive = false;
    }
    else
        return;
}

void Tron::QuitScene()
{
    if (sr::GetKey(sr::Keyboard::ENTER))
    {
        
        m_sceneManager->SetScene((std::make_shared<MenuScene>( m_sceneManager,window)));
    }
}

