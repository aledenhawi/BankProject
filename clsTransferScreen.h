#pragma once

#include <iostream>
#include <string>
#include "clsScreen.h"
#include <iomanip>
#include <vector>
#include "clsBankClient.h"
#include "clsInputValidate.h"
#include "Global.h"

class clsTransferScreen : public clsScreen
{
private:

	static string _ReadAccountNumber(string Message)
	{
		string AccountNumber;
		cout << Message;
		AccountNumber = clsInputValidate::ReadString();

		while (!clsBankClient::IsClientExist(AccountNumber))
		{
			cout << "\nAccount number is not exist , choose another one : ";
			AccountNumber = clsInputValidate::ReadString();
		}
		return AccountNumber;

	}

	static void _PrintClient(clsBankClient Client)
	{
		cout << "\n\n------------------------------";
		cout << "\n        Client Card           ";
		cout << "\n------------------------------";
		cout << "\nFull Name   : " << Client.FullName();
		cout << "\nAcc. Number : " << Client.AccountNumber();
		cout << "\nBalance     : " << Client.AccountBalance;
		cout << "\n------------------------------\n";

	}
public:

	static void ShowTransferScreen()
	{

		_DrawScreenHeader("Transfer Screen");

		string SenderAccountNumber = _ReadAccountNumber("\nPlease enter account Number to transfer from: ");

		clsBankClient Sender = clsBankClient::Find(SenderAccountNumber);

		_PrintClient(Sender);

		string RecipientAccountNumber = _ReadAccountNumber("\nPlease enter account Number to transfer to: ");

		
		while (RecipientAccountNumber == SenderAccountNumber)
		{
		    RecipientAccountNumber = _ReadAccountNumber("\nYou cant transfer to the same client , enter another account Number: ");
		}
		
		clsBankClient Recipient = clsBankClient::Find(RecipientAccountNumber);

		_PrintClient(Recipient);

		double TransferAmount;

		cout << "\nEnter transfer amount: ";
		cin >> TransferAmount;

		
		while(!Sender.Transfer(Recipient, TransferAmount , CurrentUser.Username))
		{
			cout << "\nAmount exceeds the available balance , enter another amount: ";
			cin >> TransferAmount;
		}
			cout << "\nTransfer done successfully :-)" << endl;


		_PrintClient(Sender);
		_PrintClient(Recipient);
	}
		
};

