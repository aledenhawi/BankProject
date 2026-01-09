#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "clsString.h"

using namespace std;

class clsCurrency
{
private:

    static clsCurrency _ConvertLineToCurrencyObject(string Line, string Separator = "#//#")
    {
        vector <string> vCurrency = clsString::Split(Line, Separator);
        return clsCurrency(enMode::UpdateMode, vCurrency.at(0), vCurrency.at(1), vCurrency.at(2), stof(vCurrency.at(3)));

    }

    static vector <clsCurrency> _LoadCurrenciesDataFromFile()
    {
        vector <clsCurrency> vCurrency;
        fstream MyFile;

        MyFile.open("Currencies.txt", ios::in);

        string Line;

        if (MyFile.is_open())
        {
            while (getline(MyFile, Line))
            {
                vCurrency.push_back(_ConvertLineToCurrencyObject(Line));
            }
            MyFile.close();
        }
        return vCurrency;
    }

    string _ConvertCurrencyObjectToLine(clsCurrency Currency, string Separator = "#//#")
    {
        string Line;
        Line = Currency.Country() + Separator;
        Line += Currency.CurrencyCode() + Separator;
        Line += Currency.CurrencyName() + Separator;
        Line += to_string(Currency._Rate);
        return Line;
    }

    void _SaveCurrencyDataToFile(vector <clsCurrency> vCurrency)
    {
        fstream MyFile;

        MyFile.open("Currencies.txt", ios::out);

        if (MyFile.is_open())
        {
            for (clsCurrency& C : vCurrency)
            {
                    MyFile << _ConvertCurrencyObjectToLine(C) << endl;
            }
            MyFile.close();
        }
    }

    enum enMode { EmptyMode = 0, UpdateMode = 2 };
    enMode _Mode;

    string _Country;
    string _CurrencyCode;
    string _CurrencyName;
    float _Rate;

    void _Update()
    {
        vector <clsCurrency> vCurrency = _LoadCurrenciesDataFromFile();

        for(clsCurrency &C : vCurrency)
        {
           if(C.CurrencyCode() == _CurrencyCode)
           {
               C = *this;
               break;
           }
        }
        _SaveCurrencyDataToFile(vCurrency);
    }

    static clsCurrency _GetEmptyCurrencyObject()
    {
        return clsCurrency(enMode::EmptyMode, "", "", "", 0);
    }

public:

    clsCurrency(enMode Mode, string Country, string CurrencyCode, string CurrencyName, float Rate)
    { 
        _Mode = Mode;
        _Country = Country;
        _CurrencyCode = CurrencyCode;
        _CurrencyName = CurrencyName;
        _Rate = Rate;
    }
    
    string Country() { return _Country; }

    string CurrencyCode() { return _CurrencyCode; }
  
    string CurrencyName() { return _CurrencyName; }

    float Rate() { return _Rate; }

    void UpdateRate(float NewRate)
    {
        _Rate = NewRate; 
        _Update();
    }

    static clsCurrency FindByCode(string CurrencyCode)
    {
        CurrencyCode = clsString::UpperAllLetters(CurrencyCode);
        fstream MyFile;
        string Line = "";
        clsCurrency Currency = _GetEmptyCurrencyObject();

        MyFile.open("Currencies.txt", ios::in); // Read only mode

        if (MyFile.is_open())
        {
            while (getline(MyFile, Line))
            {
                Currency = _ConvertLineToCurrencyObject(Line);
                if (Currency.CurrencyCode() == CurrencyCode)
                {
                    MyFile.close();
                    return Currency;
                }
            }
            MyFile.close();
        }
        return _GetEmptyCurrencyObject();
    }

    bool IsEmpty()
    {
        return (_Mode == enMode::EmptyMode);
    }

    static clsCurrency FindByCountry(string Country)
    {
        Country = clsString::UpperAllLetters(Country);
        fstream MyFile;
        string Line = "";
        clsCurrency Currency = _GetEmptyCurrencyObject();

        MyFile.open("Currencies.txt", ios::in); // Read only mode

        if (MyFile.is_open())
        {
            while (getline(MyFile, Line))
            {
                Currency = _ConvertLineToCurrencyObject(Line);
                if (clsString::UpperAllLetters(Currency.Country()) == Country)
                {
                    MyFile.close();
                    return Currency;
                }
            }
            MyFile.close();
        }
        return _GetEmptyCurrencyObject();
    }

    static bool IsCurrencyExist(string Code)
    {
        clsCurrency Currency = FindByCode(Code);
        return (!Currency.IsEmpty());
    }

    static vector <clsCurrency> GetCurrenciesList()
    {
        return _LoadCurrenciesDataFromFile();
    }
    
    float ConvertToUSD(float Amount)
    {
        return Amount / _Rate;
    }

    float ConvertToOtherCurrency(float Amount , clsCurrency Currency2)
    {
        float AmountInUSD = ConvertToUSD(Amount);

        if(Currency2.CurrencyCode() == "USD")
        {
            return AmountInUSD;
        }
        return (float)(AmountInUSD * Currency2.Rate());
    }
};

