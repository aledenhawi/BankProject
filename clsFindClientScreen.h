#pragma once

#include <iostream>
#include <string>
#include "clsScreen.h"
#include "clsInputValidate.h"
#include <iomanip>
#include "clsBankClient.h"

using namespace std;

class clsFindClientScreen : protected clsScreen
{
private:

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

public :
	static void ShowFindClientScreen()
	{
		if (!_CheckAccessRights(clsBankUser::enPermissions::pFindClient))
		{
			return;
		}
		string AccountNumber = "";

		_DrawScreenHeader("Find client screen");

		cout << "Please enter client account number : ";
		AccountNumber = clsInputValidate::ReadString();

		while (!clsBankClient::IsClientExist(AccountNumber))
		{
			cout << "Account number is not found , choose another one : ";
			AccountNumber = clsInputValidate::ReadString();
		}

		clsBankClient Client = clsBankClient::Find(AccountNumber);

		if(!Client.IsEmpty())
		{
			cout << "\nUser Found :)\n\n";
			_PrintClient(Client);
		}
		else
		{
			cout << "\nUser is not Found :)\n\n";
		}
		
	}
};

