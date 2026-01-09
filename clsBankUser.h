#pragma once

#include <vector>
#include <fstream>
#include "clsString.h"
#include "clsPerson.h"
#include "Global.h"
#include "clsDate.h"
#include "clsUtil.h"

using namespace std;


class clsBankUser :public clsPerson
{
private:
	static enum enMode {EmptyMode = 1 , UpdateMode = 2 ,AddNewMode = 3};
	enMode _Mode;
	string _Username;
	string _Password;
	short _Permissions;
	bool _MarkedForDelete = false;

	struct stLoginRegisterRecord;

	static stLoginRegisterRecord _ConvertLoginRegisterLineToRecord(string Line, string Separator = "#//#")
	{
		stLoginRegisterRecord LoginRegisterRecord;
		vector <string> vLoginRecords = clsString::Split(Line, Separator);
		LoginRegisterRecord.DateAndTime = vLoginRecords.at(0);
		LoginRegisterRecord.Username = vLoginRecords.at(1);
		LoginRegisterRecord.Password = clsUtil::DecryptText(vLoginRecords.at(2));
		LoginRegisterRecord.Permissions = stoi(vLoginRecords.at(3));
		return LoginRegisterRecord;
	}

	string _PrepareLoginRecord(string Separator = "#//#")
	{
		string Line = clsDate::GetFullSystemDate() + Separator;
		Line += Username + Separator;
		Line += clsUtil::EncryptText(Password) + Separator;
		Line += to_string(Permissions);
		return Line;
	}

	static clsBankUser _ConvertLineToUserObject(string Line , string Separator = "#//#")
	{
		vector <string> vBankUser = clsString::Split(Line, Separator);
		return clsBankUser(enMode::UpdateMode, vBankUser.at(0), vBankUser.at(1), vBankUser.at(2), vBankUser.at(3), vBankUser.at(4), clsUtil::DecryptText(vBankUser.at(5)), stoi(vBankUser.at(6)));

	}

	static clsBankUser _GetEmptyUserObject()
	{
		return clsBankUser(enMode::EmptyMode, "", "", "", "", "", "", 0);
	}

	string _ConvertUserObjectToLine(clsBankUser User ,string Separator = "#//#")
	{
		string Line;
		Line = User.FirstName + Separator;
		Line += User.LastName + Separator;
		Line += User.Email + Separator;
		Line += User.Phone + Separator;
		Line += User._Username + Separator;
		Line += clsUtil::EncryptText(User._Password) + Separator;
		Line += to_string(User._Permissions);
		return Line;
	}

	static vector <clsBankUser> _LoadUsersDataFromFile()
	{
		vector <clsBankUser> vUser;
		fstream MyFile;

		MyFile.open("Users.txt", ios::in);

		string Line;

		if (MyFile.is_open())
		{
			while (getline(MyFile, Line))
			{
				vUser.push_back(_ConvertLineToUserObject(Line));
			}
			MyFile.close();
		}
		return vUser;
	}

	void _SaveUsersDataToFile(vector <clsBankUser> vUser)
	{
		fstream MyFile;

		MyFile.open("Users.txt", ios::out);

		if (MyFile.is_open())
		{
			for (clsBankUser &U : vUser)
			{
				if (U._MarkedForDelete == false)
				{
					MyFile << _ConvertUserObjectToLine(U) << endl;
				}
			}
			MyFile.close();
		}
	}

	void _Update()
	{
		vector <clsBankUser> vClient = _LoadUsersDataFromFile();
		for(clsBankUser &C : vClient )
		{
			if(C._Username == _Username)
			{
				C = *this;
				break;
			}
		} 
	}

	void _AddNew()
	 {
		_AddDataLineToFile(_ConvertUserObjectToLine(*this));
	 }

	void _AddDataLineToFile(string Line)
	{
		fstream MyFile;

		MyFile.open("Users.txt", ios::out | ios::app);
		if (MyFile.is_open())
		{
			MyFile << Line << endl;
			MyFile.close();
		}

	}


public :

	struct stLoginRegisterRecord
	{
		string DateAndTime = "";
		string Username = "";
		string Password = "";
		short  Permissions = 0;
	};

	static vector <stLoginRegisterRecord> GetLoginList()
	{
		vector <stLoginRegisterRecord> vLoginData;

		fstream MyFile;

		MyFile.open("LoginRegister.txt", ios::in);

		string Line;

		if (MyFile.is_open())
		{
			while (getline(MyFile, Line))
			{
				vLoginData.push_back(_ConvertLoginRegisterLineToRecord(Line));
			}
			MyFile.close();
		}
		return vLoginData;
	}

