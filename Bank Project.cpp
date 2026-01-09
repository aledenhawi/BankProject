#include <iostream>
#include <string>
#include "clsLoginScreen.h"
#include "clsCurrencyCalculatorScreen.h"
using namespace std;

int main()
{

	while (true)
	{
		if (!clsLoginScreen::ShowLoginScreen())
			break;
	}


	return 0;
}