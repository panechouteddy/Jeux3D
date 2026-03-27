#include "pch.h"
#include "main.h"
#include "../ide/Tron/GameManager.h"
int main()
{
    GameManager* game = GameManager::GetInstance();  
    int choice = 0;

    while (choice == 0 || choice > 3)
    {
        std::cout << "Choisir le jeux : (Catcher : 1 , Shuffle : 2 ,Tron : 3 )" << std::endl;
        std::cin >> choice ;
    }
    game->Init(choice);                                    
    game->Run();                                     
    return 0;
}