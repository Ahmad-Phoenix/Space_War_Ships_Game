#pragma once
#include <iostream>
#include <string>
#include <wtypes.h>

using namespace std;

class clsScreenManagementBuffer
{
public:

    static void Render(const short& nHeight, const short& nWidth, wstring vMap, wchar_t* screen)
    {
        for (int x = 0; x < nHeight; x++)
            for (int y = 0; y < nWidth; y++)
                screen[x * nWidth + y] = vMap[x * nWidth + y];
    }

    static void CreateTextModeScreenBuffer(HANDLE& hConsole, DWORD& dwBytesWritten)
    {
        hConsole = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
        
        SetConsoleActiveScreenBuffer(hConsole);
    }

    static void BufferWriteOutPutHandle(const short& nScreenHeight, const short& nScreenWidth, HANDLE& hConsole, DWORD& dwBytesWritten, wchar_t* screen)
    {
        screen[nScreenWidth * nScreenHeight - 1] = '\0';
        WriteConsoleOutputCharacter(hConsole, screen, nScreenWidth * nScreenHeight, { 0,0 }, &dwBytesWritten);
        dwBytesWritten = 0;
    }

    static void EndTextModeScreenBuffer(HANDLE& hConsole)
    {
        CloseHandle(hConsole);
    }

};