	enum enPermissions{pAll = -1 , pClientsList = 1 , pAddnewClient = 2 , pDeleteClient = 4 , pUpdateClient = 8 , pFindClient = 16 , pTransactionsMenu=32 , pManageUsers = 64 , pLoginRegister = 128};

	clsBankUser(enMode Mode , string FirstName, string LastName, string Email, string Phone , string Username, string Password, short Permissions) :
		clsPerson(FirstName , LastName , Email , Phone)
	{
		_Mode = Mode;
		_Username = Username;
		_Password = Password;
		_Permissions = Permissions;
	}

	bool MarkedForDeleted()
	{
		return _MarkedForDelete;
	}

	void SetPassword(string Password)
	{
		_Password = Password;
	}

	string GetPassword()
	{
		return _Password;
	}

	__declspec(property(get = GetPassword, put = SetPassword)) string Password;

	short GetPermissions()
	{
		return _Permissions;
	}

	void SetPermissions(short Permissions)
	{
		_Permissions = Permissions;
	}

	__declspec(property(get = GetPermissions, put = SetPermissions)) short Permissions;

	void RegisterLogin()
	{
		fstream MyFile;
		string DateLine = _PrepareLoginRecord();
		MyFile.open("LoginRegister.txt", ios::out | ios::app);

		if (MyFile.is_open())
		{
			MyFile << DateLine << endl;
		}

	}

	string GetUsername()
	{
		return _Username;
	}

	void SetUsername(string Username)
	{
		_Username = Username;
	}

	__declspec(property(get = GetUsername, put = SetUsername)) string Username;

	static clsBankUser Find(string Username)
	{
		fstream MyFile;
		string Line = "";
		clsBankUser User = _GetEmptyUserObject();

		MyFile.open("Users.txt", ios::in); // Read only mode

		if(MyFile.is_open())
		{ 
			while(getline(MyFile ,Line))
			{
				User = _ConvertLineToUserObject(Line);
				if(User._Username == Username)
				{
					MyFile.close();
					return User;
				}
			}
			MyFile.close();
		}
		return _GetEmptyUserObject();
	}

	bool IsEmpty()
	{
		return (_Mode == enMode::EmptyMode);
	}

	static bool IsUserExist(string Username)
	{
		clsBankUser User = Find(Username);
		return (!User.IsEmpty());
	}

	static clsBankUser Find(string Username ,string Password)
	{
		fstream MyFile;
		string Line = "";
		clsBankUser User = _GetEmptyUserObject();

		MyFile.open("Users.txt", ios::in); // Read only mode

		if (MyFile.is_open())
		{
			while (getline(MyFile, Line))
			{
				User = _ConvertLineToUserObject(Line);
				if (User._Username == Username && Password == User._Password)
				{
					MyFile.close();
					return User;
				}
			}
			MyFile.close();
		}
		return _GetEmptyUserObject();
	}

	enum enSaveResult{ svFailedEmptyObject  =1 , svSuccessed = 2 , svFaildUsernameExists = 3};

	bool Delete()
	{
		fstream MyFile;

		vector <clsBankUser> vUser = _LoadUsersDataFromFile();

		MyFile.open("Users.txt", ios::out);

		if (MyFile.is_open())
		{
			for (clsBankUser &U : vUser)
			{
				if (U._Username == _Username)
				{
					U._MarkedForDelete = true;
					break;
				}
			}
			MyFile.close();
		}
		_SaveUsersDataToFile(vUser);

		*this = _GetEmptyUserObject();
		return true;
	}

	enSaveResult Save()
	{
		switch (_Mode)
		{
		case enMode::EmptyMode:

			return enSaveResult::svFailedEmptyObject;

		case enMode::UpdateMode:

			_Update();

			return enSaveResult::svSuccessed;
		case enMode::AddNewMode:

			if (IsUserExist(_Username))
			{
				return enSaveResult::svFaildUsernameExists;
			}
			else
			{
				_AddNew();
				_Mode = enMode::UpdateMode;
				return enSaveResult::svSuccessed;
			}
		}
	}

	static clsBankUser GetAddNewUserObject(string Username)
	{
		return clsBankUser(enMode::AddNewMode, "", "", "", "",Username, "", 0);
	}

	static vector <clsBankUser> GetUsersList()
	 {
		 return _LoadUsersDataFromFile();
	 }

	bool CheckAccessPermissions(enPermissions Permission)
	{
	if(this->Permissions == enPermissions::pAll)
	{
		return true;
	}
	else if ((this->Permissions & Permission) == Permission)
	{
		return true;
	}
	return false;
	}


};

