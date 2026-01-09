#pragma once

#include <iostream>
#include <string>
#include "clsScreen.h"
#include "clsInputValidate.h"
#include <iomanip>
#include "clsClientListScreen.h"
#include "clsAddNewClientScreen.h"
#include "clsDeleteClientScreen.h"
#include "clsUpdateClientScreen.h"
#include "clsFindClientScreen.h"
#include "clsTransactionsScreen.h"
#include "clsManageUsersScreen.h"
#include "clsLoginRegisterScreen.h"
#include "Global.h"
#include "clsCurrencyExchangeMainScreen.h";

using namespace std;

class clsMainScreen : protected clsScreen
{

protected:
	enum enMainMenuOptions { eClientsList = 1, eAddNew = 2, eDelete = 3, eUpdate = 4, eFindClient = 5,
		eTransactions = 6, eManageUsers = 7, eLoginRegister = 8, eCurrencyExchange = 9 , eLogout = 10};

	static void _GoBackToMainMenu()
	{
		cout << "\nPress any key to go back to main menu....";
		system("pause>0");
		ShowMainMenuScreen();
	}

	static short _ReadMainMenuOption()
	{
		cout << setw(37) << " " << "Choose what do you want to do ? [1/10]" << endl;
		short Choice = clsInputValidate::ReadNumberBetween<short>(1, 10 , "Invalid choice , enter Number Between 1 to 10 !");
		return Choice;
	}

	static void _ShowAllClientsScreen()
	{
		clsClientListScreen::ShowClientList();
	}

	static void _ShowAddNewScreen()
	{
		clsAddNewClientScreen::ShowAddNewClientScreen();
	}

	static void _ShowDeleteClientScreen()
	{
		clsDeleteClientScreen::ShowDeleteClientScreen();
	}

	static void _ShowUpdateClientScreen()
	{
		clsUpdateClientScreen::ShowUpdateClientScreen();
	
	}

	static void _ShowFindClientScreen()
	{
		clsFindClientScreen::ShowFindClientScreen();
	}

	static void _ShowTransactionsScreen()
	{
		clsTransactionsScreen::ShowTransactionsMenuScreen();
	}

	static void _ShowManageUsersScreen()
	{
		clsManageUsersScreen::ShowManageUserScreen();
	}

	static void _Logout()
	{
		CurrentUser = clsBankUser::Find("", "");
	}

	static void _ShowLoginRegisterScreen()
	{
		clsLoginRegisterScreen::ShowLoginRegisterScreen();
	}

	static void _ShowCurrencyExchangeMainScreen()
	{
		clsCurrencyExchangeMainScreen::ShowCurrencyExchangeMainScreen();
	}

	static void _PerformMainMenuOption(enMainMenuOptions MainMenuOption)
	{
	switch(MainMenuOption)
	{
	case enMainMenuOptions::eClientsList:
		system("cls");
		_ShowAllClientsScreen();
		_GoBackToMainMenu();
		break;
	case enMainMenuOptions::eAddNew:
		system("cls");
		_ShowAddNewScreen();
		_GoBackToMainMenu();
		break;
	case enMainMenuOptions::eDelete:
		system("cls");
		_ShowDeleteClientScreen();
		_GoBackToMainMenu();
		break;
	case enMainMenuOptions::eUpdate:
		system("cls");
		_ShowUpdateClientScreen();
		_GoBackToMainMenu();
		break;
	case enMainMenuOptions::eFindClient:
		system("cls");
		_ShowFindClientScreen();
		_GoBackToMainMenu();
		break;
	case enMainMenuOptions::eTransactions:
		system("cls");
		_ShowTransactionsScreen();
		_GoBackToMainMenu();
		break;
	case enMainMenuOptions::eManageUsers:
		system("cls");
		_ShowManageUsersScreen();
		_GoBackToMainMenu();
		break;
	case enMainMenuOptions::eLoginRegister:
		system("cls");
		_ShowLoginRegisterScreen();
		_GoBackToMainMenu();
		break;
	case enMainMenuOptions::eCurrencyExchange:
		system("cls");
		_ShowCurrencyExchangeMainScreen();
		_GoBackToMainMenu();
	case enMainMenuOptions::eLogout:
		system("cls");
		_Logout();
		break;
	}
	}

    public:

	static void ShowMainMenuScreen()
	{
		system("cls");
		_DrawScreenHeader("     Main Screen");
		cout << setw(37) << " " << "=============================================\n";
		cout << setw(37) << " " << "                    Main Menu                 \n";
		cout << setw(37) << " " << "=============================================\n";
		cout << setw(37) << " " << "[1] Show Clients List.\n";
		cout << setw(37) << " " << "[2] Add New Client. \n";
		cout << setw(37) << " " << "[3] Delete Client.\n";
		cout << setw(37) << " " << "[4] Update Client Info.\n";
		cout << setw(37) << " " << "[5] Find Client.\n";
		cout << setw(37) << " " << "[6] Transaction.\n";
		cout << setw(37) << " " << "[7] Manage Users.\n";
		cout << setw(37) << " " << "[8] Login Register.\n";
		cout << setw(37) << " " << "[9] Currency Exchange.\n";
		cout << setw(37) << " " << "[10] Logout.\n";
		cout << setw(37) << " " << "=============================================\n";
		_PerformMainMenuOption((enMainMenuOptions)_ReadMainMenuOption());
	}

};

