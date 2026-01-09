#pragma once

#include <iostream>
#include <string>
#include "clsScreen.h"
#include <iomanip>
#include <vector>
#include "clsBankClient.h"
#include "clsInputValidate.h"

using namespace std;

class clsAddNewClientScreen : protected clsScreen
{
private :

	static void _ReadClientInfo(clsBankClient& Client)
	{
		cout << "\nEnter First Name  : ";
		Client.FirstName = clsInputValidate::ReadString();

		cout << "\nEnter Last Name   : ";
		Client.LastName = clsInputValidate::ReadString();

		cout << "\nEnter Email       : ";
		Client.Email = clsInputValidate::ReadString();

		cout << "\nEnter Phone       : ";
		Client.Phone = clsInputValidate::ReadString();

		cout << "\nEnter Pin Code    : ";
		Client.PinCode = clsInputValidate::ReadString();

		cout << "\nEnter Balance     : ";
		Client.AccountBalance = clsInputValidate::ReadNumber<double>();

	}

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

	static void ShowAddNewClientScreen()
	{
		if (!_CheckAccessRights(clsBankUser::enPermissions::pAddnewClient))
		{
			return;
		}
		_DrawScreenHeader("Add New Client Screen");

		string AccountNumber;

		cout << "Please enter Client account Number : ";
		AccountNumber = clsInputValidate::ReadString();

		while (clsBankClient::IsClientExist(AccountNumber))
		{
			cout << "Account Number is already exist , choose another one : ";
			AccountNumber = clsInputValidate::ReadString();
		}

		// Creating object for adding
		clsBankClient NewClient = clsBankClient::GetAddNewClientObject(AccountNumber);

		_ReadClientInfo(NewClient);

		clsBankClient::enSaveResult SaveResult;

		SaveResult = NewClient.Save();

		// Check Save Result 
		switch (SaveResult)
		{
		case clsBankClient::enSaveResult::svFaildAccountNumberExists:
			cout << "\a\nERORR Adding operation failed , account number is already exist .";
			break;
		case clsBankClient::enSaveResult::svFailedEmptyObject:

			cout << "\a\nERORR Adding operation failed , empty object !" << endl;
			break;

		case clsBankClient::enSaveResult::svSuccessed:
			cout << "\n\nClient Added Successfully :-0\n\n";

			_PrintClient(NewClient);

			break;
		}
	}


};

