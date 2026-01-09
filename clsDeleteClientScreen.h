#pragma once

#include <iostream>
#include <string>
#include "clsScreen.h"
#include "clsInputValidate.h"
#include <iomanip>
#include "clsBankClient.h"

class clsDeleteClientScreen : protected clsScreen
{

	static void _PrintClient(clsBankClient Client)
	{
		cout << "------------------------------";
		cout << "\n        Client Card           ";
		cout << "\n------------------------------";
		cout << "\nFirst Name  : " << Client.FirstName;
		cout << "\nLast Name   : " << Client.LastName;
		cout << "\nFull Name   : " << Client.FullName();
		cout << "\nEmail       : " << Client.Email;
		cout << "\nPhone       : " << Client.Phone;
		cout << "\nAcc. Number : " << Client.AccountNumber();
		cout << "\nPassword    : " << Client.PinCode;
		cout << "\nBalance     : " << Client.AccountBalance;
		cout << "\n------------------------------\n";

	}

public:

	static void ShowDeleteClientScreen()
	{
		if (!_CheckAccessRights(clsBankUser::enPermissions::pDeleteClient))
		{
			return;
		}

		_DrawScreenHeader("Delete client screen");

		string AccountNumber = "";

		char cDelete = 'n';

		cout << "Please enter client account number : ";
		AccountNumber = clsInputValidate::ReadString();

		while (!clsBankClient::IsClientExist(AccountNumber))
		{
			cout << "Account number is not found , choose another one : ";
			AccountNumber = clsInputValidate::ReadString();
		}
	
		clsBankClient Client = clsBankClient::Find(AccountNumber);
	
		_PrintClient(Client);

		cout << "Are you sure you want to delete this client ? (Y/N)" << endl;
		cin >> cDelete;

		if ((tolower(cDelete) == 'y'))
		{
			if (Client.Delete())
			{
				cout << "\nClient Deleted successfully !!\n\n";
				_PrintClient(Client);
			}
			else
			{
				cout << "\nError Client Was not Deleted .";
			}


		}


	}

};

