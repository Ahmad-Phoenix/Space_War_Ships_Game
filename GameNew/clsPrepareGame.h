#pragma once
#include <iostream>
#include "clsMagazine.h"
#include "clsEnemyShip.h"
#include "clsScreenManagementBuffer.h"
#include "clsGameFactory.h"
#include "clsInput.h"
#include "clsPowerUps.h"
#include "clsGameStatistics.h"

using namespace std;

class clsMapManagement
{
public:
    static void SetupMap()
    {
        GameConfig::ScreenControl::Map += L"                                                                                                                                                     ";
        GameConfig::ScreenControl::Map += L"                                                                                                                                                     ";
        GameConfig::ScreenControl::Map += L"                                                                                                                                                     ";
        GameConfig::ScreenControl::Map += L"                                                                                                                                                     ";
        GameConfig::ScreenControl::Map += L"                                                                                                                                                     ";
        GameConfig::ScreenControl::Map += L"                                                                                                                                                     ";
        GameConfig::ScreenControl::Map += L"                                                                                                                                                     ";
        GameConfig::ScreenControl::Map += L"                                                                                                                                                     ";
        GameConfig::ScreenControl::Map += L"                                                                                                                                                     ";
        GameConfig::ScreenControl::Map += L"                                                                                                                                                     ";
        GameConfig::ScreenControl::Map += L"                                                                                                                                                     ";
        GameConfig::ScreenControl::Map += L"                                                                                                                                                     ";
        GameConfig::ScreenControl::Map += L"                                                                                                                                                     ";
        GameConfig::ScreenControl::Map += L"                                                                                                                                                     ";
        GameConfig::ScreenControl::Map += L"                                                                                                                                                     ";
        GameConfig::ScreenControl::Map += L"                                                                                                                                                     ";
        GameConfig::ScreenControl::Map += L"                                                                                                                                                     ";
        GameConfig::ScreenControl::Map += L"                                                                                                                                                     ";
        GameConfig::ScreenControl::Map += L"                                                                                                                                                     ";
        GameConfig::ScreenControl::Map += L"                                                                                                                                                     ";
        GameConfig::ScreenControl::Map += L"                                                                                                                                                     ";
        GameConfig::ScreenControl::Map += L"                                                                                                                                                     ";
        GameConfig::ScreenControl::Map += L"                                                                                                                                                     ";
        GameConfig::ScreenControl::Map += L"                                                                                                                                                     ";
        GameConfig::ScreenControl::Map += L"                                                                                                                                                     ";
        GameConfig::ScreenControl::Map += L"                                                                                                                                                     ";
        GameConfig::ScreenControl::Map += L"                                                                                                                                                     ";
        GameConfig::ScreenControl::Map += L"                                                                                                                                                     ";
        GameConfig::ScreenControl::Map += L"                                                                                                                                                     ";
        GameConfig::ScreenControl::Map += L"                                                                                                                                                     ";
        GameConfig::ScreenControl::Map += L"                                                                                                                                                     ";
        GameConfig::ScreenControl::Map += L"                                                                                                                                                     ";
        GameConfig::ScreenControl::Map += L"                                                                                                                                                     ";
        GameConfig::ScreenControl::Map += L"                                                                                                                                                     ";
        GameConfig::ScreenControl::Map += L"                                                                                                                                                     ";
        GameConfig::ScreenControl::Map += L"                                                                                                                                                     ";
        GameConfig::ScreenControl::Map += L"                                                                                                                                                     ";
        GameConfig::ScreenControl::Map += L"                                                                                                                                                     ";
        GameConfig::ScreenControl::Map += L"                                                                                                                                                     ";
    }

};

class clsPrepareGame
{
private:

    enum _Running { eGameOver = 0, Running = 1 };
    short _GameStatus = _Running::Running;

     clsMagazine* Mag;
     clsShip* Player;
     clsEnemyShip* Enemy;
     clsBackground* Background;
     clsPowerUps* PowerUps;
     clsGameStatistics* GameStatistics;

    void _Prepare()
    {
        clsMagazine::Node* Magazine_CoordinatesEnemyShip = nullptr;
        clsMagazine::Node* Stars_CoordinatesBackGrounds = nullptr;
        clsMagazine::Node* EnemysShips_Coordinates = nullptr;
        clsMagazine::Node* Magazine_Coordinates = nullptr;

        clsRandom<short>::SrandSeed();

        clsBackground::InitializeObjectsInNode(Stars_CoordinatesBackGrounds, GameConfig::NumberOfStars);

        clsEnemyShip::InitializeEnemiesInNode(EnemysShips_Coordinates, GameConfig::EnemyShips::NumberOfEnemyShips);

        Mag = clsGameFactory::CreateMagazine();
        Player = clsGameFactory::CreatePlayer(Mag);
        Enemy = clsGameFactory::CreateEnemy(EnemysShips_Coordinates, Mag);
        Background = clsGameFactory::CreateStarsBackground(Stars_CoordinatesBackGrounds);
        PowerUps = clsGameFactory::RandomPowerUps();
        GameStatistics = clsGameFactory::GameStatistics();

        clsScreenManagementBuffer::CreateTextModeScreenBuffer(GameConfig::ScreenControl::hConsole, GameConfig::ScreenControl::dwBytesWritten);
        clsMapManagement::SetupMap();

        Background->Speed(GameConfig::SPEED_STARS_BACKGROUND);
        PowerUps->Speed(GameConfig::PowerUps::SPEED);
        Mag->Speed(GameConfig::Bullet::SPEED_BULLET);
        Player->Speed(GameConfig::PlayerShip::SPEED_PLAYER_SHIP);
        Enemy->Speed(GameConfig::EnemyShips::SPEED_ENEMY_SHIP);
    }

