#pragma once

#include <iostream>
#include <string>
#include "clsScreen.h"
#include "clsInputValidate.h"
#include <iomanip>
#include "clsBankUser.h"

using namespace std;

class clsUpdateUserScreen : protected clsScreen
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

		while (!clsBankUser::IsUserExist(Username))
		{
			cout << "Username is not exist , try to enter a valid one : ";
			Username = clsInputValidate::ReadString();
		}
		return Username;
	}

public:

	static void ShowUpdateUserScreen()
	{
		_DrawScreenHeader("Update User screen");

		string Username = _ReadUsername();

		clsBankUser User = clsBankUser::Find(Username);

		_PrintUser(User);

		char Answer = 'y';
		cout << "\n\nAre you sure you want to update this user ? [Y/N] : ";
		cin >> Answer;


		if (tolower(Answer) == 'y')
		{

			cout << "\n\n    Update user info  ";
			cout << "\n----------------------------";
			_ReadUserInfo(User);

			clsBankUser::enSaveResult SaveResult;

			SaveResult = User.Save();

			switch (SaveResult)
			{
			case clsBankUser::enSaveResult::svFailedEmptyObject:
				cout << "Update failed , empty object !" << endl;
				break;
			case clsBankUser::enSaveResult::svSuccessed:

				cout << "\nUser Updated successfully !!\n\n";
				
				_PrintUser(User);
				break;

			}
		}
	}

};

