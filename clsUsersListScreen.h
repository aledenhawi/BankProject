#pragma once

#include <iostream>
#include <string>
#include "clsScreen.h"
#include <iomanip>
#include <vector>
#include "clsBankUser.h"

using namespace std;

class clsUsersListScreen : protected clsScreen
{
protected:


	static void _PrintUserRecordLine(clsBankUser UserList)
	{
		cout << setw(8) << left << "" << left << setw(15) << "| " + UserList.Username;
		cout << left << setw(25) << "| " + UserList.FullName();
		cout << left << setw(14) << "| " + UserList.Phone;
		cout << left << setw(30) << "| " + UserList.Email;
		cout << left << setw(10) << "| " + UserList.Password;
		cout << left << setw(12) << "| " + to_string(UserList.Permissions);
	}

public:

	static void ShowUsersList()
	{
		vector <clsBankUser> UserList = clsBankUser::GetUsersList();

		string Title = "User List Screen";

		string Subtitle = "    (" + to_string(UserList.size()) + ") User(s) ";


		_DrawScreenHeader(Title, Subtitle);

		// Print The Header
		cout << setw(8) << left << "" << "-------------------------------------------------------------------------------------------------------------\n\n";
		cout << setw(8) << left << "" << left << setw(15) << "|Username";
		cout << left << setw(25) << "|Full Name";
		cout << left << setw(14) << "|Phone";
		cout << left << setw(30) << "|Email";
		cout << left << setw(10) << "|Password";
		cout << left << setw(12) << "|Permissions\n\n";
		cout << setw(8) << left << "" << "-------------------------------------------------------------------------------------------------------------\n\n";

		// check if the file empty
		if (UserList.size() == 0)
		{
			cout << "\n\n                There is no Users In the system                         \n\n";
		}
		else
		{
			// Print Clients Record
			for (clsBankUser& U : UserList)
			{
				_PrintUserRecordLine(U);
				cout << endl;
			}
		}
		//Print The footer
		cout << setw(8) << left << "" << "-------------------------------------------------------------------------------------------------------------\n\n";
	}
};

