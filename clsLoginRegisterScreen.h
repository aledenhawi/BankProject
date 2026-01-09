#pragma once

#include <iostream>
#include <string>
#include "clsScreen.h"
#include <iomanip>
#include <vector>
#include "clsBankUser.h"

using namespace std;

class clsLoginRegisterScreen : public clsScreen
{

	static void _PrintLoginRegisterLine(clsBankUser::stLoginRegisterRecord LoginList)
	{
		cout << setw(20) << left << "" << left << setw(30) << "| " + LoginList.DateAndTime;
		cout << left << setw(15) << "| " + LoginList.Username;
		cout << left << setw(12) << "| " + LoginList.Password;
		cout << left << setw(12) << "| " + to_string(LoginList.Permissions);
	}

public:

	static void ShowLoginRegisterScreen()
	{
		if(!_CheckAccessRights(clsBankUser::enPermissions::pLoginRegister))
		{
			return;
		}

		vector <clsBankUser::stLoginRegisterRecord> vLoginList = clsBankUser::GetLoginList();;
	
		string Title = "Login Register List Screen";
		string Subtitle = "    (" + to_string(vLoginList.size()) + ") Record(s)";


		_DrawScreenHeader(Title, Subtitle);
		cout << setw(20) << left << "" << "---------------------------------------------------------------------------\n";
		cout << setw(20) << left << "" << left << setw(30) << "| Date/Time";
		cout << left << setw(15) << "| Username";
		cout << left << setw(12) << "| Password";
		cout << left << setw(5) << "| Permissions\n";
		cout << setw(20) << left << "" << "---------------------------------------------------------------------------\n\n";

		
		for (clsBankUser::stLoginRegisterRecord & L : vLoginList)
		{
			_PrintLoginRegisterLine(L);
			cout << endl;
		}


		cout <<"\n" << setw(20) << left << "" << "--------------------------------------------------------------------------\n";


	}
};

