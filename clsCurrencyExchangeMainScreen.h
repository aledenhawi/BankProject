#pragma once
#include <iostream>
#include <string>
#include "clsScreen.h"
#include "clsInputValidate.h"
#include <iomanip>
#include "clsCurrenciesListScreen.h"
#include "clsFindCurrencyScreen.h"
#include "clsUpdateCurrencyRateScreen.h"
#include "clsCurrencyCalculatorScreen.h"

using namespace std;

class clsCurrencyExchangeMainScreen : protected clsScreen
{
	protected:
	enum enCurrenciesMainMenuOptions {eCurrenciesList = 1, eFindCurrency = 2, eUpdateRate = 3, eCurrencyCalculator = 4, eMainMenu = 5	};

	static void _GoBackTCurrencyExchangeMenu()
		{
			cout << "\n\n\n\nPress any key to go back to currency exchange menu ....";
			system("pause>0");
			ShowCurrencyExchangeMainScreen();
		}

	static short _ReadCurrencyExchangeMenuOption()
		{
			cout << setw(37) << " " << "Choose what do you want to do ? [1/5]" << endl;
			short Choice = clsInputValidate::ReadNumberBetween<short>(1, 5, "Invalid choice , enter Number Between 1 to 5 !");
			return Choice;
		}

	static void _ShowCurrenciesListScreen()
	{
		//cout << "Currencies List Screen Will Be Here Soon ...";
		clsCurrenciesListScreen::ShowLoginRegisterScreen();
	}

	static void _ShowFindCurrencyScreen()
	{
		//cout << "Find Currency Screen Will Be Here Soon ...";
		clsFindCurrencyScreen::ShowFindCurrencyScreen();
	}

	static void _ShowUpdateRateScreen()
	{
	//	cout << "Update Rate Screen Will Be Here Soon ...";
		clsUpdateCurrencyRateScreen::ShowUpdateCurrencyRateScreen();
	}

	static void _ShowCurrencyCalculatorScreen()
	{
		//cout << "Currency Calculator Screen Will Be Here Soon ...";
		clsCurrencyCalculatorScreen::ShowCurrencyCalculatorScreen();
	}

	static void _PerformCurrenciesMainMenuOption(enCurrenciesMainMenuOptions CurrencyExchangeMenuOption)
	{
		switch (CurrencyExchangeMenuOption)
		{
		case enCurrenciesMainMenuOptions::eCurrenciesList:
			system("cls");
			_ShowCurrenciesListScreen();
			_GoBackTCurrencyExchangeMenu();
			break;
		case enCurrenciesMainMenuOptions::eFindCurrency:
			system("cls");
			_ShowFindCurrencyScreen();
			_GoBackTCurrencyExchangeMenu();
			break;
		case enCurrenciesMainMenuOptions::eUpdateRate:
			system("cls");
			_ShowUpdateRateScreen();
			_GoBackTCurrencyExchangeMenu();
			break;
		case enCurrenciesMainMenuOptions::eCurrencyCalculator:
			system("cls");
			_ShowCurrencyCalculatorScreen();
			_GoBackTCurrencyExchangeMenu();
			break;
		case enCurrenciesMainMenuOptions::eMainMenu:
			break;
		}
	}

	public:

		static void ShowCurrencyExchangeMainScreen()
		{
			system("cls");
			_DrawScreenHeader("Currency Exchange Menu Screen");
			cout << setw(37) << " " << "=============================================\n";
			cout << setw(37) << " " << "           Currency Exchange Menu                  \n";
			cout << setw(37) << " " << "=============================================\n";
			cout << setw(37) << " " << "[1] Currencies List.\n";
			cout << setw(37) << " " << "[2] Find Currency. \n";
			cout << setw(37) << " " << "[3] Update Rate.\n";
			cout << setw(37) << " " << "[4] Currency Calculator.\n";
			cout << setw(37) << " " << "[5] Main Menu.\n";
			cout << setw(37) << " " << "=============================================\n";
			_PerformCurrenciesMainMenuOption((enCurrenciesMainMenuOptions)_ReadCurrencyExchangeMenuOption());
		}

};

