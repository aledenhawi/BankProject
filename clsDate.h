#pragma once
#pragma warning (disable : 4996)

#include<iostream>
#include<string>
#include<iomanip>
#include"clsString.h";
#include<cctype>

using namespace std;

class clsDate 
{
	
	short _Year;
	short _Month;
	short _Day;

public:

	clsDate()
    {
		*this = SystemDate();
    }

	clsDate(string sDate)
	{
		*this  =  StringToDate(sDate);
	}
	
	clsDate(short Day , short Month , short Year)
	{
		this->_Day = Day;
		this->_Month = Month;
		this->_Year = Year;
	}

	clsDate(short DayOrderInYear , short Year)
	{
		*this = GetDateFromDayOrderInYear(DayOrderInYear, Year);
	}

    //Porperty set
	void SetYear(short Year)
	{
		_Year = Year;
	}

	//Property get
	short GetYear()
	{
		return _Year;
	}

	__declspec(property(get = GetYear, put = SetYear)) short Year;

	//Porperty set
	void SetMonth(short Month)
	{
		_Month = Month;
	}

	//Property get
	short GetMonth()
	{
		return _Month;
	}

	__declspec(property(get = GetMonth, put = SetMonth)) short Month;

	//Porperty set
	void SetDay(short Day)
	{
		_Day = Day;
	}

	//Property get
	short GetDay()
	{
		return _Day;
	}

	__declspec(property(get = GetDay, put = SetDay)) short Day;



	static short DaysInYear(short Year)
	{
		return IsLeapYear(Year) ? 366 : 365;
	}

	short DaysInYear()
	{
		return DaysInYear(_Year);
	}

	static short HoursInYear(short Year)
	{
		return DaysInYear(Year) * 24;
	}

	short HoursInYear()
	{
		return DaysInYear() * 24;
	}

	static int MinuetsInYear(short Year)
	{
		return HoursInYear(Year) * 60;
	}

	int MinuetsInYear()
	{
		return HoursInYear() * 60;
	}

	static int SecondsInYear(short Year)
	{
		return MinuetsInYear(Year) * 60;
	}

	int SecondsInYear()
	{
		return MinuetsInYear() * 60;
	}

    static short NumberOfDaysInAMonth(short Year, short Month)
	{
		if (Month < 1 || Month > 12)
		{
			return 0;
		}
		short NumberOfDays[13] = { 0,31,0,31,30,31,30,31,31,30,31,30,31 };
		return(Month == 2) ? (IsLeapYear(Year) ? 29 : 28) : NumberOfDays[Month];
	}

	short NumberOfDaysInAMonth()
	{
		return NumberOfDaysInAMonth(_Year,_Month);
	}

	static short HoursInMonth(short Year, short Month)
	{
		return NumberOfDaysInAMonth(Year, Month) * 24;
	}

	short HoursInMonth()
	{
		return NumberOfDaysInAMonth() * 24;
	}
	
	static int MinuetsInMonth(short Year, short Month)
	{
		return HoursInMonth(Year, Month) * 60;
	}

	int MinuetsInMonth()
	{ 
		return HoursInMonth() * 60;
	}

	static int SecondsInMonth(short Year, short Month)
	{
		return MinuetsInMonth(Year, Month) * 60;
	}

	int SecondsInMonth()
	{
		return MinuetsInMonth() * 60;
	}

	static bool IsLeapYear(short Year)
	{
		return (Year % 4 == 0 && Year % 100 != 0) || (Year % 400 == 0);
	}

	bool IsLeapYear()
	{
		return IsLeapYear(_Year);
	}

	static clsDate GetDateFromDayOrderInYear(short DayOrderInYear, short Year)
	{
		clsDate Date;
		short DaysInAMonth;
		short RemainingDays = DayOrderInYear;
		Date._Month = 1;
		Date._Year = Year;

		while (true)
		{
			DaysInAMonth = NumberOfDaysInAMonth(Year, Date._Month);
			if (DaysInAMonth < RemainingDays)
			{
				RemainingDays -= DaysInAMonth;
				Date._Month++;
			}
			else if (!(DaysInAMonth < RemainingDays))
			{
				Date._Day = RemainingDays;
				break;
			}
		}

		return Date;
	}

