#pragma once

#include <vector>
#include <fstream>
#include "clsString.h"
#include "clsPerson.h"
#include "clsDate.h"
#include <string>
#include "clsUtil.h"

using namespace std;

class clsBankClient : public clsPerson
{
private:
	enum enMode { EmptyMode = 0, UpdateMode = 1, AddNewMode = 2, DeleteMode = 3 };
	enMode _Mode;
	string _AccountNumber;
	string _PinCode;
	double _AccountBalance;
	bool _MarkForDelete = false;

	struct stTransferLogRecord;

	static stTransferLogRecord _ConvertTransferLogLineToRecord(string Line, string Separator = "#//#")
	{
		stTransferLogRecord TransferLogRecord;
		vector <string> vLoginRecords = clsString::Split(Line, Separator);
		TransferLogRecord.DateAndTime = vLoginRecords.at(0);
		TransferLogRecord.SenderAccountNumber = vLoginRecords.at(1);
		TransferLogRecord.RecipientAccountNumber = vLoginRecords.at(2);
		TransferLogRecord.Amount = stof(vLoginRecords.at(3));
		TransferLogRecord.SenderBalance = stof(vLoginRecords.at(4));
		TransferLogRecord.RecipientBalance = stof(vLoginRecords.at(5));
		TransferLogRecord.Username = vLoginRecords.at(6);

		return TransferLogRecord;
	}

	static clsBankClient _ConvertLineToClientObject(string Line, string Separator = "#//#")
	{
		vector <string> vBankClient = clsString::Split(Line, Separator);
		return clsBankClient(enMode::UpdateMode, vBankClient.at(0), vBankClient.at(1), vBankClient.at(2), vBankClient.at(3), vBankClient.at(4), vBankClient.at(5), stof(vBankClient.at(6)));
	}

	static string _ConvertObjectToLine(clsBankClient Client, string Separator = "#//#")
	{
		string Line = "";
		Line = Client.FirstName + Separator;
		Line += Client.LastName + Separator;
		Line += Client.Email + Separator;
		Line += Client.Phone + Separator;
		Line += Client.AccountNumber() + Separator;
		Line += Client.PinCode + Separator;
		Line += to_string(Client.AccountBalance);
		return Line;
	}

	static vector <clsBankClient> _LoadClientsDataFromFile()
	{
		vector <clsBankClient> vClient;
		fstream MyFile;

		MyFile.open("clients.txt", ios::in);

		string Line;

		if (MyFile.is_open())
		{
			while (getline(MyFile, Line))
			{
				vClient.push_back(_ConvertLineToClientObject(Line));
			}
			MyFile.close();
		}
		return vClient;
	}

	void _SaveClientsDataToFile(vector <clsBankClient> vClient)
	{
		fstream MyFile;

		MyFile.open("clients.txt", ios::out);

		if (MyFile.is_open())
		{
			for (clsBankClient C : vClient)
			{
				if(C._MarkForDelete == false)
				MyFile << _ConvertObjectToLine(C) << endl;
			}
			MyFile.close();
		}
	}

	static clsBankClient _GetEmptyClientObject()
	{
		return clsBankClient(enMode::EmptyMode, "", "", "", "", "", "", 0);
	}

	void _AddDataLineToFile(string Line)
	{
		fstream MyFile;

		MyFile.open("Clients.txt", ios::out | ios::app);
		if (MyFile.is_open())
		{
			MyFile << Line << endl;
			MyFile.close();
		}

	}

	void _Update()
	{
		vector <clsBankClient> vClient = _LoadClientsDataFromFile();

		for (clsBankClient& C : vClient)
		{
			if (C.AccountNumber() == _AccountNumber)
			{
				C = *this;
				break;
			}
		}

		_SaveClientsDataToFile(vClient);
	}

	void _AddNew()
	{
		return _AddDataLineToFile(_ConvertObjectToLine(*this));
	}

	string _PrepareTransferLogRecord(double Amount, clsBankClient Recipient,  string Username,string Separator = "#//#" )
	{
		string Line  = clsDate::GetFullSystemDate() + Separator;
		Line += AccountNumber() + Separator;
		Line += Recipient.AccountNumber() + Separator;
	    Line += to_string(Amount) + Separator;
		Line += to_string(AccountBalance) + Separator;
		Line += to_string(Recipient.AccountBalance) + Separator;
		Line += Username;
		return Line;
	}

	void _RegisterTransferLog(double Amount, clsBankClient RecipientBalance, string Username,string Separator = "#//#" )
	{
		fstream MyFile;
		string DateLine = _PrepareTransferLogRecord(Amount, RecipientBalance , Username , Separator);
		MyFile.open("TransferLog.txt", ios::out | ios::app);

		if (MyFile.is_open())
		{
			MyFile << DateLine << endl;
		}
	}

public:
	
