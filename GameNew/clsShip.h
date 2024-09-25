#pragma once
#include <iostream>
#include <set>
#include <vector>
#include "GameConfig.h"
#include "clsRandom.h"

using namespace std;

class clsShip
{
private:
    char* _Input;
    float* _X;
    float* _Y;

   // <=>
   // \ / -
   // <||=====>
   // \ / -
   // <=>
    vector<wstring> Ship = { L"<=>\\/-<||=====>\\/-<=>" };

    enum Keys { KeyUp = 72, KeyRight = 77, KeyDown = 80, KeyLeft = 75, KeyShootF = 70 };

    bool _IsCollision()
    {
        switch (*_Input)
        {
        case Keys::KeyUp: {

            return (static_cast<short>(*_X - 1) > 0) ? false : true;

            break;
        }

        case Keys::KeyRight: {

            return (static_cast<short>(*_Y + 1) < GameConfig::ScreenControl::nWidth) ? false : true;

            break;
        }

        case Keys::KeyDown: {

            return (static_cast<short>(*_X + 1) < GameConfig::ScreenControl::nHeight) ? false : true;

            break;

        }

        case Keys::KeyLeft: {

            return (static_cast<short>(*_Y - 1) > 0) ? false : true;

            break;
        }
        }

    }

    void _InputHandle(const char& _Input, float& _fPlayerX, float& _fPlayerY)
    {
        switch (_Input)
        {
            case Keys::KeyUp: {

                if (!_IsCollision())
                    _fPlayerX -= _SPEED;

                break;
            }

            case Keys::KeyRight: {

                if (!_IsCollision())
                    if (!(_fPlayerY >= GameConfig::ScreenControl::CenterWidth))
                        _fPlayerY += _SPEED;

                break;
            }

            case Keys::KeyDown: {

                if (!_IsCollision())
                    _fPlayerX += _SPEED;

                break;

            }

            case Keys::KeyLeft: {

                if (!_IsCollision())
                    _fPlayerY -= _SPEED;

                break;
            }

            case Keys::KeyShootF: {
                _Mag->ShootABullet();

                break;
            }
        }

    }

    bool _CheckShipBoundary()
    {
       //  -1
        // <=>  + 5
        // \ / - + 5
        // <||=====> + 5
        // \ / - + 5
        // <=> + 5
        //  +
        //  5

        char IsEnemyShip;
        set<decltype(IsEnemyShip)> invalidShapes = 
        {
            GameConfig::BackGroundStarShape,
            GameConfig::Space,
            GameConfig::PowerUps::SuperShotShape,
            GameConfig::PowerUps::SuperSpeedShape,
            GameConfig::Bullet::BulletShape
        };

        uint8_t ShipBoundary = 5;
        for (uint8_t Front = 0; Front <= ShipBoundary; Front++)
        {
            IsEnemyShip = (*_Map)[(uint8_t)(*_X + Front) * GameConfig::ScreenControl::nWidth + (uint8_t)*_Y + 5];

            if (invalidShapes.find(IsEnemyShip) == invalidShapes.end()) 
                return true;
        }

        ShipBoundary = 3;
        for (uint8_t UP = 0; UP < ShipBoundary; UP++)
        {
            IsEnemyShip = (*_Map)[(uint8_t)(*_X + -1) * GameConfig::ScreenControl::nWidth + (uint8_t)*(_Y + UP)];
            
            if (invalidShapes.find(IsEnemyShip) == invalidShapes.end())
                return true;
        }

        for (uint8_t Down = 0; Down < ShipBoundary; Down++)
        {
            IsEnemyShip = (*_Map)[(uint8_t)(*_X + 5) * GameConfig::ScreenControl::nWidth + (uint8_t)*(_Y + Down)];
            
            if (invalidShapes.find(IsEnemyShip) == invalidShapes.end())
                return true;
        }

        return false;
    }

    void _Reset()
    {
        _IsAlive = false;
        _Input = nullptr;
        _X = nullptr;
        _Y = nullptr;
    }

protected:
    wstring* _Map;
    float _SPEED;
    bool _IsAlive;
    clsMagazine* _Mag;

