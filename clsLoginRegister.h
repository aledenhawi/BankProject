#pragma once

#include <iostream>
#include <string>
#include "clsScreen.h"
#include <iomanip>
#include <vector>
#include <fstream>

class clsLoginRegister
{
private:

	string _DateAndTime;
	string _Username;
	string _Password;
	string _Permissions;


	static clsLoginRegister _ConvertLineToLoginObject(string Line, string Separator = "#//#")
	{
		vector <string> vLoginRecords = clsString::Split(Line, Separator);
		return clsLoginRegister(vLoginRecords.at(0), vLoginRecords.at(1), vLoginRecords.at(2), vLoginRecords.at(3));

	}

	static vector <clsLoginRegister> _LoadLoginRegisterDataFromFile()
	{
		vector <clsLoginRegister> vLoginData;

		fstream MyFile;

		MyFile.open("LoginRegister.txt", ios::in);

		string Line;

		if (MyFile.is_open())
		{
			while (getline(MyFile, Line))
			{
				vLoginData.push_back(_ConvertLineToLoginObject(Line));
			}
			MyFile.close();
		}
		return vLoginData;
	}

public:

	clsLoginRegister(string DateAndTime, string Username, string Password, string Permissions)
	{
		_DateAndTime = DateAndTime;
		_Username = Username;
		_Password = Password;
		_Permissions = Permissions;
	}
	// --- DateAndTime ---
	void SetDateAndTime(string DateAndTime)
	{
		_DateAndTime = DateAndTime;
	}

	string GetDateAndTime()
	{
		return _DateAndTime;
	}

	__declspec(property(get = GetDateAndTime, put = SetDateAndTime)) string DateAndTime;


	// --- Username ---
	void SetUsername(string Username)
	{
		_Username = Username;
	}

	string GetUsername()
	{
		return _Username;
	}

	__declspec(property(get = GetUsername, put = SetUsername)) string Username;


	// --- Password ---
	void SetPassword(string Password)
	{
		_Password = Password;
	}

	string GetPassword()
	{
		return _Password;
	}

	__declspec(property(get = GetPassword, put = SetPassword)) string Password;


	// --- Permissions ---
	void SetPermissions(string Permissions)
	{
		_Permissions = Permissions;
	}

	string GetPermissions()
	{
		return _Permissions;
	}

	__declspec(property(get = GetPermissions, put = SetPermissions)) string Permissions;

	static vector <clsLoginRegister> GetLoginList()
	{
		return _LoadLoginRegisterDataFromFile();
	}
};
