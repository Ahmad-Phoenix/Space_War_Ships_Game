#pragma once
#include <iostream>
#include <iomanip>
#include "clsGameFactory.h"
#include "clsGameStatistics.h"

using namespace std;
class clsGameStatisticsInfo
{
private:

	static void _PrintGameStatistics()
	{
		clsGameStatistics GameStatistics;
		GameStatistics.Retrieval();

		system("cls");
		cout << setw(31) << left << "" << "+----------------------------------------+\n";
		cout << setw(31) << left << "" << "|         GAME STATISTICS          |\n";
		cout << setw(31) << left << "" << "+----------------------------------------+\n";
		cout << setw(31) << left << "" << "| STATISTIC               |       VALUE  | \n";
		cout << setw(31) << left << "" << "+----------------------------------------+\n";
		cout << setw(31) << left << "" << "| ShipsWasDestroyed       |" << setw(13) << right << GameStatistics.GetShipsWasDestroyed() << left << " | \n";
		cout << setw(31) << left << "" << "+----------------------------------------+\n";		
		cout << setw(31) << left << "" << "| BulletsWasShots         |" << setw(13) << right << GameStatistics.GetBulletsWasShots() << left << " | \n";
		cout << setw(31) << left << "" << "+----------------------------------------+\n";		
		cout << setw(31) << left << "" << "| TotalPowerUpsPickups    |" << setw(13) << right << GameStatistics.GetTotalPowerUpsPickups() << left << " | \n";
		cout << setw(31) << left << "" << "+----------------------------------------+\n";		
		cout << setw(31) << left << "" << "| DeathTimes              |" << setw(13) << right << GameStatistics.GetDeathTimes() << left << " | \n";
		cout << setw(31) << left << "" << "+----------------------------------------+\n";

	}

public:

	static void ShowGameStatisticsScreen()
	{
		_PrintGameStatistics();
	}
};