    void _DrawBattleShip(const short& ShipShape, vector<wstring>& Ship, wstring*& Map, const float& X, const float& Y)
    {
        short ShipShapeParts = 0;


        for (short i = 0; i < 3; i++)
            (*Map)[(short)(X - 1) * GameConfig::ScreenControl::nWidth + (short)(Y + i)] = Ship.at(ShipShape).at(ShipShapeParts++);

        for (short i = 0; i < 3; i++)
            (*Map)[(short)(X)*GameConfig::ScreenControl::nWidth + (short)(Y + i)] = Ship.at(ShipShape).at(ShipShapeParts++);

        (*Map)[(short)(X + 1) * GameConfig::ScreenControl::nWidth + (short)(Y - 2)] = Ship.at(ShipShape).at(ShipShapeParts++);
        (*Map)[(short)(X + 1) * GameConfig::ScreenControl::nWidth + (short)(Y - 1)] = Ship.at(ShipShape).at(ShipShapeParts++);

        for (short i = 0; i < 7; i++)
            (*Map)[(short)(X + 1) * GameConfig::ScreenControl::nWidth + (short)(Y + i)] = Ship.at(ShipShape).at(ShipShapeParts++);

        for (short i = 0; i < 3; i++)
            (*Map)[(short)(X + 2) * GameConfig::ScreenControl::nWidth + (short)(Y + i)] = Ship.at(ShipShape).at(ShipShapeParts++);

        for (short i = 0; i < 3; i++)
            (*Map)[(short)(X + 3) * GameConfig::ScreenControl::nWidth + (short)(Y + i)] = Ship.at(ShipShape).at(ShipShapeParts++);

    }

    void _UpdateBattleShip(wstring*& Map, const float& X, float& Y)
    {

        char ClearPart = ' ';

        for (short i = 0; i < 3; i++)
            (*Map)[(short)(X - 1) * GameConfig::ScreenControl::nWidth + (short)(Y + i)] = ClearPart;

        for (short i = 0; i < 3; i++)
            (*Map)[(short)(X)*GameConfig::ScreenControl::nWidth + (short)(Y + i)] = ClearPart;

        (*Map)[(short)(X + 1) * GameConfig::ScreenControl::nWidth + (short)(Y - 2)] = ClearPart;
        (*Map)[(short)(X + 1) * GameConfig::ScreenControl::nWidth + (short)(Y - 1)] = ClearPart;

        for (short i = 0; i < 7; i++)
            (*Map)[(short)(X + 1) * GameConfig::ScreenControl::nWidth + (short)(Y + i)] = ClearPart;

        for (short i = 0; i < 3; i++)
            (*Map)[(short)(X + 2) * GameConfig::ScreenControl::nWidth + (short)(Y + i)] = ClearPart;

        for (short i = 0; i < 3; i++)
            (*Map)[(short)(X + 3) * GameConfig::ScreenControl::nWidth + (short)(Y + i)] = ClearPart;

    }

    void _UpdateStatues()
    {
        _IsAlive = _CheckShipBoundary();
    }

public:

    clsShip(clsMagazine* Mag, char* Input, wstring* Map, float* fPlayerX, float* fPlayerY)
    {
        _Mag = Mag;
        _Map = Map;
        _Input = Input;
        _X = fPlayerX;
        _Y = fPlayerY;
    };

    virtual void Move()
    {
        _UpdateBattleShip(_Map, *_X, *_Y);
        _InputHandle(*_Input, *_X, *_Y);
        _UpdateStatues();
        _DrawBattleShip(0, Ship, _Map, *_X, *_Y);
    }

    void Speed(const float& speed)
    {
        _SPEED = speed;
    }

    bool IsAlive() const
    {
        return (_IsAlive);
    }

    void SetAliveStatus(const bool& Status)
    {
        _IsAlive = Status;
    }

    void Clear()
    {
        _UpdateBattleShip(_Map, *_X, *_Y);
        _Reset();
    }
};
