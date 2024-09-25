#pragma once
#include <iostream>
#include <vector>
#include <fstream>
#include "clsMainGameScreen.h"
using namespace std;

const string GameStatisticsFile = "GameStatisticsFile.txt";

class clsGameStatistics
{

private:

    struct stGameStatistics
    {
        int ShipsWasDestroyed = 0;
        int BulletsWasShots = 0;
        int TotalPowerUpsPickups = 0;
        int DeathTimes = 0;
    };

    stGameStatistics _GameStatistics;

    static vector <string> Split(string S1, const string& delim)
    {

        vector <string> vData;
        string Word = "";
        int pos = 0;

        while ((pos = S1.find(delim)) != string::npos)
        {
            Word = S1.substr(0, pos);

            if (Word != "")
            {
                vData.push_back(Word);
            }

            S1.erase(0, pos + delim.length());

        }

        if (S1 != "")
        {
            vData.push_back(S1);
        }

        return vData;
    }

    static stGameStatistics _ConvertGameStatisticsToRecord(const string& Line, const string& Seperator = "#")
    {
        stGameStatistics GameStatistics;

        vector <string> vGameStatistics = Split(Line, Seperator);

        GameStatistics.ShipsWasDestroyed = stoi(vGameStatistics.at(0));
        GameStatistics.BulletsWasShots = stoi(vGameStatistics.at(1));
        GameStatistics.TotalPowerUpsPickups = stoi(vGameStatistics.at(2));
        GameStatistics.DeathTimes = stoi(vGameStatistics.at(3));

        return GameStatistics;
    }

    static string _PrepareGameStatisticsToRecord(const stGameStatistics& GameStatistics, const string& Seperator = "#")
    {
        string Line = "";

        Line += to_string(GameStatistics.ShipsWasDestroyed) + Seperator;
        Line += to_string(GameStatistics.BulletsWasShots) + Seperator;
        Line += to_string(GameStatistics.TotalPowerUpsPickups) + Seperator;
        Line += to_string(GameStatistics.DeathTimes);

        return Line;
    }
    
    static bool _SaveGameStatisticsRecordToFile(const stGameStatistics& GameStatistics)
    {
        fstream File;
        File.open(GameStatisticsFile, ios::out);

        if (File.is_open())
        {
            File << _PrepareGameStatisticsToRecord(GameStatistics);
            File.close();
            return true;
        }
        else
        {
            cout << "\nFile Not Open\n";
            File.close();
            return false;
        }
    }

    stGameStatistics _RetrievalGameStatisticsFromRecord()
    {
        fstream File;
        File.open(GameStatisticsFile, ios::in);

        if (File.is_open())
        {
            string Line;
            while (getline(File, Line))
            {
                _GameStatistics = _ConvertGameStatisticsToRecord(Line);
            }
            File.close();
            return _GameStatistics;
        }
        else
        {
            cout << "\nFile Not Open\n";
            File.close();
        }
    }

public:

    clsGameStatistics()
    {
        stGameStatistics GameStatistics;
        GameStatistics = Retrieval();
    }

    void SetShipsWasDestroyed(const int& ShipsWasDestroyed) 
    {
        _GameStatistics.ShipsWasDestroyed += ShipsWasDestroyed;
    }

    void SetTotalPowerUpsPickups(const int& TotalPowerUpsPickups)
    {
        _GameStatistics.TotalPowerUpsPickups += TotalPowerUpsPickups;
    }

    void SetBulletsWasShots(const int& BulletsWasShots) 
    {
        _GameStatistics.BulletsWasShots += BulletsWasShots;
    }

    void SetDeathTimes(const int& DeathTimes) 
    {
        _GameStatistics.DeathTimes += DeathTimes;
    }

    int GetShipsWasDestroyed() const
    {
        return _GameStatistics.ShipsWasDestroyed;
    }

    int GetTotalPowerUpsPickups() const
    {
        return _GameStatistics.TotalPowerUpsPickups;
    }

    int GetBulletsWasShots() const
    {
        return _GameStatistics.BulletsWasShots;
    }

    int GetDeathTimes() const
    {
        return _GameStatistics.DeathTimes;
    }

    stGameStatistics GetGameStatistics() const
    {
        return _GameStatistics;
    }

    bool Save() const
    {
        return (_SaveGameStatisticsRecordToFile(_GameStatistics));
    }

    stGameStatistics Retrieval()
    {
        return _RetrievalGameStatisticsFromRecord();
    }

};

