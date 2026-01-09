#pragma once

#include <iostream>
#include <string>
#include "clsScreen.h"
#include <iomanip>
#include <vector>
#include "clsCurrency.h"

using namespace std;

class clsCurrenciesListScreen :protected clsScreen
{

	static void _PrintCurrencyRegisterLine(clsCurrency Currency)
	{
		cout << setw(10) << left << "" << left << setw(30) << "| " + Currency.Country();
		cout << "| " << left << setw(15) << Currency.CurrencyCode();
		cout << "| " << left << setw(40) << Currency.CurrencyName();
		cout << "| " << left << setw(12) << Currency.Rate();
	}		   

public:

	static void ShowLoginRegisterScreen()
	{

		vector <clsCurrency> vCurrenciesList = clsCurrency::GetCurrenciesList();;

		string Title = "Currencies List Screen";
		string Subtitle = "    (" + to_string(vCurrenciesList.size()) + ") Currency";


		_DrawScreenHeader(Title, Subtitle);
		cout << setw(10) << left << "" << "----------------------------------------------------------------------------------------------------\n";
		cout << setw(10) << left << "" << left << setw(30) << "| Country";
		cout << "| " << left << setw(15) << "Code";
		cout << "| " << left << setw(40) << "Name";
		cout << "| " << left << setw(12) << "Rate/($1)\n";
		cout << setw(9) << left << "" << "--------------------------------------------------------------------------------------------------\n\n";

		if(vCurrenciesList.size() == 0)
		{
			cout << "\n\n\nThere Is No Currencies In The System... \n\n\n";
		}
		else
		{
			for (clsCurrency& C : vCurrenciesList)
			{
				_PrintCurrencyRegisterLine(C);
				cout << endl;
			}
		}


		cout << "\n" << setw(10) << left << "" << "--------------------------------------------------------------------------------------------------\n";


	}

};