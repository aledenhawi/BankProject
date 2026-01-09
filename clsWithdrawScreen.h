#pragma once

#include <iostream>
#include <string>
#include <vector>
#include "clsScreen.h"
#include <iomanip>
#include "clsBankClient.h"
#include "clsInputValidate.h"

class clsWithdrawScreen : protected clsScreen
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

	static string _ReadAccountNumber()
	{
		string AccountNumber;
		cout << "Please enter client account number : ";
		AccountNumber = clsInputValidate::ReadString();

		while (!clsBankClient::IsClientExist(AccountNumber))
		{
			cout << "Account number is not found , choose another one : ";
			AccountNumber = clsInputValidate::ReadString();
		}
		return AccountNumber;
	}
public:


	static void ShowWithdrawClientScreen()
	{

	

		_DrawScreenHeader("Withdraw screen");

		string AccountNumber = _ReadAccountNumber() ;

		clsBankClient Client = clsBankClient::Find(AccountNumber);

		_PrintClient(Client);

		double Amount;
		cout << "\nPlease enter deposit amount : ";

		Amount = clsInputValidate::ReadNumber<double>();

		char Answer;
		cout << "\n\nAre you sure you want to perform this transaction ? (Y/N) ";
		cin >> Answer;

		if (tolower(Answer) == 'y')
		{

			if(Client.Withdraw(Amount))
			{

				cout << "\n\nWithdraw done successfully!!\n";
				cout << "New Balance is = " << Client.AccountBalance << endl;
			}
			else
			{
				cout << "\nCannot withdraw , insufficient balance . \n";
				cout << "Amount to withdraw is = " << Amount << endl;
				cout << "Your Balance = " << Client.AccountBalance << endl;
			}
		}
		else
		{
			cout << "\n\nWithdraw was cancelled!";
		}
	}
};
