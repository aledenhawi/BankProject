#pragma once

#include <iostream>
#include <string>
#include "clsScreen.h"
#include "clsInputValidate.h"
#include <iomanip>
#include "clsDepositScreen.h"
#include "clsWithdrawScreen.h"
#include "clsTransferScreen.h"
#include "clsTransferLogScreen.h"
#include "clsTotalBalancesScreen.h"
using namespace std;


class clsTransactionsScreen : protected clsScreen
{
	static enum enTransactionsMenuOption {eDeposit = 1 , eWithdraw = 2 , eTotalBalances = 3 ,eTransfer = 4 ,eTransferLog = 5,eMainMenu = 6 };

	static short ReadTransactionMenuOption()
	{
		cout << setw(37) << " " << "Choose what do you want to do ? [1/6]" << endl;
		short Choice = clsInputValidate::ReadNumberBetween<short>(1, 6, "Number is not within the range , enter number between 1/6");
		return Choice;
	}

	static void GoBackToTransactionsMenu()
	{
		cout << "\nPress any key to go back to transactions menu.... ";
		system("pause>0");
		ShowTransactionsMenuScreen();
	}
	
	static void _ShowDepositScreen()
	{
		clsDepositScreen::ShowDepositClientScreen();
	}

	static void _ShowWithdrawScreen()
	{
		clsWithdrawScreen::ShowWithdrawClientScreen();
	}

	static void _ShowTotalBalancesScreen()
	{
		clsTotalBalancesScreen::ShowTotalBalances();
	}

	static void _ShowTransferScreen()
	{
		clsTransferScreen::ShowTransferScreen();
	}

	static void _ShowTransferLogScreen()
	{
		clsTransferLog::ShowTransferLogScreen();
	}

	static void PerformTransactionsScreen(enTransactionsMenuOption TransactionsMenuOption)
	{
	switch(TransactionsMenuOption)
	{
	case enTransactionsMenuOption::eDeposit :
		system("cls");
		_ShowDepositScreen();
		GoBackToTransactionsMenu();
		break;
	case enTransactionsMenuOption::eWithdraw:
		system("cls");
		_ShowWithdrawScreen();
		GoBackToTransactionsMenu();
		break;
	case enTransactionsMenuOption::eTotalBalances:
		system("cls");
		_ShowTotalBalancesScreen();
		GoBackToTransactionsMenu();
		break;
	case enTransactionsMenuOption::eTransfer:
		system("cls");
		_ShowTransferScreen();
		GoBackToTransactionsMenu();
		break;
	case enTransactionsMenuOption::eTransferLog:
		system("cls");
		_ShowTransferLogScreen();
		GoBackToTransactionsMenu();
		break;
	case enTransactionsMenuOption::eMainMenu:
		break;
	}
	}
public:

	static void ShowTransactionsMenuScreen()
	{
		if (!_CheckAccessRights(clsBankUser::enPermissions::pTransactionsMenu))
		{
			return;
		}
		system("cls");
		_DrawScreenHeader("Transactions Screen");
		cout << setw(37) << " " << "=============================================\n";
		cout << setw(37) << " " << "              Transactions Menu                 \n";
		cout << setw(37) << " " << "=============================================\n";
		cout << setw(37) << " " << "[1] Deposit.\n";
		cout << setw(37) << " " << "[2] Withdraw. \n";
		cout << setw(37) << " " << "[3] TotalBalances.\n";
		cout << setw(37) << " " << "[4] Transfer.\n";
		cout << setw(37) << " " << "[5] Transfer Log.\n";
		cout << setw(37) << " " << "[6] Main Menu.\n";
		cout << setw(37) << " " << "=============================================\n";

		PerformTransactionsScreen(enTransactionsMenuOption(ReadTransactionMenuOption()));
	}

};

