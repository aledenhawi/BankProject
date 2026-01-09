#pragma once

#include <iostream>
#include "clsInputValidate.h"
#include <string>
#include "clsCurrency.h"
#include <cctype>
#include "clsScreen.h"

using namespace std;

class clsUpdateCurrencyRateScreen : protected clsScreen
{
private :

	static void _PrintCurrency(clsCurrency Currency)
	{
		cout << "\n------------------------------------";
		cout << "\n             Currency Info";
		cout << "\n------------------------------------";
		cout << "\nCountry   : " << Currency.Country();
		cout << "\nCode      : " << Currency.CurrencyCode();
		cout << "\nName      : " << Currency.CurrencyName();
		cout << "\nRate/(1$) : " << Currency.Rate();
		cout << "\n------------------------------------";
	}

	static float _ReadRate()
	{
		float NewRate;

		cout << "Enter new rate : ";
		NewRate = clsInputValidate::ReadNumber<float>();

		return NewRate;
	}

public :

	static void ShowUpdateCurrencyRateScreen()
	{
		_DrawScreenHeader("Update Currency Screen");

		string Code;
		cout << "\nPlease enter currency code : ";
		Code = clsInputValidate::ReadString();

		clsCurrency Currency = clsCurrency::FindByCode(Code);

		while(Currency.IsEmpty())
		{
			cout << "\nWrong code , Choose another one : ";
			Code = clsInputValidate::ReadString();
		}
		_PrintCurrency(Currency);

		char Answer = 'n';

		cout << "\n\nAre you sure you want to update this rate ? [Y/N]  ";
		cin >> Answer;

		if(tolower(Answer) == 'y')
		{
			cout << "\nUpdate Currency Rate:\n\n";
			cout << "----------------------\n\n";
			
			Currency.UpdateRate(_ReadRate());

			cout << "\nCurrency rate updated successfully :-)\n" << endl;

			_PrintCurrency(Currency);
		}
		
	}
};

