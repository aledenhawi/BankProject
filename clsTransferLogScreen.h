#pragma once

#include <iostream>
#include <string>
#include "clsScreen.h"
#include <iomanip>
#include <vector>
#include"clsBankClient.h";

class clsTransferLog : public clsScreen
{

	static void _PrintTransferLogLine(clsBankClient::stTransferLogRecord TransferLogRecord)
	{
		cout << setw(10) << left << "" << left << setw(22) << "| " + TransferLogRecord.DateAndTime;
		cout << "| " << left << setw(8) << TransferLogRecord.SenderAccountNumber;
		cout << "| " << left << setw(8) << TransferLogRecord.RecipientAccountNumber;
		cout << "| " << left << setw(13) << TransferLogRecord.Amount;
		cout << "| " << left << setw(13) << TransferLogRecord.SenderBalance;
		cout << "| " << left << setw(13) << TransferLogRecord.RecipientBalance;
		cout << "| " << left << setw(5)  << TransferLogRecord.Username;
	}

public:

	static void ShowTransferLogScreen()
	{
		vector <clsBankClient::stTransferLogRecord> vTransferList = clsBankClient::GetTransferList();

		string Title = "Transfer Log Screen";
		string Subtitle = "    (" + to_string(vTransferList.size()) + ") Record(s)";


		_DrawScreenHeader(Title, Subtitle);
		cout << setw(10) << left << "" << "-------------------------------------------------------------------------------------------------\n";
		cout << setw(10) << left << "" << left << setw(22) << "| Date/Time";
		cout << "| "<< left << setw(8) << "S.Acct";
		cout << "| "<< left << setw(8) << "R.Acct";
		cout << "| "<< left << setw(13) << "Amount";
		cout << "| "<< left << setw(13) << "S.Balance";
		cout << "| "<< left << setw(13) << "R.Balance";
		cout << "| "<< left << setw(5) << "User\n";
		cout << setw(10) << left << "" << "-------------------------------------------------------------------------------------------------\n\n";

		for (clsBankClient::stTransferLogRecord& T : vTransferList)
		{
			_PrintTransferLogLine(T);
			cout << endl;
		}

		cout << "\n" << setw(10) << left << "" << "-------------------------------------------------------------------------------------------------\n";

	}
};

