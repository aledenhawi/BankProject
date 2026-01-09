#pragma once

#include <iostream>
#include <string>
#include "clsDate.h";

using namespace std;

class clsInputValidate
{

public:


	
	template <typename T> static bool IsNumberBetween(T Number, T From, T To)
	{
		return (Number >= From && Number <= To);
	}

	static bool IsDateBetween(clsDate Date1, clsDate StartDate, clsDate EndDate)
	{
		if (clsDate::IsDate1BeforeDate2(EndDate,StartDate))
		{
			clsDate::SwapDates(StartDate, EndDate);
		}

		return !(clsDate::IsDate1AfterDate2(StartDate , EndDate) &&  clsDate::IsDate1BeforeDate2(EndDate,StartDate) );
	};

	static string ReadString()
	{
		string S = "";
		getline(cin >> ws, S);
		return S;
	}

	template <typename T> static T ReadNumber(string FailMessage = "Invalid Number , Enter a valid one : ")
	{
		T Number;


		while(!(cin >> Number))
		{
			cin.clear();
			cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');

			cout << FailMessage << endl;
		}
		return Number;
	}
	
	template <typename T> static T ReadNumberBetween(T From, T To , string FailMessage = "Number Is not within the range , enter another one  : ")
	{
		T Number = ReadNumber<T>();

		while (!IsNumberBetween(Number , From , To))
		{
			cout << FailMessage << endl;
			Number = ReadNumber<T>();
		} 

		return Number;
	}

	static bool IsValidDate(clsDate Date)
	{
		return clsDate::IsValidDate(Date);
	}


private:
	void NNN()
	{
		cout << "REUSEABILITY , PRODUCTABILITY , ONE SOURCE";
	}
};