	struct stTransferLogRecord 
	{
		string Username;
		string SenderAccountNumber;
		string RecipientAccountNumber;
		string DateAndTime;
		float Amount = 0;
		float SenderBalance = 0;
		float RecipientBalance = 0;


	};

	static vector <stTransferLogRecord> GetTransferList()
	{
		vector <stTransferLogRecord> vTransferLog;

		fstream MyFile;

		MyFile.open("TransferLog.txt", ios::in);

		string Line;

		if (MyFile.is_open())
		{
			while (getline(MyFile, Line))
			{
				vTransferLog.push_back(_ConvertTransferLogLineToRecord(Line));
			}
			MyFile.close();
		}
		return vTransferLog;
	}


	clsBankClient(enMode Mode, string FirstName, string LastName, string Email, string Phone, string AccountNumber, string PinCode, double AccountBalance)
		: clsPerson(FirstName, LastName, Email, Phone)
	{
		_Mode = Mode;
		_AccountNumber = AccountNumber;
		_PinCode = PinCode;
		_AccountBalance = AccountBalance;

	}

	string AccountNumber()
	{
		return _AccountNumber;
	}

	//property Get
	double GetAccountBalance()
	{
		return _AccountBalance;
	}

	//property Set
	void SetAccountBalance(double AccountBalance)
	{
		_AccountBalance = AccountBalance;
	}

	__declspec(property(get = GetAccountBalance, put = SetAccountBalance)) double AccountBalance;

	bool IsEmpty()
	{
		return (_Mode == enMode::EmptyMode);
	}

	//property Get
	string GetPinCode()
	{
		return _PinCode;
	}

	//property Set
	void SetPinCode(string PinCode)
	{
		_PinCode = PinCode;
	}

	__declspec(property(get = GetPinCode, put = SetPinCode)) string PinCode;

	static clsBankClient Find(string AccountNumber)
	{
		fstream MyFile;

		MyFile.open("Clients.txt", ios::in);

		if (MyFile.is_open())
		{
			string Line;

			while (getline(MyFile, Line))
			{
				clsBankClient Client = _ConvertLineToClientObject(Line);
				if (Client.AccountNumber() == AccountNumber)
				{
					MyFile.close();
					return Client;
				}
			}
			MyFile.close();

		}
		return _GetEmptyClientObject();
	}

	static clsBankClient Find(string AccountNumber, string PinCode)
	{
		fstream MyFile;

		MyFile.open("Clients.txt", ios::in);

		if (MyFile.is_open())
		{
			string Line;

			while (getline(MyFile, Line))
			{
				clsBankClient Client = _ConvertLineToClientObject(Line);
				if (Client.AccountNumber() == AccountNumber && Client.PinCode == PinCode)
				{
					MyFile.close();
					return Client;
				}
			}
			MyFile.close();

		}
		return _GetEmptyClientObject();
	}

	static bool IsClientExist(string AccountNumber)
	{
		clsBankClient Client = Find(AccountNumber);
		return !(Client.IsEmpty());
	}

	static enum enSaveResult { svSuccessed = 0, svFailedEmptyObject = 1, svFaildAccountNumberExists };

	static clsBankClient GetAddNewClientObject(string AccountNumber)
	{
		return clsBankClient(enMode::AddNewMode, "", "", "", "", AccountNumber, "", 0);
	}

	bool Delete()
	{
		vector <clsBankClient> vClient = _LoadClientsDataFromFile();

		for (clsBankClient& C : vClient)
		{
			if (C.AccountNumber() == _AccountNumber)
			{
				C._MarkForDelete = true;
				break;
			}
		}

		_SaveClientsDataToFile(vClient);
		*this = _GetEmptyClientObject();
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

			if (IsClientExist(AccountNumber()))
			{
				return enSaveResult::svFaildAccountNumberExists;
			}
			else
			{
				_AddNew();
				_Mode = enMode::UpdateMode;
				return enSaveResult::svSuccessed;
			}
		}
	}

	static vector <clsBankClient> GetClientList()
	{
		return _LoadClientsDataFromFile();
	}

	static double GetTotalBalances()
	{
		double TotalBalances = 0;

		vector <clsBankClient> vClient = GetClientList();

		for (clsBankClient& C : vClient)
		{
			TotalBalances += C.AccountBalance;
		}

		return TotalBalances;

	}

	void Deposit(double Amount)
	{
		_AccountBalance += Amount;
		Save();
	}

	bool Withdraw(double Amount)
	{
		if(Amount > _AccountBalance)
		{
			return false;
		}
		_AccountBalance -= Amount;
		Save();
		return true;
	}

	bool Transfer(clsBankClient &Recipient, double Amount , string Username)
	{
		if (Withdraw(Amount))
		{
			Recipient.Deposit(Amount);
			_RegisterTransferLog(Amount, Recipient ,Username);
			return true;
		}
		else
		{
			return false;
		}
	}

};