	static clsDate StringToDate(string sDate)
	{
		clsDate Date;

		vector <string> vDate = clsString::Split(sDate, "/");

		Date._Year = stoi(vDate.at(2));
		Date._Month = stoi(vDate.at(1));
		Date._Day = stoi(vDate.at(0));

		return Date;
	}

	static short DayOfWeekOrder(clsDate Date)
	{
		short a = (14 - Date._Month) / 12;
		short y = Date._Year - a;
		short m = Date._Month + (12 * a) - 2;

		short DayWeekIndex = (Date._Day + y + (y / 4) - (y / 100) + (y / 400) + ((31 * m) / 12)) % 7;
		return DayWeekIndex;
	}

    short DayOfWeekOrder()
	{
		return DayOfWeekOrder(*this);
	}

	static string DayShortName(short Index)
	{
		string WeekDays[7] = { "Sun" , "Mon" , "Tue" , "Wen" , "Thu" , "Fri" , "Sat" };
		return WeekDays[Index];
	}
    
	string DayShortName()
	{
		return DayShortName(DayOfWeekOrder());
	}
	
	static string MonthShortName(short Month)
	{
		string MonthName[13] = { "" , "Jan" , "Feb" , "Mar" , "Apr" , "May" , "jun" , "jul" ,"Aug" , "Sep" , "Oct" , "Nov" , "Dec" };
		return MonthName[Month];
	}

	string MonthShortName()
	{
		return MonthShortName(_Month);
	}

    static clsDate SystemDate()
	{
		time_t t = time(0);   // get time now

		tm* tDateNow = localtime(&t);
		short Year, Month, Day;

		Year = tDateNow->tm_year + 1900;
		Month = tDateNow->tm_mon + 1;
		Day = tDateNow->tm_mday;
	
		return clsDate(Day, Month, Year);
	}

    static string DateToString(clsDate Date)
    {
		return to_string(Date._Day) + "/" + to_string(Date._Month) + "/" + to_string(Date._Year);
	}

	string DateToString()
	{
		return DateToString(*this);
	}

	static void Print(clsDate Date)
	{
	cout << DateToString(Date) << endl;
	}

	void Print()
	{
	cout << DateToString() << endl;
	}
	
	static void PrintMonthCalendar(clsDate Date)
	{
		int Current = DayOfWeekOrder(Date),
			NumberOfDays = NumberOfDaysInAMonth(Date._Year, Date._Month);

		printf("\n  _________________%s______________\n\n", MonthShortName(Date._Month).c_str());
		printf("  Sun  Mon  Tue  Wen  Thu  Fri  Sat\n");

		short k;

		for (k = 0; k < Current; k++)
			printf("     ");

		for (short i = 1; i <= NumberOfDays; i++)
		{
			printf("%5d", i);

			if (++k == 7)
			{
				k = 0;
				cout << endl;
			}

		}
		printf("\n  _________________________________\n\n");
	}

	void PrintMonthCalendar()
	{
		PrintMonthCalendar(*this);
	}

	static void PrintYearCalendar(short Year)
	{
		printf("\n\n  ----------------------------------\n\n");
		printf("             Calendar - %d              \n\n", Year);
		printf("  ----------------------------------\n");

		for (short i = 1; i <= 12; i++)
		{
			PrintMonthCalendar(clsDate(1,i,Year));
			cout << endl;
		}
	}

	void PrintYearCalendar()
	{
		PrintYearCalendar(_Year);
	}

	static short NumberOfDaysFromBeginningOfTheYear(clsDate Date)
	{
		short TotalDays = 0;

		for (short i = 1; i < Date._Month; i++)
		{
			TotalDays += NumberOfDaysInAMonth(Date._Year, i);
		}
		TotalDays += Date._Day;

		return TotalDays;
	}

	short NumberOfDaysFromBeginningOfTheYear()
	{
		return NumberOfDaysFromBeginningOfTheYear(*this);
	}

