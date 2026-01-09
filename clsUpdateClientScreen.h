#pragma once

#include <iostream>
#include <string>
#include "clsScreen.h"
#include "clsInputValidate.h"
#include <iomanip>
#include "clsBankClient.h"

using namespace std;

class clsUpdateClientScreen : protected clsScreen
{
private:

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
		Client.AccountBalance = clsInputValidate::ReadNumber<float>();

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


public :

	static void ShowUpdateClientScreen()
	{
		if (!_CheckAccessRights(clsBankUser::enPermissions::pUpdateClient))
		{
			return;
		}
		string AccountNumber = "";

		_DrawScreenHeader("Update client screen");

		cout << "Please enter client account number : ";
		AccountNumber = clsInputValidate::ReadString();

		while (!clsBankClient::IsClientExist(AccountNumber))
		{
			cout << "Account number is not found , choose another one : ";
			AccountNumber = clsInputValidate::ReadString();
		}

		clsBankClient Client = clsBankClient::Find(AccountNumber);

		_PrintClient(Client);

		char Answer = 'y';
		cout << "\n\nAre you sure you want to update this client ? [Y/N] : ";
		cin >> Answer;


		if (tolower(Answer) == 'y')
		{

			cout << "\n\n    Update Client Info  ";
			cout << "\n----------------------------";
			_ReadClientInfo(Client);

			clsBankClient::enSaveResult SaveResult;

			SaveResult = Client.Save();

			switch (SaveResult)
			{
			case clsBankClient::enSaveResult::svFailedEmptyObject:
				cout << "Update failed , empty object !" << endl;
				break;
			case clsBankClient::enSaveResult::svSuccessed:
				cout << "\nClient Updated successfully !!\n\n";
				_PrintClient(Client);
				break;

			}
		}
	}

};

