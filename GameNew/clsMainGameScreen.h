#pragma once
#include <iostream>
#include <vector>
#include <iomanip>
#include <chrono> 
#include <thread> 
#include "clsInput.h"
#include "clsPrepareGame.h"
#include "clsGameStatisticsInfo.h"
using namespace std;

class clsMainGameScreen
{
private:

    enum _Running { eGameOver = 0, Running = 1 };
    short _GameStatus = _Running::Running;

    char arrow = '<';

    vector <string> vMenu = { "NewGame <","GameStatistics  ","Exit  " };

    void _ShowNewGameScreen()
    {
        clsPrepareGame PrepareGame;
        PrepareGame.Start();
    }

    void _ShowGameStatisticsScreen()
    {
        clsGameStatisticsInfo::ShowGameStatisticsScreen();
    }

    void _ShowExitScreen(char Input)
    {
        // Get the handle of the console window
        HWND hwnd = GetConsoleWindow();

        // Send a message to close the console window
        PostMessage(hwnd, WM_CLOSE, 0, 0);
        
    }

    bool _HandleGameMenuAction(const short& Index, const clsInput::Keys& Input)
    {
        if (Input == clsInput::Keys::KeyEnter)
        {
            if (vMenu[Index] == vMenu[0])
            {
                _ShowNewGameScreen();
                system("pause>0");
                return true;
            }
            else if (vMenu[Index] == vMenu[1])
            {
                _ShowGameStatisticsScreen();
                system("pause>0");
                return true;
            }
            else
            {
                _ShowExitScreen(Input);
                system("pause>0");
                return true;
            }
            return false;
        }
        return false;
    }

    void _UpdateSelectedOption(const clsInput::Keys& Input, short& Index, vector<string>& vMenu, const char& PointerShape) const
    {
        if (vMenu.empty())
            return;

        short LastElement = vMenu.size() - 1;
        short FirstElement = 0;

        switch (Input)
        {
            case clsInput::Keys::KeyUp:
            {
                for (short up = 0; up < vMenu.size(); up++)
                {
                    if (vMenu.at(up).at(vMenu.at(up).size() - 1) == PointerShape)
                    {
                        if (up == FirstElement)
                        {
                            vMenu.at(FirstElement).at(vMenu.at(FirstElement).size() - 1) = ' ';
                            vMenu.at(LastElement).at(vMenu.at(LastElement).size() - 1) = PointerShape;
                            Index = up;
                            return;
                        }
                        else
                        {
                            vMenu.at(up).at(vMenu.at(up).size() - 1) = ' ';
                            vMenu.at(up - 1).at(vMenu.at(up - 1).size() - 1) = PointerShape;
                            Index = up - 1;
                            return;
                        }
                    }
                }
                break;
            }
            case clsInput::Keys::KeyDown:
            {
                for (short down = 0; down < vMenu.size(); down++)
                {
                    if (vMenu.at(down).at(vMenu.at(down).size() - 1) == PointerShape)
                    {
                        if (down == LastElement)
                        {
                            vMenu.at(down).at(vMenu.at(down).size() - 1) = ' ';
                            vMenu.at(FirstElement).at(vMenu.at(FirstElement).size() - 1) = PointerShape;
                            Index = down;
                            return;
                        }
                        else
                        {
                            vMenu.at(down).at(vMenu.at(down).size() - 1) = ' ';
                            vMenu.at(down + 1).at(vMenu.at(down + 1).size() - 1) = PointerShape;
                            Index = down + 1;
                            return;
                        }
                    }
                }
                break;
            }
        }
    }

    void _PrintMenu()
    {
        system("cls");
        for (int i = 0; i < vMenu.size(); i++)
        {
            cout << setw(50) << left << "" << vMenu[i] << endl;
        }
    }

    bool Exit(char Input)
    {
        return (static_cast<clsInput::Keys>(Input) == clsInput::ExitEsc);
    }

public:

    void MainGameMenuScreen()
    {

        short Index = 0;
        char Input = ' ';

        while (_GameStatus != _Running::eGameOver)
        {
     
            Input = clsInput::DynamicInput();

            _HandleGameMenuAction(Index, static_cast<clsInput::Keys>(Input));

            _UpdateSelectedOption(static_cast<clsInput::Keys>(Input), Index, vMenu, arrow);

            _PrintMenu();

            std::this_thread::sleep_for(std::chrono::milliseconds(1)); // Approx 60 FPS
        }

    }


};

