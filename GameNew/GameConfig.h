#pragma once
#include <vector>
#include <string>
#include <wtypes.h>
using namespace std;

namespace GameConfig
{

	char Space = ' ';

	short NumberOfStars = 10;
	float SPEED_STARS_BACKGROUND = 2.2f;
	char BackGroundStarShape = '.';

	namespace PowerUps
	{
		float X = 0.0f;
		float Y = 0.0f;
		float SPEED = 1.0f;
		char SuperShotShape = 'B';
		char SuperSpeedShape = 'S';
		//char HealthShape = 'H';
		//char CoinsShape = 'C';
		//char CoinsShape = '$';
		const vector <char> vRandom = { SuperShotShape, SuperSpeedShape };

	}

	namespace EnemyShips
	{
		short NumberOfEnemyShips = 6;
		float SPEED_ENEMY_SHIP = 0.3f;
	}

	namespace Bullet
	{
		float SPEED_BULLET = 1.0f;
		char BulletShape = 'o';
		bool Ishoot = false;
		bool IsEnemyShoot = false;
	}

	namespace ScreenControl
	{
		const int nScreenWidth = 140;
		const int nScreenHeight = 34;
		const int nWidth = nScreenWidth;
		const int nHeight = nScreenHeight;
		HANDLE hConsole = nullptr;
		DWORD dwBytesWritten = 0;

		const float CenterWidth = static_cast<float>(nWidth) / 2;
		const float CenterHeight = static_cast<float>(nHeight) / 2;

		wstring Map;
		wchar_t* screen = nullptr;
	}

	namespace PlayerShip
	{
		float P_CenterWidth = ScreenControl::CenterWidth;
		float P_CenterHeight = ScreenControl::CenterHeight;
		float SPEED_PLAYER_SHIP = 1.0f;
		float* fPlayerX = &P_CenterHeight;
		float* fPlayerY = &P_CenterWidth;
	}

	char Input = 'd';
	char* PTR_Input = &Input;
}