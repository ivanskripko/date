#include "Date.h"
#include <iostream>
#include <iomanip>
#include <ctime>
using namespace std;


bool Date::isLeapYear() const
{
	if (yyyy % 4 == 0 &&
		(yyyy % 100 != 0 || yyyy % 400 == 0) )
		return true;
	else
		return false;
}

Date Date::getCurrentDate() 
{	
	time_t timestamp;
	tm* ptm;

	time(&timestamp); 
	ptm = gmtime(&timestamp);
	
	Date currentDate(ptm->tm_mday, (Month)(ptm->tm_mon + 1), ptm->tm_year + 1900);

	return currentDate;
}

bool Date::operator < (const Date& date2) const
{	
	return (yyyy <  date2.yyyy) ||
			(yyyy == date2.yyyy && mm <  date2.mm) ||
			(yyyy == date2.yyyy && mm == date2.mm && dd < date2.dd);
}

bool Date::operator >  (const Date& date2) const
{
	return  (yyyy > date2.yyyy) ||
			(yyyy == date2.yyyy && mm > date2.mm) ||
			(yyyy == date2.yyyy && mm == date2.mm && dd > date2.dd);
}

bool Date::operator == (const Date& date2) const
{
	return (yyyy == date2.yyyy && mm == date2.mm && dd == date2.dd);
}

bool Date::operator != (const Date& date2) const
{	
	return !(*this == date2);
}

Date& Date::operator ++ ()
{
	if (isLeapYear() && mm == FEB && dd == 28) {
		++dd;	
	} else if (isTheEndOfYear()) { 
		dd = 1;
		mm = JAN;
		++yyyy;
	} else if (isTheEndOfMonth()) {
		dd = 1;
		int m = (int)mm;
		++m;
		mm = (Month)m;		
	} else {
		++dd;
	}

	return *this;
}

Date Date::operator ++ (int)
{
	Date tmp = *this;
	++(*this);
	return tmp;
}

Date& Date::operator -- () 
{	
	if (isLeapYear() && mm == MAR && dd == 1) {
		dd = 29;
		mm = FEB;
	} else if (isTheBeginningOfYear()) {
		dd = 31;
		mm = DEC;
		--yyyy;
	} else if (isTheBeginningOfMonth()) {
		dd = DaysAtMonth[mm - 2];		
		int m = (int)mm;
		--m;
		mm = (Month)m;	
	} else {
		--dd;
	}

	return *this;
}

Date  Date::operator -- (int) 
{
	Date tmp = *this;
	--(*this);
	return tmp;
}

int Date::operator - (const Date& date2) const
{
	int result = totalDaysFromDate() - date2.totalDaysFromDate();
	return (result > 0 ? result : -result);
}

int Date::totalDaysFromDate() const
{
	int totalDays = 0;
	totalDays += (yyyy - YEAR_TO_COUNT_DAYS) * DAYS_A_YEAR;	
	int tmp = yyyy - 1; 
	while (tmp > YEAR_TO_COUNT_DAYS) {
		if (tmp % 4 == 0 &&	(tmp % 100 != 0 || tmp % 400 == 0)) {
			++totalDays; // каждый високосный год прибавляем по 1 дню
		}
		--tmp;
	}

	int i = 1;
	while (mm - i >= 0) {
		totalDays += DaysAtMonth[mm - i]; // прибавляем число дней в месяцах
		++i;
	}

	if (mm > FEB && isLeapYear()) {
		++totalDays;	//прибавляем 1 день, если текущий год високосный, т.к. до этого не учитывали это
	}

	totalDays += dd; // прибавляем дни

	return totalDays;
}

bool Date::isTheEndOfMonth() const
{
	if ((isLeapYear() && mm == FEB && dd == 29) || (dd == DaysAtMonth[mm - 1])) {
		return true;
	}		
	return false;
}

bool Date::isTheBeginningOfMonth()  const
{
	return dd == 1;
}

bool Date::isTheEndOfYear() const
{
	return mm == DEC && dd == 31;
}

bool Date::isTheBeginningOfYear() const
{
	return mm == JAN && dd == 1;
}

ostream& operator << (ostream& os, const Date& date)
{
	os << setfill('0');
	os << setw(2) << date.getDay() << '.'
	   << setw(2) << date.getMonth() << '.'
	   << setw(4) << date.getYear();
	os << setfill(' ');
	return os;
}


istream& operator >> (istream& is, Date& d)
{	
	int day;
	int month;
	int year;
	char c;

	is >> day >> c
		>> month >> c
		>> year;
	
	d.setDay(day);
	d.setMonth((Date::Month)month);
	d.setYear(year);

	return is;
}

const int Date::DaysAtMonth[Date::MONTHS] = {31,28,31,30,31,30,31,31,30,31,30,31};