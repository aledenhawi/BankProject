#pragma once

#include <iostream>
#include <string>
#include "clsScreen.h"
#include <iomanip>
#include <vector>
#include "clsBankUser.h"
#include "clsInputValidate.h"

using namespace std;


class clsDeleteUserScreen : public clsScreen
{
private:

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

public:

	static void ShowDeleteUserScreen()
	{
		_DrawScreenHeader("Delete client screen");

		string Username = _ReadUsername();

		clsBankUser User = clsBankUser::Find(Username);

		_PrintUser(User);

		char Answer = 'y';

		cout << "\nAre you sure you want to delete this User ? [Y/N] ";
		cin >> Answer;

		if (tolower(Answer) == 'y')
		{
			if (User.Delete())
			{
				cout << "\nUser Deleted Successfully :-) \n";
				_PrintUser(User);
			}
			else
			{
				cout << "\nError delete user failed !!";
			}
		}

	}
	
};

