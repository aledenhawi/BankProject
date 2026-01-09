#pragma once

#include <iostream>
#include <string>
#include <iomanip>
#include "Global.h"
#include "clsBankUser.h"
#include "clsDate.h"
using namespace std;

class clsScreen
{
protected :

	static void _DrawScreenHeader(string Title , string Subtitle = "")
	{
		cout << setw(37) << " " << "---------------------------------------------\n\n";
		cout << setw(37) << " " << "              " << Title << "\n";
		if(Subtitle != "")
		{
			cout << setw(37) << " " << "             " << Subtitle << "\n";
		}
		cout << "\n" << setw(37) << " " << "--------------------------------------------- \n\n";


		cout << setw(37) << " " << "User : " << CurrentUser.Username << endl;
		cout << setw(37) << " " << "Date : " << clsDate::DateToString(clsDate());
		cout << "\n\n\n";
	}

	static bool _CheckAccessRights(clsBankUser::enPermissions Permission)
	{
	if(CurrentUser.CheckAccessPermissions(Permission))
	{
		return true;
	}
	{
		cout << setw(37) << "" << "---------------------------------------------\n\n";
		cout << setw(37) << "" << "     Access Denied Contact Your Admin\n\n";
		cout << setw(37) << "" << "---------------------------------------------\n\n";
	}
	return false;
	}

};