	static clsDate AddDays(clsDate Date, short DaysToAdd)
	{
		short RemainingDays = DaysToAdd + NumberOfDaysFromBeginningOfTheYear(Date);
		short MonthDays = 0;

		Date._Month = 1;

		while (true)
		{
			MonthDays = NumberOfDaysInAMonth(Date._Year, Date._Month);
			if (RemainingDays > MonthDays)
			{
				RemainingDays -= MonthDays;
				Date._Month++;

				if (Date._Month > 12)
				{
					Date._Month = 1;
					Date._Year++;
				}
			}
			else
			{
				Date._Day = RemainingDays;
				break;
			}
		}

		return Date;

	}

	clsDate AddDays(short DaysToAdd)
	{
		return AddDays(*this, DaysToAdd);
	}

	static bool IsDate1BeforeDate2(clsDate Date1, clsDate Date2)
	{
		return (Date2._Year > Date1._Year) ? true : (Date2._Year == Date1._Year ? (Date2._Month > Date1._Month ? true : (Date2._Month == Date1._Month ? Date2._Day > Date1._Day  : false)) : false);
	}

	bool IsDateBeforeDate2(clsDate Date2)
	{
		IsDate1BeforeDate2(*this, Date2);
	}

	static bool IsDate1EqualDate2(clsDate Date1, clsDate Date2)
	{
		return (Date2._Year == Date1._Year) ? (Date2._Month == Date1._Month ? Date2._Day == Date1._Day : false) : false;
	}

	bool IsDateEqualDate2(clsDate Date2)
	{
		IsDate1EqualDate2(*this, Date2);
	}

	static bool IsLastDayInMonth(clsDate Date)
	{
		return (NumberOfDaysInAMonth(Date._Year, Date._Month) == Date._Day);
	}

	bool IsLastDayInMonth()
	{
		return IsLastDayInMonth(*this);
	}

	static bool IsLastMonthInYear(short Month)
	{
		return (Month == 12);
	}

	bool IsLastMonthInYear()
	{
		return IsLastMonthInYear(_Month);
	}

	static clsDate AddOneDay(clsDate Date)
	{
		IsLastDayInMonth(Date) ? (IsLastMonthInYear(Date._Month) ? (Date._Year++, Date._Month = 1, Date._Day = 1) : (Date._Month++, Date._Day = 1)) : Date._Day++;
		return Date;
	}

	clsDate AddOneDay()
	{
		return AddOneDay(*this);
	}

	static void SwapDates(clsDate &Date1, clsDate& Date2)
	{
		clsDate TempDate;
		TempDate = Date1;
		Date1 = Date2;
		Date2 = TempDate;
	}

	void SwapDates(clsDate& Date2)
	{
		SwapDates(*this, Date2);
	}

	static short GetDifferenceInDays(clsDate Date1, clsDate Date2, bool IncludeEndDay = false)
	{
		short Days = 0;
		short SwapflagValue = 1;

		if (!IsDate1BeforeDate2(Date1, Date2))
		{
			SwapDates(Date1, Date2);
			SwapflagValue = -1;
		}

		while (IsDate1BeforeDate2(Date1, Date2))
		{
			Date1 = AddOneDay(Date1);
			Days++;
		}
		return IncludeEndDay ? (++Days * SwapflagValue) : (Days * SwapflagValue);
	}

	short GetDifferenceInDays(clsDate Date2, bool IncludeEndDay = false)
	{
		return GetDifferenceInDays(*this, Date2, IncludeEndDay);
	}

	static clsDate IncreaseDateByXDay(clsDate & Date, short X)
	{
		for (short i = 0; i < X; i++)
		{
			Date = AddOneDay(Date);
		}
		return Date;
	}

	void IncreaseDateByXDay(short X)
	{
		IncreaseDateByXDay(*this, X);
	}

	static clsDate IncreaseDateByOneWeek(clsDate& Date)
	{
		for (short i = 0; i < 7; i++)
		{
			Date = AddOneDay(Date);
		}
		return Date;
	}

	void IncreaseDateByOneWeek()
	{
	 IncreaseDateByOneWeek(*this);
	}

