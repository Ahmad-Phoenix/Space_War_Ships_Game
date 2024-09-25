#pragma once
#include "clsMagazine.h"
#include "clsEnemyShip.h"
#include "clsShip.h"
#include "clsBackground.h"
#include "GameConfig.h"
#include "clsPowerUps.h"
#include "clsGameStatistics.h"

class clsGameFactory
{
public:

    static clsMagazine* CreateMagazine()
    {
        return new clsMagazine(&GameConfig::ScreenControl::Map, GameConfig::PlayerShip::fPlayerX, GameConfig::PlayerShip::fPlayerY, GameConfig::Bullet::BulletShape);
    }

    static clsShip* CreatePlayer(clsMagazine* Mag)
    {
        return new clsShip(Mag, GameConfig::PTR_Input, &GameConfig::ScreenControl::Map, GameConfig::PlayerShip::fPlayerX, GameConfig::PlayerShip::fPlayerY);
    }

    static clsEnemyShip* CreateEnemy(clsMagazine::Node*& EnemysShips_Coordinates, clsMagazine* Mag)
    {

        return new clsEnemyShip(Mag, GameConfig::PTR_Input, EnemysShips_Coordinates,
            GameConfig::PlayerShip::fPlayerX, GameConfig::PlayerShip::fPlayerY, &GameConfig::ScreenControl::Map);
    }

    static clsBackground* CreateStarsBackground(clsMagazine::Node*& Stars_CoordinatesBackGrounds)
    {

        return new clsBackground(Stars_CoordinatesBackGrounds, &GameConfig::ScreenControl::Map, GameConfig::BackGroundStarShape);
    }

    static clsPowerUps* RandomPowerUps()
    {
        return new clsPowerUps(GameConfig::PowerUps::SPEED, GameConfig::PowerUps::vRandom, &GameConfig::ScreenControl::Map, GameConfig::ScreenControl::nWidth);
    }

    static clsPowerUps* PowerUps(const char& Shape)
    {
        return new clsPowerUps(GameConfig::PowerUps::SPEED,  Shape, &GameConfig::ScreenControl::Map, GameConfig::ScreenControl::nWidth);
    }

    static clsGameStatistics* GameStatistics()
    {
        return new clsGameStatistics();
    }

};