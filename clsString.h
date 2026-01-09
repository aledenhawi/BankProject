#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <cctype>

using namespace std;

class clsString
{

	string _Value;

public:

	clsString()
	{
		_Value = "";
	}

	clsString(string Value)
	{
		_Value = Value;
	}

	static short CountSpecificLetter(string String, char RepeatedChar, bool MatchCase = true)
	{
		short Counter = 0;

		for (short i = 0; i < String.length(); i++)
		{

			if (MatchCase)
			{
				if (String[i] == RepeatedChar)
					Counter++;
			}
			else
			{
				if (tolower(String[i]) == tolower(RepeatedChar))
					Counter++;
			}
		}
		return Counter;
	}

	short CountSpecificLetter(char RepeatedChar, bool MatchCase = true)
	{
		return CountSpecificLetter(_Value, RepeatedChar, MatchCase);
	}

	enum enWhatToCount { All = 1 , Capital = 2 , Small = 3 };

	static short CountLetters(string S1 , enWhatToCount WhatToCount = enWhatToCount::All)
	{
		short counter = 0;

			if (WhatToCount == enWhatToCount::All)
			{
				for (short i = 0; i < S1.length(); i++)
				{
					if (isalpha(S1[i]))
						counter++;
				}	
				return counter;
     		}
			else if (WhatToCount == enWhatToCount::Capital)
			{
				return CountCapitalLetters(S1);
			}
			else
			{
				return CountSmallLetters(S1);
			}
	}

	short CountLetters(enWhatToCount WhatToCount = enWhatToCount::All)
	{
		return CountLetters(_Value, WhatToCount);
	}

	static short CountCapitalLetters(string S1)
	{
		short counter = 0;

		for (short i = 0; i < S1.length(); i++)
		{
			if (isalpha(S1[i]))
			{
				if (isupper(S1[i]))
					counter++;
			}
		}

		return counter;
	}
	
	short CountCapitalLetters()
	{
		return CountCapitalLetters(_Value);
	}

	static short CountSmallLetters(string S1)
	{
		short counter = 0;

		for (short i = 0; i < S1.length(); i++)
		{
			if (isalpha(S1[i]))
			{
				if (islower(S1[i]))
					counter++;
			}
		}

		return counter;
	}

	short CountSmallLetters()
	{
		return CountSmallLetters(_Value);
	}

	static short CountWords(string String)
	{
		string delim = " ";
		string sWord = "";
		short pos = 0;
		short Counter = 0;

		while ((pos = String.find(delim)) != std::string::npos)
		{
			sWord = String.substr(0, pos);
			if (sWord != "")
			{
				Counter++;
			}
			String.erase(0, pos + delim.length());
		}
		if (String != "")
		{
			Counter++;
		}

		return Counter;
	}

	short CountWords()
	{
		return CountWords(_Value);
	}

	static short CountVowels(string S1)
	{
		short Counter = 0;

		for (short i = 0; i < S1.length(); i++)
		{
			if (IsVowel(S1[i]))
				Counter++;
		}
		return Counter;
	}

	short CountVowels()
	{
		return CountVowels(_Value);
	}

	static short Length(string S1)
	{
		return S1.length();
	}

	short Length()
	{
		return _Value.length();
	}

   void SetValue(string Value)
{
	_Value = Value;
}

   string GetValue()
{
	return _Value;
}

    __declspec(property(get = GetValue, put = SetValue)) string Value;

	static string TrimLeft(string S1)
	{

		for (short i = 0; i < S1.length(); i++)
		{
			if (S1[i] != ' ')
			{
				return S1.substr(i, S1.length() - i);
			}

		}

		return "";
	}

	string TrimLeft()
	{
		return TrimLeft(_Value);
	}

	static string TrimRight(string S1 )
	{

		for (short i = S1.length() - 1; i > 0; i--)
		{
			if (S1[i] != ' ')
			{
				return S1.substr(0, i + 1);
			}

		}

		return "";
	}

	string TrimRight()
	{
		return TrimRight(_Value);
	}

	static string Trim(string  S1)
	{
		return TrimLeft(TrimRight(S1));
	}

	string Trim()
	{
		return Trim(_Value);
	}

	static string UpperFirstLetterOfEachWord(string& String)
	{

		bool IsFirstLetter = true;

		for (short i = 0; i < String.length(); i++)
		{
			if (String[i] != ' ' && IsFirstLetter)
			{
				if (islower(String[i]))
				{
					String[i] = toupper(String[i]);
				}
			}
			IsFirstLetter = ((String[i] == ' ') ? true : false);
		}
		return String;
	}

