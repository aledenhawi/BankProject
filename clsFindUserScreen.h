#pragma once

#include <iostream>
#include <string>
#include "clsScreen.h"
#include "clsInputValidate.h"
#include <iomanip>
#include "clsBankUser.h"

using namespace std;

class clsFindUserScreen : protected clsScreen
{
private:

	static void _PrintUser(clsBankUser User)
	{
		cout << "------------------------------";
		cout << "\n        Client Card           ";
		cout << "\n------------------------------";
		cout << "\nFirst Name  : " << User.FirstName;
		cout << "\nLast Name   : " << User.LastName;
		cout << "\nFull Name   : " << User.FullName();
		cout << "\nEmail       : " << User.Email;
		cout << "\nPhone       : " << User.Phone;
		cout << "\nUsername    : " << User.Username;
		cout << "\nPassword    : " << User.Password;
		cout << "\nPermissions : " << User.Permissions;
		cout << "\n------------------------------\n";

	}

	static string _ReadUsername()
	{
		string Username;

		cout << "Please enter user username : ";
		Username = clsInputValidate::ReadString();

		while (!clsBankUser::IsUserExist(Username))
		{
			cout << "Username is not exist , try to enter a valid one : ";
			Username = clsInputValidate::ReadString();
		}
		return Username;
	}

public:

	static void ShowFindUserScreen()
	{
		_DrawScreenHeader("Find user screen");
		string Username = _ReadUsername();

		clsBankUser User = clsBankUser::Find(Username);

		if (!User.IsEmpty())
		{
			cout << "\nUser Found :)\n\n";
			_PrintUser(User);
		}
		else
		{
			cout << "\nUser is not Found :(\n\n";
		}
	}


};

