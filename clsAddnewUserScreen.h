#pragma once

#include <iostream>
#include <string>
#include "clsScreen.h"
#include <iomanip>
#include <vector>
#include "clsBankUser.h"
#include "clsInputValidate.h"

using namespace std;


class clsAddNewUserScreen : protected clsScreen
{
private:

	static short _ReadPermissionsToSet()
	{
		short Permissions = 0;

		char Answer = 'n';

		cout << "\nDo you want to give this user full access ? [Y/N] ";
		cin >> Answer;

		if (tolower(Answer) == 'y')
		{
			return -1;
		}

		cout << "\nChoose what permissions do you want to give : " << endl;

		cout << "\n1) Access to Clients list ? [Y/N] ";
		cin >> Answer;
		if (tolower(Answer) == 'y')
		{
			Permissions = clsBankUser::pClientsList;
		}

		cout << "\n2) Access to add new client screen ? [Y/N] ";
		cin >> Answer;

		if (tolower(Answer) == 'y')
		{
			Permissions |= clsBankUser::pAddnewClient;
		}

		cout << "\n3) Access to delete screen ? [Y/N] ";
		cin >> Answer;

		if (tolower(Answer) == 'y')
		{
			Permissions |= clsBankUser::pDeleteClient;
		}

		cout << "\n4) Access to update screen ? [Y/N] ";
		cin >> Answer;

		if (tolower(Answer) == 'y')
		{
			Permissions |= clsBankUser::pUpdateClient;
		}

		cout << "\n5) Access to find client screen ? [Y/N] ";
		cin >> Answer;

		if (tolower(Answer) == 'y')
		{
			Permissions |= clsBankUser::pFindClient;
		}

		cout << "\n6) Access to transactions screen ? [Y/N] ";
		cin >> Answer;

		if (tolower(Answer) == 'y')
		{
			Permissions |= clsBankUser::pTransactionsMenu;
		}

		cout << "\n7) Access to manage users screen ? [Y/N] ";
		cin >> Answer;
		if (tolower(Answer) == 'y')
		{
			Permissions |= clsBankUser::pManageUsers;
		}
		cout << "\n7) Access to Login Register screen ? [Y/N] ";
		cin >> Answer;
		if (tolower(Answer) == 'y')
		{
			Permissions |= clsBankUser::pLoginRegister;
		}
		return Permissions;

	}

	static void _ReadUserInfo(clsBankUser& User)
	{
		cout << "\nEnter First Name  : ";
		User.FirstName = clsInputValidate::ReadString();

		cout << "\nEnter Last Name   : ";
		User.LastName = clsInputValidate::ReadString();

		cout << "\nEnter Email       : ";
		User.Email = clsInputValidate::ReadString();

		cout << "\nEnter Phone       : ";
		User.Phone = clsInputValidate::ReadString();

		cout << "\nEnter Password    : ";
		User.Password = clsInputValidate::ReadString();

		cout << "\nEnter Permissions :";
		User.Permissions = _ReadPermissionsToSet();

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

	static string _ReadUsername()
	{
		string Username;

		cout << "Please enter user username : ";
		Username = clsInputValidate::ReadString();

		while (clsBankUser::IsUserExist(Username))
		{
			cout << "Username is already exist , choose another one : ";
			Username = clsInputValidate::ReadString();
		}
		return Username;
	}

public:

	static void ShowAddNewUserScreen()
	{
		_DrawScreenHeader("Add new user screen");

		string Username = _ReadUsername();

		// Creating object for adding
		clsBankUser NewUser = clsBankUser::GetAddNewUserObject(Username);

		_ReadUserInfo(NewUser);

		clsBankUser::enSaveResult SaveResult;

		SaveResult = NewUser.Save();

		// Check Save Result 
		switch (SaveResult)
		{
		case clsBankUser::enSaveResult::svFaildUsernameExists:
			cout << "\a\nERORR Adding operation failed ,Username is already exist .";
			break;
		case clsBankUser::enSaveResult::svFailedEmptyObject:

			cout << "\a\nERORR Adding operation failed , empty object !" << endl;
			break;

		case clsBankUser::enSaveResult::svSuccessed:
			cout << "\n\nUser Added Successfully :-0\n\n";

			_PrintUser(NewUser);

			break;
		}
	}

};