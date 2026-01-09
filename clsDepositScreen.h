#pragma once

#include <iostream>
#include <string>
#include <vector>
#include "clsScreen.h"
#include <iomanip>
#include "clsBankClient.h"
#include "clsInputValidate.h"

class clsDepositScreen : protected clsScreen
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

public :


	static void ShowDepositClientScreen()
	{

		string AccountNumber = "";

		_DrawScreenHeader("Deposit screen");

		cout << "Please enter client account number : ";
		AccountNumber = clsInputValidate::ReadString();

		while (!clsBankClient::IsClientExist(AccountNumber))
		{
			cout << "Account number is not found , choose another one : ";
			AccountNumber = clsInputValidate::ReadString();
		}

		clsBankClient Client = clsBankClient::Find(AccountNumber);

		_PrintClient(Client);

		double Amount ;
		cout << "\nPlease enter deposit amount : ";

		Amount = clsInputValidate::ReadNumber<double>();

		char Answer;
		cout << "\n\nAre you sure you want to perform this transaction ? (Y/N) ";
		cin >> Answer;

		if (tolower(Answer) == 'y')
		{
			Client.Deposit(Amount);
			cout << "\n\nAmount Deposited successfully!!\n";
			cout << "New Balance is = " << Client.AccountBalance << endl;
		}
		else
		{
			cout << "\n\nDeposit was cancelled!";
		}
	}
};

