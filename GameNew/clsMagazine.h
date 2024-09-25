#pragma once
#include <iostream>
#include "GameConfig.h"
#include "clsRandom.h"
using namespace std;

class clsMagazine
{

private:
    class Node;
    float* _ObjectX;
    float* _ObjectY;
    char _BULLET_SHAPE;
    wstring* _Map;
    float _SPEED;
    int _TotalBulletsWasShots;
    bool _Ishoot;

    void _InsertBulletIntoMag(float x, float y)
    {
        Node* NewBullet = new Node();

        NewBullet->x = x;
        NewBullet->y = y;

        NewBullet->next = _Magazine_Coordinates;

        _Magazine_Coordinates = NewBullet;

        ++_TotalBullets;
    }

    void _DeleteABulletFromMagazine(float BulletX, float BulletY)
    {
        if (_Magazine_Coordinates == nullptr) return;

        Node* Temp = _Magazine_Coordinates;

        if ((Temp->x == trunc(BulletX) && Temp->y == trunc(BulletY)))
        {
            if (Temp->next == NULL)
            {
                _Magazine_Coordinates = NULL;
                delete Temp;
                --_TotalBullets;
                return;
            }
            else if (Temp->next->next == NULL)
            {
                _Magazine_Coordinates = Temp->next;
                delete Temp;
                --_TotalBullets;
                return;
            }

            _Magazine_Coordinates = Temp->next;
            delete Temp;
            --_TotalBullets;
            return;
        }

        Node* Current = _Magazine_Coordinates;
        Node* Prev = _Magazine_Coordinates;

        while (Current->next != NULL)
        {
            Prev = Current;
            Current = Current->next;
        }

        if (Current == NULL) return;

        if (Current->next == NULL)
        {
            Prev->next = NULL;
        }
        else
        {
            Prev->next = Current->next;
        }

        delete Current;
        --_TotalBullets;
    }

    static void __DeleteABulletFromMagazine(Node*& Magazine, float BulletX, float BulletY)
    {
        if (Magazine == nullptr) return;

        Node* Temp = Magazine;

        if ((Temp->x == trunc(BulletX) && Temp->y == trunc(BulletY)))
        {
            if (Temp->next == NULL)
            {
                Magazine = NULL;
                delete Temp;
                return;
            }
            else if (Temp->next->next == NULL)
            {
                Magazine = Temp->next;
                delete Temp;
                return;
            }

            Magazine = Temp->next;
            delete Temp;
            return;
        }

        Node* Current = Magazine;
        Node* Prev = Magazine;

        while (Current->next != NULL)
        {
            Prev = Current;
            Current = Current->next;
        }

        if (Current == NULL) return;

        if (Current->next == NULL)
        {
            Prev->next = NULL;
        }
        else
        {
            Prev->next = Current->next;
        }

        delete Current;
    }

    void _PrepareBullet(const float* ObjectX, const float* ObjectY, float ShotSide = 1.0f)
    {
        if (ShotSide > 3)
            return;

        float BulletSpawnX = *ObjectX + (ShotSide);
        float BulletSpawnY = *ObjectY + 7;
        // <=> -1
        // \/-  0
        // <||=====> 1
        // \/-  2
        // <=>  3

        _InsertBulletIntoMag(BulletSpawnX, BulletSpawnY);
        _TotalBulletsWasShots++;
        bool s = true;
        _Ishoot = &s;
    }

    void _PrepareBullet()
    {
        _PrepareBullet(_ObjectX, _ObjectY);
    }

    void _Reset()
    {
        _TotalBulletsWasShots = 0;
        _Ishoot = false;
    }

protected:
    float _TotalBullets = 0.0f;

public:
    Node* _Magazine_Coordinates = nullptr;
    static class Node
    {
    public:
        float x;
        float y;
        Node* next;
    };

    clsMagazine(wstring* Map, float* ObjectX, float* ObjectY, char BULLET_SHAPE)
    {
        _Map = Map;
        _ObjectX = ObjectX;
        _ObjectY = ObjectY;
        _BULLET_SHAPE = BULLET_SHAPE;
    }

    void ShootABullet(const float* ObjectX, const float* ObjectY, float ShotSide = 1.0f)
    {
        _PrepareBullet(ObjectX, ObjectY, ShotSide);
    }

    void ShootABullet(float ShotSide = 1.0f)
    {
        _PrepareBullet(_ObjectX, _ObjectY, ShotSide);
    }

