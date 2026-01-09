#pragma once

#include <iostream>
#include <string>
#include "clsScreen.h"
#include <iomanip>
#include <vector>
#include "clsUtil.h"
#include "clsInputValidate.h"
#include "clsUsersListScreen.h"
#include "clsAddNewUserScreen.h"
#include "clsDeleteUserScreen.h"
#include "clsUpdateUserScreen.h"
#include "clsFindUserScreen.h"


using namespace std;

class clsManageUsersScreen : protected clsScreen
{
private:
	enum enManageUserMenuOptions {eUserList = 1 , eAddNewUser = 2 , eDeleteUser = 3 , eUpdateUser = 4 , eFindUser = 5 , eMainMenu};

	static void _GoBackToManageUsersMenu()
	{
		cout << "\n\nPress any key to go back to Manage Users Menu...";
		system("pause>0");
		ShowManageUserScreen();
	}

	static short _ReadManageUserOption()
	{
		cout << setw(37) << " " << "Choose what do you want to do ? [1/6]" << endl;
		short Choice = clsInputValidate::ReadNumberBetween<short>(1, 6, "Number is not within the range , enter number between 1 to 6 .");
		return Choice;
	}

	static void _ShowUsersListScreen()
	{
		clsUsersListScreen::ShowUsersList();
	}

	static void _ShowAddNewUserScreen()
	{
		clsAddNewUserScreen::ShowAddNewUserScreen();
	}

	static void _ShowDeleteUserScreen()
	{
		clsDeleteUserScreen::ShowDeleteUserScreen();
	}

	static void _ShowUpdateUserScreen()
	{
		//	cout << "Update user screen will be here soon.";
		clsUpdateUserScreen::ShowUpdateUserScreen();
	}

	static void _ShowFindUserScreen()
	{
		//cout << "Find user screen will be here soon.";
		clsFindUserScreen::ShowFindUserScreen();
	}

	static void _PerformManageUserOption(enManageUserMenuOptions ManageUserMenuOptions)
	{
	switch(ManageUserMenuOptions)
	{
	case enManageUserMenuOptions::eUserList :
		system("cls");
		_ShowUsersListScreen();
		_GoBackToManageUsersMenu();
		break;
	case enManageUserMenuOptions::eAddNewUser:
		system("cls");
		_ShowAddNewUserScreen();
		_GoBackToManageUsersMenu();
		break;
	case enManageUserMenuOptions::eDeleteUser:
		system("cls");
		_ShowDeleteUserScreen();
		_GoBackToManageUsersMenu();
		break;
	case enManageUserMenuOptions::eUpdateUser:
		system("cls");
		_ShowUpdateUserScreen();
		_GoBackToManageUsersMenu();
		break;
	case enManageUserMenuOptions::eFindUser:
		system("cls");
		_ShowFindUserScreen();
		_GoBackToManageUsersMenu();
		break;
	case enManageUserMenuOptions::eMainMenu:
		break;
	}
	}

public :

	static void ShowManageUserScreen()
	{
		if (!_CheckAccessRights(clsBankUser::enPermissions::pManageUsers))
		{
			return;
		}
		system("cls");
		_DrawScreenHeader("  Manage Users");
		cout << setw(37) << " " << "=============================================\n";
		cout << setw(37) << " " << "                Manage Users                 \n";
		cout << setw(37) << " " << "=============================================\n";
		cout << setw(37) << " " << "[1] Users List.\n";
		cout << setw(37) << " " << "[2] Add New User. \n";
		cout << setw(37) << " " << "[3] Delete User.\n";
		cout << setw(37) << " " << "[4] Update User.\n";
		cout << setw(37) << " " << "[5] Find User.\n";
		cout << setw(37) << " " << "[6] Main Menu.\n";
		cout << setw(37) << " " << "=============================================\n";
		_PerformManageUserOption((enManageUserMenuOptions)_ReadManageUserOption());
	}
};

