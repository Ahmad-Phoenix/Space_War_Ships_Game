#pragma once

#include <iostream> 
#include <vector>  
#include "GameConfig.h"
#include "clsShip.h"
#include "clsRandom.h"
#include "clsBackground.h"
using namespace std;

class clsEnemyShip : public clsShip
{
private:

    float* _EnemyX;
    float* _EnemyY;
    int _TotalShipsWasDestroyed;
    clsMagazine::Node* _Enemy;
    vector<wstring>* Ship = new vector<wstring>();

    void _ClearPositIon(wstring*& Map, const float& EnemyX, float& EnemyY)
    {
        _UpdateBattleShip(Map, EnemyX, EnemyY);

        EnemyY -= _SPEED;
    }

    void _UpdatePosition(const short& ShipShape, vector<wstring>* Ship, wstring*& Map, const float& EnemyX, float& EnemyY)
    {

        _ClearPositIon(Map, EnemyX, EnemyY);

        _DrawBattleShip(ShipShape, *Ship, Map, EnemyX, EnemyY);

    }

    wstring _GenerateRandomEnemyShip(float& x, float& y)
    {

        clsRandom<short>::RandomXAndY(1.0, GameConfig::ScreenControl::nHeight - 1, GameConfig::ScreenControl::CenterWidth, GameConfig::ScreenControl::nWidth, x, y); // Initialize Enemy Ship Random Coordinates

        const wchar_t EnemyShape0[22] = 
           L"<->"
           L"*||"
           L"<--+)))))"
           L"*||"
           L"<->";

        const wchar_t Enemyshape1[22] = 
            L"<=="
            L"|_|"
            L"<==={==}>"
            L"|_|"
            L"<==";        
        
        const wchar_t Enemyshape2[22] =
            L"<+>"
            L"/ \\"
            L"<=*=*=*=>"
            L"\\ /"
            L"<+>";

        const wchar_t Enemyshape3[22] =
            L"[=]"
            L"_^_"
            L"-(-----)C"
            L"-v-"
            L"[=]";

        const size_t Ships = 4;
        const wstring arrShipShape[Ships] = { EnemyShape0, Enemyshape1, Enemyshape2, Enemyshape3 };
        short index = clsRandom<short>::RandomNumber(0, Ships - 1);

        return arrShipShape[index];
    }

    void _PrepareNewShip(float& EnemyX, float& EnemyY, wstring*& Map, const short& ShipShape)
    {
        _ClearPositIon(Map, EnemyX, EnemyY);

        clsRandom<short>::RandomXAndY(1.0, GameConfig::ScreenControl::nHeight - 1, GameConfig::ScreenControl::CenterWidth, GameConfig::ScreenControl::nWidth, EnemyX, EnemyY);

    }

    void _HandleShipMovementAndSpawning(float& EnemyX, float& EnemyY, wstring*& Map, vector<wstring>*& Ship, short& ShipShape)
    {

        bool IsShipWithinMapBoundary = (EnemyY >= (GameConfig::ScreenControl::nWidth - GameConfig::ScreenControl::nWidth) + 1);
        bool AreShipCoordinatesZero = (EnemyX <= 0.0f && EnemyY <= 0.0f);

        if (IsShipWithinMapBoundary)
        {
            _UpdatePosition(ShipShape, Ship, Map, EnemyX, EnemyY);
        }
        else if (AreShipCoordinatesZero)
        {
            Ship->push_back(_GenerateRandomEnemyShip(EnemyX, EnemyY));
        }
        else
        {
            _PrepareNewShip(EnemyX, EnemyY, Map, ShipShape);
        }

        ++ShipShape;
    }

    bool _ProcessEnemyHit(clsMagazine::Node**& TempMagazine, float& EnemyX, float& EnemyY, wstring*& Map, short& ShipShape)
    {

        bool AreShipCoordinatesGreaterThanZero = (EnemyX > 0.0f && EnemyY > 0.0f);

        if (AreShipCoordinatesGreaterThanZero && GameConfig::Bullet::Ishoot)
        {
            float X, Y;
            if (clsMagazine::IsBulletHitTarget(GameConfig::ScreenControl::Map, X, Y, EnemyX, EnemyY, GameConfig::Bullet::BulletShape))
            {
                clsMagazine::UpdateCurrentMagazine(*TempMagazine, X, Y, GameConfig::ScreenControl::Map);
                _PrepareNewShip(EnemyX, EnemyY, _Map, ShipShape);
                _TotalShipsWasDestroyed++;
                return true;
            }
            return false;
        }
        return false;
    }

    void _DrawShip()
    {

        clsMagazine::Node* tempEnemy = _Enemy;
        clsMagazine::Node** TempMagazine = &_Mag->_Magazine_Coordinates;

        short ShipShape = 0;
        while (tempEnemy != nullptr)
        {
            float EnemyX = tempEnemy->x, EnemyY = tempEnemy->y;

            if (_ProcessEnemyHit(TempMagazine, EnemyX, EnemyY, _Map, ShipShape))
            {
                tempEnemy->x = EnemyX, tempEnemy->y = EnemyY;
                tempEnemy = tempEnemy->next;
                continue;
            }

            _HandleShipMovementAndSpawning(EnemyX, EnemyY, _Map, Ship, ShipShape);

            tempEnemy->x = EnemyX, tempEnemy->y = EnemyY;
            tempEnemy = tempEnemy->next;
        }
    }

    void _Reset()
    {
        //_EnemyX = nullptr;
        //_EnemyY = nullptr;
        _TotalShipsWasDestroyed = 0;
        delete Ship;
    }

public:

    clsEnemyShip(clsMagazine* Mag, char* Input, clsMagazine::Node* Enemy, float* fPlayerX, float* fPlayerY, wstring* Map)
        : clsShip(Mag, Input, Map, fPlayerX, fPlayerY)
    {
        _Mag = Mag;
        _Enemy = Enemy;
        _Map = Map;
    }

    void Move() override
    {
        _DrawShip();
    }

    static void InitializeEnemiesInNode(clsMagazine::Node*& EnemysShips_Coordinates, short NumberOfEnemyShips)
    {
        clsBackground::InitializeObjectsInNode(EnemysShips_Coordinates, NumberOfEnemyShips);
    }

    int TotalShipsWasDestroyed() const
    {
        return _TotalShipsWasDestroyed;
    }

    void Clear()
    {
        clsMagazine::Node* tempEnemy = _Enemy;

        while (tempEnemy != nullptr)
        {
            float EnemyX = tempEnemy->x, EnemyY = tempEnemy->y;

            _ClearPositIon(_Map, EnemyX, EnemyY);

            tempEnemy->x = 0.0f, tempEnemy->y = 0.0f;
            tempEnemy = tempEnemy->next;
        }
        _Reset();
    }
};