	static clsDate IncreaseDateByXWeek(clsDate& Date, short X)
	{
		for (short i = 0; i < X; i++)
		{
			Date = IncreaseDateByOneWeek(Date);
		}
		return Date;
	}

	void IncreaseDateByXWeek(short X)
	{
		 IncreaseDateByXWeek(*this, X);
	}

	static clsDate IncreaseDateByOneMonth(clsDate& Date)
	{
		IsLastMonthInYear(Date._Month) ? Date._Year++, Date._Month = 1 : Date._Month++;
		short NumberOfDaysInTheCurrentMonth = NumberOfDaysInAMonth(Date._Year, Date._Month);
		if (NumberOfDaysInTheCurrentMonth > Date._Day)
		{
			Date._Day = NumberOfDaysInTheCurrentMonth;
		}
		return Date;
	}

	void IncreaseDateByOneMonth()
	{
		 IncreaseDateByOneMonth(*this);
	}

	static clsDate IncreaseDateByXMonth(clsDate& Date, short X)
	{
		for (short i = 0; i < X; i++)
		{
			Date = IncreaseDateByOneMonth(Date);
		}
		return Date;
	}

	void IncreaseDateByXMonth(short X)
	{
		 IncreaseDateByXMonth(*this, X);
	}

	static clsDate IncreaseDateByOneYear(clsDate& Date)
	{
		Date._Year++;
		return Date;
	}

	void IncreaseDateByOneYear()
	{
		 IncreaseDateByOneYear(*this);
	}

	static clsDate IncreaseDateByXYear(clsDate& Date, short X)
	{
		Date._Year += X;
		return Date;
	}

	void IncreaseDateByXYear(short X)
	{
		IncreaseDateByXYear(*this, X);
	}

	static clsDate IncreaseDateByOneDecade(clsDate& Date)
	{
		Date = IncreaseDateByXYear(Date, 10);
		return Date;
	}

	void IncreaseDateByOneDecade()
	{
		 IncreaseDateByOneDecade(*this);
	}

	static clsDate IncreaseDateByXDecades(clsDate& Date, short X)
	{
		Date._Year += (X * 10);
		return Date;
	}

	void IncreaseDateByXDecades(short X)
	{
		 	IncreaseDateByXDecades(*this , X);
	}

	static clsDate IncreaseDateByOneCentury(clsDate& Date)
	{
		Date = IncreaseDateByXYear(Date, 100);
		return Date;
	}

	void IncreaseDateByOneCentury()
	{
		IncreaseDateByOneCentury(*this);
	}

	static clsDate IncreaseDateByOneMillennium(clsDate& Date)
	{
		Date = IncreaseDateByXYear(Date, 1000);
		return Date;
	}

	void IncreaseDateByOneMillennium()
	{
		 IncreaseDateByOneMillennium(*this);
	}

	static clsDate DecreaseDateByOneDay(clsDate& Date)
	{
		(Date._Day == 1) ? (Date._Month == 1) ? (Date._Year--, Date._Month = 12, Date._Day = 31) : (--Date._Month, Date._Day) = NumberOfDaysInAMonth(Date._Year, Date._Month) : --Date._Day;
		return Date;
	}

	void DecreaseDateByOneDay()
	{
		 DecreaseDateByOneDay(*this);
	}

	static clsDate DecreaseDateByXDay(clsDate& Date, short X)
	{
		for (short i = 0; i < X; i++)
		{
			Date = DecreaseDateByOneDay(Date);
		}
		return Date;
	}

	void DecreaseDateByXDay(short X)
	{
		 DecreaseDateByXDay(*this, X);
	}

	static clsDate DecreaseDateByOneWeek(clsDate& Date)
	{
		for (short i = 0; i < 7; i++)
		{
			Date = DecreaseDateByOneDay(Date);
		}
		return Date;
	}

	void DecreaseDateByOneWeek()
	{
		 DecreaseDateByOneWeek(*this);
	}

	static clsDate DecreaseDateByXWeek(clsDate& Date, short X)
	{
		for (short i = 0; i < X; i++)
		{
			Date = DecreaseDateByOneWeek(Date);
		}
		return Date;
	}

	void DecreaseDateByXWeek(short X)
	{
		 DecreaseDateByXWeek(*this, X);
	}

