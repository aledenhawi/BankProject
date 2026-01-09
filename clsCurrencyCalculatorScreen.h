#pragma once

#include <iostream>
#include "clsInputValidate.h"
#include <string>
#include "clsCurrency.h"
#include <cctype>
#include "clsScreen.h"
#include "clsString.h"

class clsCurrencyCalculatorScreen : protected clsScreen
{
private:

	static void _PrintCurrency(clsCurrency Currency , string Title)
	{
		cout << "\n------------------------------------\n";
		cout << Title;
		cout << "\n------------------------------------";
		cout << "\nCountry   : " << Currency.Country();
		cout << "\nCode      : " << Currency.CurrencyCode();
		cout << "\nName      : " << Currency.CurrencyName();
		cout << "\nRate/(1$) : " << Currency.Rate();
		cout << "\n------------------------------------";
	}

	static float _ReadAmount()
	{
		float Amount;
		cout << "\nPlease enter an amount to exchange : ";
		Amount = clsInputValidate::ReadNumber<float>();

		return Amount;
	}

	static clsCurrency _GetCurrency(string message)
	{
		string CurrencyCode;

		cout << message;
		CurrencyCode = clsInputValidate::ReadString();

		while (!clsCurrency::IsCurrencyExist(CurrencyCode))
		{
			cout << "\nWrong code , Choose another one : ";
			CurrencyCode = clsInputValidate::ReadString();
		}

		clsCurrency Currency = clsCurrency::FindByCode(CurrencyCode);

		return Currency;
	}

	static void PrintCalculationResult(float Amount ,clsCurrency Currency1 , clsCurrency Currency2)
	{
		_PrintCurrency(Currency1, "\tConvert From :");

		cout << "\n\n" << Amount << " " + Currency1.CurrencyCode() + " = " << Currency1.ConvertToUSD(Amount) << " USD" << endl;

		if (Currency1.CurrencyCode() != "USD")
		{
			cout << "\nConvert from Usd to :" << endl;

			_PrintCurrency(Currency2, "\tTo:");

			cout << "\n\n" << Amount << " " + Currency1.CurrencyCode() + " = " << Currency1.ConvertToOtherCurrency(Amount, Currency2) << " " + Currency2.CurrencyCode() << endl;
		}
	}

public:

	static void ShowCurrencyCalculatorScreen()
	{

		_DrawScreenHeader("Currency Calculator Screen");

		char Answer = 'y';
		string Code1, Code2;

		while (tolower(Answer) == 'y')
		{
			clsCurrency CurrencyFrom = _GetCurrency("\nPlease enter currency1 code :");
			clsCurrency CurrencyTo = _GetCurrency("\nPlease enter currency2 code :");
			float Amount = _ReadAmount();

			PrintCalculationResult(Amount, CurrencyFrom, CurrencyTo);

			cout << "\n\nDo you want to perform another exchange ? [Y/N] ";
			cin >> Answer;
		}
	}
};

