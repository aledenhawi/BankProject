#pragma once


#include <iostream>
#include <string>
#include "clsScreen.h"
#include <iomanip>
#include <vector>
#include "clsBankClient.h"
#include "clsUtil.h"
using namespace std;

class clsTotalBalancesScreen : protected clsScreen
{
private:

	static void _PrintClientBalanceLine(clsBankClient ClientList)
	{
		cout << setw(20) << left << "" << left << setw(15) << "| " + ClientList.AccountNumber();
		cout << left << setw(40) << "| " + ClientList.FullName();
		cout << left << setw(12) << "| " + to_string(ClientList.AccountBalance);
	}
public:


	static void ShowTotalBalances()
	{
		vector <clsBankClient> ClientList = clsBankClient::GetClientList();
		double TotalBalances = clsBankClient::GetTotalBalances();

		string Title = " Balances List Screen";
		string Subtitle = "    (" + to_string(ClientList.size()) + ") Client(s)";


		_DrawScreenHeader(Title, Subtitle);
		cout << setw(20) << left << "" << "---------------------------------------------------------------------------\n";
		cout << setw(20) << left << "" << left << setw(15) << "| Account Number";
		cout << left << setw(40) << "| Client Name";
		cout << left << setw(12) << "| Balance\n";
		cout << setw(18) << left << "" << "---------------------------------------------------------------------------\n\n";

		if (ClientList.size() == 0)
		{
			cout << "\n\n                There is no Clients In the system                         \n\n";
		}
		else
		{

			for (clsBankClient& C : ClientList)
			{
				_PrintClientBalanceLine(C);
				cout << endl;
			}
		}

		cout << setw(20) << left << "" << "---------------------------------------------------------------------------\n";
		cout << setw(17) << left << "" << "                  Total Balances = " << TotalBalances << endl;
		cout << setw(17) << left << "" << "                 (" << clsUtil::NumberToText(TotalBalances)<< ")" << endl;
	}

};

