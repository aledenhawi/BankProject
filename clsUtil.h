
#pragma once
#include <iostream>
#include <string>
#include <ctime>
#include <cstdlib>
#include "clsDate.h"

using namespace std;

class clsUtil
{
public :
	// —„Ê“ ANSI ··√·Ê«‰
	static const string RED;
	static const string GREEN;
	static const string YELLOW;
	static const string BLUE;
	static const string MAGENTA;
	static const string CYAN;
	static const string RESET;

	static void Srand()
	{
		srand((unsigned)(time(NULL)));
	}

	static int RandomNumber(int From, int To)
	{
		int RandomNumber = rand() % (To - From + 1) + From;
		return RandomNumber;
	}

	static void Swap(int &A , int &B)
	{
		int temp = A;
		A = B;
		B = temp;
	}

	static void Swap(double& A, double& B)
	{
		double temp = A;
		A = B;
		B = temp;
	}

	static  void Swap(bool& A, bool& B)
	{
		bool Temp;

		Temp = A;
		A = B;
		B = Temp;
	}

	static  void Swap(char& A, char& B)
	{
		char Temp;

		Temp = A;
		A = B;
		B = Temp;
	}

	static void Swap(string& A, string& B)
	{
		string temp = A;
		A = B;
		B = temp;
	}

	static void Swap(clsDate& A, clsDate& B)
	{
		clsDate temp = A;
		A = B;
		B = temp;
	}

	static enum enCharType { SmallLetter = 1, CapitalLetter = 2, SpecialCharacter = 3, Digit = 4 , MixChar };
	
	static char GenerateRandomCharacter(enCharType CharType)
	{
		switch (CharType)
		{

		case enCharType::CapitalLetter:
		{
			return char(RandomNumber(65, 90));
			break;
		}
		case enCharType::SmallLetter:
		{
			return char(RandomNumber(97, 122));
			break;
		}
		case enCharType::SpecialCharacter:
		{
			return char(RandomNumber(33, 47));
			break;
		}
		case enCharType::Digit:
		{
			return char(RandomNumber(48, 57));
			break;
		}
		case enCharType::MixChar:
			return char(RandomNumber(48, 122));
		}
		return 0;
	}
	
	static string EncryptText(string Text, short EncryptionKey =16)
	{
		for (int i = 0; i < Text.length(); i++)
		{
			Text[i] = char(int(Text[i]) + EncryptionKey); // ≈“«Õ… ﬂ· Õ—› 2 
		}
		return Text;
	}
	
	static string DecryptText(string Text, short EncryptionKey = 16)
	{
		for (int i = 0; i < Text.length(); i++)
		{
			Text[i] = char(int(Text[i]) - EncryptionKey); // ≈—Ã«⁄ ﬂ· Õ—› 2 
		}
		return Text;
	}
	
	static string GenerateWord(enCharType CharType, short Length)
	{
		string Word = "";

		for (int j = 1; j <= Length; j++)
		{
			Word += GenerateRandomCharacter(CharType);
		}
		return Word;
	}
	
	static string GenerateKey(enCharType CharType = enCharType::CapitalLetter)
	{
		string Key = "";

		Key = GenerateWord(CharType,4) + "-";
		Key += GenerateWord(CharType,4) + "-";
		Key += GenerateWord(CharType,4) + "-";
		Key += GenerateWord(CharType,4);
		return Key;
	}

	static void GenerateKeys(int TotalKeys , enCharType CharType)
	{
		for (int i = 1; i <= TotalKeys; i++)
		{
			cout << "Key[" << i << "] : " << GenerateKey(CharType) << endl;
		}
	}

	static void ShuffleArray(int arr[100], int arrLength)
	{

		for (short i = 0; i < arrLength; i++)
		{
			Swap(arr[RandomNumber(0, arrLength - 1)], arr[RandomNumber(0, arrLength - 1)]);
		}

	}

	static void ShuffleArray(string arr[100], int arrLength)
	{

		for (short i = 0; i < arrLength; i++)
		{
			Swap(arr[RandomNumber(0, arrLength - 1)], arr[RandomNumber(0, arrLength - 1)]);
		}

	}

	static void FillArrayWithRandomNumbers(int Array[100], int& arrLength, int From , int To)
	{
		for (int i = 0; i < arrLength; i++)
			Array[i] = RandomNumber(From, To);
	}
	
    static void FillArrayWithRandomWords(string Array[100], int& arrLength , int WordLength , enCharType CharType)
	{
		for (int i = 0; i < arrLength; i++)
			Array[i] = GenerateWord(CharType, WordLength);
	}

	static void FillArrayWithRandomKeys(string Array[100], int& arrLength, enCharType CharType)
	{
		for (int i = 0; i < arrLength; i++)
			Array[i] = GenerateKey(CharType);
	}

	static string Taps(short TotalTaps)
	{
		string sTaps = "";
	for(short i = 0 ; i < TotalTaps ; i++)
	{
		sTaps += "\t";
	}
	return sTaps;
	}

	static string NumberToText(int Number)
	{
		if ((Number) == 0)
		{
			return "";
		}

		if (Number >= 1 && Number <= 19)
		{
			string arr[] =
			{ "" , "One","Tow","Three","Four","Five","six","Seven"
				,"Eight","Nine","Ten","Eleven","Twelve","Thirteen",
				"Fourteen","Fifteen","SixTeen","SevenTeen","Eighteen","Nineteen"
			};
			return arr[Number] + " ";
		}
		else if (Number >= 20 && Number <= 99)
		{
			string arr[] = { ""  , "", "Twenty ","Thirty ","Fourty ","Fifty ","Sixty ","Seventy","Eighty","Ninety" };
			return arr[Number / 10] + " " + NumberToText(Number % 10);
		}
		else if (Number >= 100 && Number <= 199)
		{
			return "One Hundred " + NumberToText(Number % 100);
		}
		else if (Number >= 200 && Number <= 999)
		{
			return NumberToText(Number / 100) + "Hundreds " + NumberToText(Number % 100);
		}
		else if (Number >= 1000 && Number <= 1999)
		{
			return "One Thousand " + NumberToText(Number % 1000);
		}
		else if (Number >= 2000 && Number <= 999999)
		{
			return NumberToText(Number / 1000) + "Thousand " + NumberToText(Number % 1000);
		}
		else if (Number >= 1000000 && Number <= 1999999)
		{
			return "One Million " + NumberToText(Number % 1000000);
		}
		else if (Number >= 2000000 && Number <= 999999999)
		{
			return NumberToText(Number / 1000000) + "Millions " + NumberToText(Number % 1000000);
		}
		else if (Number >= 1000000000 && Number <= 1999999999)
		{
			return "One Billion " + NumberToText(Number % 1000000);
		}
		else if (Number >= 2000000 && Number <= 999999999)
		{
			return NumberToText(Number / 1000000) + "Billion " + NumberToText(Number % 1000000);
		}

	}

};

const string clsUtil::RED = "\033[31m";
const string clsUtil::GREEN = "\033[32m";
const string clsUtil::YELLOW = "\033[33m";
const string clsUtil::BLUE = "\033[34m";
const string clsUtil::MAGENTA = "\033[35m";
const string clsUtil::CYAN = "\033[36m";
const string clsUtil::RESET = "\033[0m";