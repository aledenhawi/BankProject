#pragma once

#include <iostream>
#include <string>
#include "clsScreen.h"
#include <iomanip>
#include <vector>
#include "clsCurrency.h"
#include "clsInputValidate.h"

using namespace std;

class clsFindCurrencyScreen : protected clsScreen
{
private:
	enum enFindTypes {ByCode = 1 , ByCountry = 2};

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

	static short _ReadFindCurrencyOption()
	{
		short Answer;
		cout << "Find By : (1) Code or (2) Country ? " << endl;
		Answer = clsInputValidate::ReadNumber<short>();

		while(Answer != 2 && Answer != 1)
		{
			cout << "Wrong Choice , Please enter 1 or 2 only .";
			cin >> Answer;
		}
		return Answer;
	}

	static void _ShowResult(clsCurrency Currency)
	{

		if (!Currency.IsEmpty())
		{
			cout << "Currency Found :)" << endl;
			_PrintCurrency(Currency);
		}
		else
		{
			cout << "Currency Was Not Found :(" << endl;
		}
	}

public:

	static void ShowFindCurrencyScreen()
	{
		_DrawScreenHeader("Find Currency Screen");


		short Answer = _ReadFindCurrencyOption();


		if(Answer == 1)
		{	

			string CurrencyCode;
			cout << "Please enter currency code : ";
		    CurrencyCode = clsInputValidate::ReadString();
			clsCurrency Currency = clsCurrency::FindByCode(CurrencyCode);
			_ShowResult(Currency);
	    }
		else
		{
			string Country;
		    cout << "Please enter country name : ";
			Country = clsInputValidate::ReadString();
			clsCurrency Currency = clsCurrency::FindByCountry(Country);
			_ShowResult(Currency);
		}

		
	}
};