    void _Render()
    {
        clsScreenManagementBuffer::Render(GameConfig::ScreenControl::nHeight, GameConfig::ScreenControl::nWidth, GameConfig::ScreenControl::Map, GameConfig::ScreenControl::screen);
        swprintf_s(GameConfig::ScreenControl::screen, 40, L"PowerUps Time Left=%3.2f", PowerUps->Duration());
        clsScreenManagementBuffer::BufferWriteOutPutHandle(GameConfig::ScreenControl::nScreenWidth, GameConfig::ScreenControl::nScreenHeight, GameConfig::ScreenControl::hConsole, GameConfig::ScreenControl::dwBytesWritten, GameConfig::ScreenControl::screen);
        std::this_thread::sleep_for(std::chrono::milliseconds(8)); // Approx 60 FPS
    }

    bool _IsPlayerAlive()
    {
        if (Player->IsAlive())
        {
            _GameStatus = _Running::eGameOver;
            return true;
        }
        else
        {
            _GameStatus = _Running::Running;
            return false;
        }
    }
   
    void _HandlePowerUps()
    {
        bool IsReachTarget = PowerUps->IsReachTarget(*GameConfig::PlayerShip::fPlayerX, *GameConfig::PlayerShip::fPlayerY);
        if (PowerUps->ArePickUpSuperShoot())
        {
            Mag->ShootABullet(PowerUps->ActiveSuperShootPower());
        }
        else if (PowerUps->ArePickUpSuperSpeed())
        {
            Player->Speed(PowerUps->ActiveSuperSpeedPower());
        }
        else
        {
            Player->Speed(GameConfig::PlayerShip::SPEED_PLAYER_SHIP);
            _ActivePowerUps();
        }
    }
   
    void _ActivePowerUps()
    {

        if (PowerUps->IsActive())
        {
            PowerUps->Update();
        }
        else
        {
            PowerUps->GenerateRandomPowersUps();
        }

    }

    void _Input()
    {
        GameConfig::Input = static_cast<char>(NULL);

        GameConfig::Input = clsInput::DynamicInput();

        GameConfig::PTR_Input = &GameConfig::Input;
    }

    void _Move()
    {
        Player->Move();

        if (Mag->Ishoot())
        {
            GameConfig::Bullet::Ishoot = true;
        }

        Background->Move();

        Enemy->Move();
    }

    void _UpdateGameStatistics()
    {
        GameStatistics->Retrieval();
        GameStatistics->SetShipsWasDestroyed(Enemy->TotalShipsWasDestroyed());
        GameStatistics->SetTotalPowerUpsPickups(PowerUps->TotalPowerUpsPickups());
        GameStatistics->SetBulletsWasShots(Mag->TotalBulletsWasShots());
        GameStatistics->SetDeathTimes(1);
        GameStatistics->Save();
    }

    void _Clear()
    {
        Enemy->Clear();
        Player->Clear();
        PowerUps->Clear();
        Background->Clear();
        Mag->Clear();
    }

    void _CloseBuffer()
    {
        clsScreenManagementBuffer::EndTextModeScreenBuffer(GameConfig::ScreenControl::hConsole);
    }

    bool Exit()
    {
        return (GameConfig::Input == clsInput::ExitEsc);
    }

public:

    clsPrepareGame()
    {
        GameConfig::ScreenControl::screen = new wchar_t[GameConfig::ScreenControl::nScreenWidth * GameConfig::ScreenControl::nScreenHeight];
        GameConfig::ScreenControl::hConsole = nullptr;
        GameConfig::ScreenControl::dwBytesWritten = 0;
        GameConfig::PowerUps::X = 0.0f;
        GameConfig::PowerUps::Y = 0.0f;
        GameConfig::Bullet::SPEED_BULLET = 1.0f;
        GameConfig::Bullet::BulletShape = 'o';
        GameConfig::Bullet::Ishoot = false;
        GameConfig::Bullet::IsEnemyShoot = false;
        
        GameConfig::PlayerShip::P_CenterWidth = GameConfig::ScreenControl::CenterWidth;
        GameConfig::PlayerShip::P_CenterHeight = GameConfig::ScreenControl::CenterHeight;
        GameConfig::PlayerShip::fPlayerX = &GameConfig::PlayerShip::P_CenterHeight;
        GameConfig::PlayerShip::fPlayerY = &GameConfig::PlayerShip::P_CenterWidth;
    }

    ~clsPrepareGame()
    {
        delete Mag;
        delete PowerUps;
        delete Player;
        delete Enemy;
        delete Background;
        delete GameStatistics;

        delete[] GameConfig::ScreenControl::screen;
    }

    void Start()
    {
        _Prepare();

        while (_GameStatus != _Running::eGameOver)
        {
            _Input();

            _Move();

            _HandlePowerUps();

            Mag->UpdatePlayerMagazine();

            _Render();

            if (_IsPlayerAlive() || Exit())
            {
                _UpdateGameStatistics();
                _Clear();
                _CloseBuffer();
                _GameStatus = _Running::eGameOver;
            }
        }
    }

};