    void UpdatePlayerMagazine()
    {
        if (_Ishoot)
        {
            Node* Current = _Magazine_Coordinates;

            while (Current != nullptr)
            {
                if (Current->y + 1 != GameConfig::ScreenControl::nWidth)
                {

                    float BX = Current->x;
                    float BY = Current->y;

                    float Old_Bullet_Coordinates = BX * GameConfig::ScreenControl::nWidth + BY;
                    BY += _SPEED;
                    float New_Bullet_Coordinates = BX * GameConfig::ScreenControl::nWidth + BY;

                    (*_Map)[Old_Bullet_Coordinates] = GameConfig::Space;
                    (*_Map)[New_Bullet_Coordinates] = _BULLET_SHAPE;

                    Current->x = BX;
                    Current->y = BY;
                }
                else
                {
                    (*_Map)[Current->x * GameConfig::ScreenControl::nWidth + Current->y] = GameConfig::Space;

                    _DeleteABulletFromMagazine(Current->x, Current->y);

                    if (_Magazine_Coordinates != nullptr)
                    {
                        Current = _Magazine_Coordinates;
                        continue;
                    }

                    _Ishoot = false;
                    return;
                }

                Current = Current->next;
            }

        }
    }

    static void UpdateCurrentMagazine(Node*& Magazine, const float& EnemyX, const float& EnemyY, wstring& Map)
    {

        Node* temp = Magazine;
        while (temp != nullptr)
        {
            if (temp->x == EnemyX && temp->y == trunc(EnemyY))
            {
                Map[temp->x * GameConfig::ScreenControl::nWidth + temp->y] = GameConfig::Space;

                __DeleteABulletFromMagazine(Magazine, EnemyX, EnemyY);

                return;

            }
            temp = temp->next;
        }
    }

    float GetTotalBullets() const
    {
        return (_TotalBullets);
    }

    static void InsertBulletIntoMag(Node*& head, float x, float y)
    {
        Node* NewBullet = new Node();

        NewBullet->x = x;
        NewBullet->y = y;

        NewBullet->next = head;

        head = NewBullet;
    }

    static bool IsBulletHitTarget(const wstring& Map, float& X, float& Y, const float& TargetX, const float& TargetY, const char& TargetShape)
    {
        // Search in map of ship by ship Coordinates x, y to check if it's front face bullet or no.
     
        // [6 -] <->
        // [6 -] * ||
        // [6 -] < -- + )))))
        // [6 -] * ||
        // [6 -] < ->

        for (short i = -1; i < 7; i++)
        {
            if (Map[(TargetX + i) * GameConfig::ScreenControl::nWidth + (TargetY - 6)] == TargetShape)
            {
                X = TargetX + i;
                Y = TargetY - 6;
                return true;
            }
        }

        return false;
    }

    void Speed(const float& speed)
    {
        _SPEED = speed;
    }

    bool Ishoot()
    {
        return (_Ishoot);
    }

    int TotalBulletsWasShots() const
    {
        return _TotalBulletsWasShots;
    }

    //void UpdateEnemyMagazine(Node*& Magazine, wstring& Map)
//{
//    if (IsEnemyShoot)
//    {
//        Node* Current = Magazine;
//        while (Current != nullptr)
//        {
//            if (Current->y + 1 != (nWidth - nWidth) + 1)
//            {
//                float BX = Current->x;
//                float BY = Current->y;
//
//                float Old_Bullet_Coordinates = BX * nWidth + BY;
//                BY -= BULLET_SPEED;
//                float New_Bullet_Coordinates = BX * nWidth + BY;
//
//                Map[Old_Bullet_Coordinates] = ' ';
//                Map[New_Bullet_Coordinates] = PLAYER_BULLET_SHAPE;
//
//                Current->x = BX;
//                Current->y = BY;
//            }
//            else
//            {
//                Map[Current->x * nWidth + Current->y] = ' ';
//
//                DeleteABulletFromMagazine(Magazine, Current->x, Current->y);
//
//                if (Magazine != nullptr)
//                {
//                    Current = Magazine;
//                    continue;
//                }
//
//                IsEnemyShoot = false;
//                return;
//            }
//
//            Current = Current->next;
//        }
//
//    }
//}


    void Clear()
    {
        Node* Current = _Magazine_Coordinates;

        while (Current != nullptr)
        {
            float Bullet_Coordinates = Current->x * GameConfig::ScreenControl::nWidth + Current->x;

            (*_Map)[Bullet_Coordinates] = GameConfig::Space;

            Current->x = NULL, Current->x = NULL;
            Current = Current->next;
        }
        _Reset();
    }

};
