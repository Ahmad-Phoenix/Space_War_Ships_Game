#pragma once
#include <ctime>
#include <cstdlib> 
using namespace std;

template <class T>
class clsRandom
{
public:

    static void SrandSeed()
    {
        srand(static_cast<unsigned>(time(NULL)));
    }

    static T RandomNumber(T From, T To)
    {
        int RandNum = rand() % (To - From + 1) + From;
        return static_cast<T>(RandNum);
    }

    static void RandomXAndY(const float& xFrom, const float& xTo, const float& yFrom, const float& yTo, float& x, float& y)
    {
        x = clsRandom<T>::RandomNumber(xFrom, xTo);
        y = clsRandom<T>::RandomNumber(yFrom, yTo);
    }

    static void _GenerateRandomObject(float& x, float& y, wstring& Map, const wchar_t& Object, const short& Spawn)
    {
        clsRandom<short>::RandomXAndY(1.0f, GameConfig::ScreenControl::nHeight - 1, GameConfig::ScreenControl::nScreenWidth, GameConfig::ScreenControl::nWidth - Spawn, x, y);

        Map[x * GameConfig::ScreenControl::nWidth + y] = Object;
    }

};
