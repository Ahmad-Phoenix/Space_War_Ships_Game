#pragma once
#include <conio.h>

class clsInput
{
public:
    enum Keys { KeyEnter = 13, KeyUp = 72, KeyRight = 77, KeyDown = 80, KeyLeft = 75, KeyShootF = 70, ExitEsc = 27 };

    static char DynamicInput()
    {
        return ((_kbhit()) ? _getch() : NULL);
    }

    static char NormalInput()
    {
        return _getch();
    }

};

