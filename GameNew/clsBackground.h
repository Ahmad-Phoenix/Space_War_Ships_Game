#pragma once
#include "GameConfig.h"
#include "clsEnemyShip.h"
#include "clsShip.h"
#include "clsRandom.h"

using namespace std;

class clsBackground
{
private:
    clsMagazine::Node* _ObjectType;
    wstring* _Map;
    wchar_t _shape;
    float _SPEED;
    const short _Spawn = -100;


    void _UpdateBackground()
    {
        clsMagazine::Node* temp_ObjectType = _ObjectType;

        while (temp_ObjectType != nullptr)
        {

            if (temp_ObjectType->y >= (GameConfig::ScreenControl::nWidth - GameConfig::ScreenControl::nWidth) + 1)
            {
                (*_Map)[temp_ObjectType->x * GameConfig::ScreenControl::nWidth + temp_ObjectType->y] = ' ';
                temp_ObjectType->y -= _SPEED;
                (*_Map)[temp_ObjectType->x * GameConfig::ScreenControl::nWidth + temp_ObjectType->y] = _shape;
            }
            else
            {
                (*_Map)[temp_ObjectType->x * GameConfig::ScreenControl::nWidth + temp_ObjectType->y] = ' ';
                clsRandom<short>::_GenerateRandomObject(temp_ObjectType->x, temp_ObjectType->y, *_Map, _shape, _Spawn);
            }

            temp_ObjectType = temp_ObjectType->next;
        }
    }

    void _Reset()
    {
        _Map = nullptr;
    }

public:

    clsBackground(clsMagazine::Node* ObjectType, wstring* Map, const wchar_t& shape)
    {
        _ObjectType = ObjectType;
        _Map = Map;
        _shape = shape;
    }

    void Move()
    {
        _UpdateBackground();
    }

    static void InitializeObjectsInNode(clsMagazine::Node*& ObjectType, short Size)
    {
        if (Size <= 0)
            return;
        else
            for (short OT = 1; OT <= Size; OT++)
                clsMagazine::InsertBulletIntoMag(ObjectType, 0.0f, 0.0f);

    }

    void Speed(const float& speed)
    {
        _SPEED = speed;
    }


    void Clear()
    {
        clsMagazine::Node* tempObjectType = _ObjectType;

        while (tempObjectType != nullptr)
        {
            float EnemyX = tempObjectType->x, EnemyY = tempObjectType->y;

            (*_Map)[tempObjectType->x * GameConfig::ScreenControl::nWidth + tempObjectType->y] = ' ';

            tempObjectType->x = 0.0f, tempObjectType->y = 0.0f;
            tempObjectType = tempObjectType->next;
        }
        _Reset();
    }
};