	void UpperFirstLetterOfEachWord()
	{
	_Value = UpperFirstLetterOfEachWord(_Value);
	}

	static string LowerFirstLetterOfEachWord(string& String)
	{

		bool IsFirstLetter = true;

		for (short i = 0; i < String.length(); i++)
		{
			if (String[i] != ' ' && IsFirstLetter)
			{
				if (isupper(String[i]))
				{
					String[i] = tolower(String[i]);
				}
			}
			IsFirstLetter = ((String[i] == ' ') ? true : false);
		}

	}

	void LowerFirstLetterOfEachWord()
	{
		_Value = LowerFirstLetterOfEachWord(_Value);
	}

	static string UpperAllLetters(string String)
	{
		for (short i = 0; i < String.length(); i++)
		{
			String[i] = toupper(String[i]);
		}
		return String;
	}

	void UpperAllLetters()
	{
		_Value = UpperAllLetters(_Value);
	}

	static string LowerAllString(string String)
	{
		for (short i = 0; i < String.length(); i++)
		{
			String[i] = tolower(String[i]);
		}
		return String;
	}

	void LowerAllString()
	{
		_Value = LowerAllString(_Value);
	}

	static char InvertLetterCase(char Character)
	{
		return (isupper(Character)) ? tolower(Character) : toupper(Character);
	}

	static string InvertAllStringLettersCase(string String)
	{
		for (short i = 0; i < String.length(); i++)
		{
			String[i] = InvertLetterCase(String[i]);
		}
		return String;
	}

	void InvertAllStringLettersCase()
	{
		_Value = InvertAllStringLettersCase(_Value);
	}

	static bool IsVowel(char Char)
	{
		Char = tolower(Char);

		return (Char == 'i' || Char == 'o' || Char == 'e' || Char == 'a' || Char == 'u');

	}

	static vector<string> Split(string S1, string Delim)
	{

		vector<string> vString;

		short pos = 0;
		string sWord; // define a string variable  

		// use find() function to get the position of the delimiters  
		while ((pos = S1.find(Delim)) != std::string::npos)
		{
			sWord = S1.substr(0, pos); // store the word   
			// if (sWord != "")
			// {
			vString.push_back(sWord);
			//}

			S1.erase(0, pos + Delim.length());  /* erase() until position and move to next word. */
		}

		if (S1 != "")
		{
			vString.push_back(S1); // it adds last word of the string.
		}

		return vString;

	}

	vector <string> Split(string Delim = " ")
	{
		return Split(_Value , Delim);
	}

    static string JoinString(vector <string> vString, string Delim)
	{
		string String = "";

		for (string& S : vString)
		{
			String += S + Delim;
		}
		String.erase(String.length() - Delim.length(), String.length());

		return String;
	}

    static string JoinString(string arr[], short Length, string Delim)
	{
		string String;

		for (short i = 0; i <= Length - 1; i++)
		{
			String += arr[i] + Delim;
		}
		String.erase(String.length() - Delim.length(), String.length());

		return String;
	}

	static string ReverseWordsInString(string String)
	{
		string S2 = "";

		vector <string> vString = Split(String, " ");

		vector <string>::iterator Iterator = vString.end();

		while (Iterator != vString.begin())
		{
			Iterator--;

			S2 += *Iterator + " ";
		}

		return S2.substr(0, S2.length() - 1);

	}

	void ReverseWordsInString()
	{
		_Value = ReverseWordsInString(_Value);
	}

	static string ReplaceWord(string S1, string StringToReplace, string sReplaceTo, bool MatchCase = true)
	{
		short pos = 0;

		if (!MatchCase)
		{
			while ((pos = LowerAllString(S1).find(LowerAllString(StringToReplace))) != string::npos)
			{

				S1.erase(pos, StringToReplace.length());
				S1.insert(pos, sReplaceTo);
			}
		}
		else
		{
			while ((pos = S1.find(StringToReplace)) != string::npos)
			{

				S1.erase(pos, StringToReplace.length());
				S1.insert(pos, sReplaceTo);
			}
		}
		return S1;
	}

	void ReplaceWord(string StringToReplace, string sReplaceTo, bool MatchCase = true)
	{
		_Value = ReplaceWord(_Value, StringToReplace, sReplaceTo, MatchCase);
	}

	static string RemovePunctuations(string S1)
	{
		string S2 = "";
		for (short i = 0; i < S1.length(); i++)
		{
			if (!ispunct(S1[i]))
			{
				S2 += S1[i];
			}

		}
		return S2;
	}

	void RemovePunctuations()
	{
		_Value = RemovePunctuations(_Value);
	}

};

