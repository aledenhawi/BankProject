#pragma once

#include<iostream>
#include<string>
#include"clsDate.h"

using namespace std;

class clsPeriod
{
	clsDate _StartDate;
	clsDate _EndDate;

public:

	clsPeriod(clsDate StartDate, clsDate EndDate)
	{
		_StartDate = StartDate;
		_EndDate = EndDate;
	}

	clsDate GetStartDate()
	{
		return _StartDate;
	}

	void SetStartDate(clsDate StartDate)
	{
		_StartDate = StartDate;
	}

	__declspec(property(get = GetStartDate, put = SetStartDate)) clsDate StartDate;

	void SetEndDate(clsDate EndDate)
	{
		_EndDate = EndDate;
	}

	clsDate GetEndDate()
	{
		return _EndDate;
	}

	__declspec(property(get = GetEndDate, put = SetEndDate)) clsDate EndDate;

	static bool IsPeriodsOverlap(clsPeriod Period1, clsPeriod Period2)
	{
		return !(clsDate::IsDate1BeforeDate2(Period2.EndDate, Period1.StartDate) || clsDate::IsDate1BeforeDate2(Period1.EndDate, Period2.StartDate));
	}

	static short PeriodLengthInDays(clsPeriod Period, bool IncludeEndDay = false)
	{
		return clsDate::GetDifferenceInDays(Period.StartDate, Period.EndDate, IncludeEndDay);
	}

	static bool IsDateWithinPeriod(clsPeriod Period, clsDate Date)
	{
		return !(clsDate::CompareDates(Date, Period.StartDate) == clsDate::enDateCompare::Before || clsDate::CompareDates(Date, Period.EndDate) == clsDate::enDateCompare::After);
	}

	static int CountOverlapDays(clsPeriod Period1, clsPeriod Period2)
	{
		int OverLapDays = 0;
		int Period1Length = PeriodLengthInDays(Period1);
		int Period2Length = PeriodLengthInDays(Period2);

		if (!IsPeriodsOverlap(Period1, Period2))
			return 0;

		if (Period1Length < Period2Length)
		{
			while (clsDate::IsDate1BeforeDate2(Period1.StartDate, Period1.EndDate))
			{
				if (IsDateWithinPeriod(Period2, Period1.StartDate))
					OverLapDays++;

				if (clsDate::IsDate1EqualDate2(Period1.StartDate, Period1.EndDate))
					break;

				Period1.StartDate = clsDate::AddOneDay(Period1.StartDate);
			}
		}
		else
		{
			while (clsDate::IsDate1BeforeDate2(Period2.StartDate, Period2.EndDate))
			{
				if (IsDateWithinPeriod(Period1, Period2.StartDate))
					OverLapDays++;

				if (clsDate::IsDate1EqualDate2(Period2.StartDate, Period2.EndDate))
					break;

				Period2.StartDate = clsDate::AddOneDay(Period2.StartDate);
			}
		}
		return OverLapDays;
	}

};