	static clsDate DecreaseDateByOneMonth(clsDate& Date)
	{
		(Date._Month == 1) ? Date._Year--, Date._Month = 12 : Date._Month--;

		short NumberOfDaysInTheCurrentMonth = NumberOfDaysInAMonth(Date._Year, Date._Month);
		if (NumberOfDaysInTheCurrentMonth < Date._Day)
		{
			Date._Day = NumberOfDaysInTheCurrentMonth;
		}
		return Date;
	}

	void DecreaseDateByOneMonth()
	{
		 DecreaseDateByOneMonth(*this);
	}

	static clsDate DecreaseDateByXMonth(clsDate& Date, short X)
	{
		for (short i = 0; i < X; i++)
		{
			Date = DecreaseDateByOneMonth(Date);
		}
		return Date;
	}

	void DecreaseDateByXMonth(short X)
	{
		 DecreaseDateByXMonth(*this, X);
	}

	static clsDate DecreaseDateByOneYear(clsDate& Date)
	{
		Date._Year--;
		return Date;
	}

	void DecreaseDateByOneYear()
	{
		 DecreaseDateByOneYear(*this);
	}

	static clsDate DecreaseDateByXYear(clsDate& Date, short X)
	{
		Date._Year -= X;
		return Date;
	}

	void DecreaseDateByXYear(short X)
	{
		 DecreaseDateByXYear(*this, X);
	}

	static clsDate DecreaseDateByOneDecade(clsDate& Date)
	{
		Date = DecreaseDateByXYear(Date, 10);
		return Date;
	}

	void DecreaseDateByOneDecade()
	{
		 DecreaseDateByOneDecade(*this);
	}

	static clsDate DecreaseDateByXDecades(clsDate& Date, short X)
	{
		Date._Year -= (X * 10);
		return Date;
	}

	void DecreaseDateByXDecades(short X)
	{
		 DecreaseDateByXDecades(*this, X);
	}

	static clsDate DecreaseDateByOneCentury(clsDate& Date)
	{
		Date = DecreaseDateByXYear(Date, 100);
		return Date;
	}

	void DecreaseDateByOneCentury()
	{
		 DecreaseDateByOneCentury(*this);
	}

	static clsDate DecreaseDateByOneMillennium(clsDate& Date)
	{
		Date._Year -= 1000;
		return Date;
	}

	void DecreaseDateByOneMillennium()
	{
		 DecreaseDateByOneMillennium(*this);
	}

	static bool IsEndOfWeek(clsDate Date)
	{
		return (DayOfWeekOrder(Date) == 6);
	}

	bool IsEndOfWeek()
	{
		return IsEndOfWeek(*this);
	}

	static bool IsWeekend(clsDate Date)
	{
		short DayOfWeek = DayOfWeekOrder(Date);
		return (DayOfWeek == 6 || DayOfWeek == 5);
	}

	bool IsWeekend()
	{
		return IsWeekend(*this);
	}

	static bool IsBusinessDay(clsDate Date)
	{
		return (!IsWeekend(Date));
	}

	bool IsBusinessDay()
	{
		return IsBusinessDay(*this);
	}

	static enum enDateCompare { Before = -1, Equal = 0, After = 1 };

	static bool IsValidDate(clsDate Date)
	{
		if (Date.Day > 31 || Date.Day < 1)
			return false;
		if (Date.Month > 12 || Date.Month < 1)
			return false;

		short DaysInMonth = NumberOfDaysInAMonth(Date.Year, Date.Month);

		if (Date.Day > DaysInMonth)
			return false;

		return true;
	}

	bool IsValid()
	{
		return IsValidDate(*this);
	}

	static string FormatDate(clsDate Date, string DateFormat = "dd/mm/yyyy")
	{
		string FormatedDateString = "";
		FormatedDateString = clsString::ReplaceWord(DateFormat, "yyyy", to_string(Date._Year));
		FormatedDateString = clsString::ReplaceWord(FormatedDateString, "mm", to_string(Date._Month));
		FormatedDateString = clsString::ReplaceWord(FormatedDateString, "dd", to_string(Date._Day));
		return FormatedDateString;
	}

