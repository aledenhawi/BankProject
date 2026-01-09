#pragma once

#include <iostream>
#include <string>
#include "clsScreen.h"
#include <iomanip>
#include <vector>
#include "clsBankClient.h"
#include "clsUsersListScreen.h"

using namespace std;

class clsClientListScreen : protected clsScreen
{
protected:


	static void _PrintClientRecordLine(clsBankClient ClientList)
	{
		cout << setw(8) << left << "" << left << setw(15) << "| " + ClientList.AccountNumber();
		cout << left << setw(25) << "| " + ClientList.FullName();
		cout << left << setw(14) << "| " + ClientList.Phone;
		cout << left << setw(30) << "| " + ClientList.Email;
		cout << left << setw(10) << "| " + ClientList.PinCode;
		cout << left << setw(12) << "| " + to_string(ClientList.AccountBalance);
	}

public:

	static void ShowClientList()
	{
		if(!_CheckAccessRights(clsBankUser::enPermissions::pClientsList))
		{
			return;
		}


		vector <clsBankClient> ClientList = clsBankClient::GetClientList();

		string Title = "Client List Screen";
		
		string Subtitle = "(" + to_string(ClientList.size()) + ") Client(s) ";
		

		_DrawScreenHeader(Title, Subtitle);

		// Print The Header
		cout << setw(8) << left << "" << "-------------------------------------------------------------------------------------------------------------\n\n";
		cout << setw(8) << left << "" << left << setw(15) << "|Account Number";
		cout << left << setw(25) << "|Client Name";
		cout << left << setw(14) << "|Phone";
		cout << left << setw(30) << "|Email";
		cout << left << setw(10) << "|PinCode";
		cout << left << setw(12) << "|Balance\n\n";
		cout << setw(6) << left << "" << "-------------------------------------------------------------------------------------------------------------\n\n";

		// check if the file empty
		if (ClientList.size() == 0)
		{
			cout << "\n\n                There is no Clients In the system                         \n\n";
		}
		else
		{
			// Print Clients Record
			for (clsBankClient& C : ClientList)
			{
				_PrintClientRecordLine(C);
				cout << endl;
			}
		}
		//Print The footer
		cout << setw(8) << left << "" << "-------------------------------------------------------------------------------------------------------------\n\n";
	}


};

