#pragma once

#include <iostream>
#include <string>
#include "clsScreen.h"
#include "clsMainScreen.h"
#include "Global.h"
#include <fstream>

using namespace std;

class clsLoginScreen : public clsScreen
{


	static bool _Login()
	{
		bool LoginFailed = false;
		string Username = "", Password = "";
		short LoginTrails = 3 ;
		do
		{	
			

			if (LoginFailed)
			{
				LoginTrails--;
				cout << "\nWrong Password/Username , try again : \n";
				cout << "You have " << LoginTrails << " trails left to login ." << endl;

				if (LoginTrails == 0)
				{
					cout << "\n\n\nyou are locked after 3 failed trails.\n\n\n";
					return false;
				}
			}

			cout << "\nEnter username : ";
			cin >> Username;

			cout << "\nEnter password : ";
			cin >> Password;

			CurrentUser = clsBankUser::Find(Username, Password);

			LoginFailed = CurrentUser.IsEmpty();

		} while (LoginFailed);
		CurrentUser.RegisterLogin();
		clsMainScreen::ShowMainMenuScreen();
		return true;
	}
	
public:


	static bool ShowLoginScreen()
	{
		system("cls");
		_DrawScreenHeader("   Login Screen");
		return _Login();
		
	}
};