	string FormatDate(string DateFormat = "dd/mm/yyyy")
	{
		return FormatDate(*this, DateFormat);
	}

	static short DaysUntilTheEndOfWeek(clsDate Date)
	{
		return 6 - DayOfWeekOrder(Date);
	}

	short DaysUntilTheEndOfWeek()
	{
		return DaysUntilTheEndOfWeek(*this);
	}

	static short DaysUntilTheEndOfMonth(clsDate Date)
	{
		clsDate EndOfMonthDate;
		EndOfMonthDate._Day = NumberOfDaysInAMonth(Date._Year, Date._Month);
		EndOfMonthDate._Month = Date._Month;
		EndOfMonthDate._Year = Date._Year;

		return GetDifferenceInDays(Date, EndOfMonthDate, true);
	}

	short DaysUntilTheEndOfMonth()
	{
		return DaysUntilTheEndOfMonth(*this);
	}

	static short DaysUntilTheEndOfYear(clsDate Date, bool WithEndDay = true)
	{
		clsDate EndOfYearDate;
		EndOfYearDate._Day = 31;
		EndOfYearDate._Month = 12;
		EndOfYearDate._Year = Date._Year;

		return GetDifferenceInDays(Date, EndOfYearDate, true);
	}

	short DaysUntilTheEndOfYear(bool WithEndDay = true)
	{
		return DaysUntilTheEndOfYear(*this);
	}

	static short CalculateVacationDays(clsDate DateFrom, clsDate DateTo)
	{
		short DaysCount = 0;

		while (IsDate1BeforeDate2(DateFrom, DateTo))
		{
			DateFrom = AddOneDay(DateFrom);

			if (IsBusinessDay(DateFrom))
				DaysCount++;
		}

		return DaysCount;
	}

	short CalculateVacationDays(clsDate DateTo)
	{
		return CalculateVacationDays(*this, DateTo);
	}

	static clsDate CalculateVacationReturnDate(clsDate DateFrom, short VacationDays)
	{

		short WeekendDays = 0;
		while (IsWeekend(DateFrom))
		{
			DateFrom = AddOneDay(DateFrom);
		}

		for (short i = 0; i < VacationDays + WeekendDays; i++)
		{
			if (IsWeekend(DateFrom))
				WeekendDays++;

			DateFrom = AddOneDay(DateFrom);
		}

		while (IsWeekend(DateFrom))
		{
			DateFrom = AddOneDay(DateFrom);
		}

		return DateFrom;
	}

	clsDate CalculateVacationReturnDate(short VacationDays)
	{
		return CalculateVacationReturnDate(*this, VacationDays);
	}

	static bool IsDate1AfterDate2(clsDate Date1, clsDate Date2)
	{
		return (!IsDate1BeforeDate2(Date1, Date2) && !IsDate1EqualDate2(Date1, Date2));
	}

	bool IsDate1AfterDate2(clsDate Date2)
	{
		return IsDate1AfterDate2(*this, Date2);
	}

	static enDateCompare CompareDates(clsDate Date1, clsDate Date2)
	{
		if (IsDate1BeforeDate2(Date1, Date2))
			return enDateCompare::Before;
		if (IsDate1EqualDate2(Date1, Date2))
			return enDateCompare::Equal;

		return enDateCompare::After;
	}

	enDateCompare CompareDates( clsDate Date2)
	{
		return CompareDates( *this,Date2);
	}

	static string GetFullSystemDate()
	{
		time_t t = time(0);   // get time now

		tm* tDateNow = localtime(&t);
		short Year, Month, Day , Hour ,Minute, Second;

		Year = tDateNow->tm_year + 1900;
		Month = tDateNow->tm_mon + 1;
		Day = tDateNow->tm_mday;
		Hour = tDateNow->tm_hour;
		Minute = tDateNow->tm_min;
		Second = tDateNow->tm_sec;
		return to_string(Year) + "/" + to_string(Month) + "/" + to_string(Day) + " - " + to_string(Hour) + ":" + to_string(Minute) + ":" + to_string(Second);
	}

};

