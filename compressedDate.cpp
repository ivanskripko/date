#include "compressedDate.h"
#include <iostream>
#include <iomanip>
#include <ctime>
using namespace std;

Date::Date()
{
	setDay(1);
	setMonth(Date::JAN);
	setYear(1970);
}

Date::Date(int d, Date::Month m, int y)
{
	setDay(d);
	setMonth(m);
	setYear(y);
}

void Date::setDay(int newDay) 
{
	datec_t mask = ~dayMask;
	cDate &= mask;
	cDate |= newDay;	
}

void Date::setMonth(Date::Month newMonth) 
{			
	datec_t mask = (~(monthMask << monthShift));
	cDate &= mask;
	cDate |= (newMonth << monthShift);
}

void Date::setYear(int newYear) 
{		
	datec_t mask = datec_t((~(yearMask << yearShift)));	
	cDate &= mask;
	cDate |= (newYear << yearShift);	
}

int Date::getYear() const
{
	return (cDate >> yearShift) & yearMask;
}

int Date::getMonth() const
{
	return (cDate >> monthShift) & monthMask;
}

int Date::getDay() const
{
	return cDate & dayMask;
}

bool Date::isLeapYear() const
{
	int year = getYear();
	if (year % 4 == 0 &&
		(year % 100 != 0 || year % 400 == 0) )
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
	return cDate < date2.cDate;
}

bool Date::operator >  (const Date& date2) const
{
	return  cDate > date2.cDate;
}

bool Date::operator == (const Date& date2) const
{
	return cDate == date2.cDate;
}

bool Date::operator != (const Date& date2) const
{	
	return cDate != date2.cDate;
}

Date& Date::operator ++ ()
{
	if (isLeapYear() && getMonth() == FEB && getDay() == 28) {
		++cDate;	
	} else if (isTheEndOfYear()) { 
		setDay(1);
		setMonth(JAN);
		setYear(getYear() + 1);		
	} else if (isTheEndOfMonth()) {
		setDay(1);
		int m = getMonth();
		++m;
		setMonth((Month)m);
	} else {
		++cDate;
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
	if (isLeapYear() && getMonth() == MAR && getDay() == 1) {
		setDay(29);
		setMonth(FEB);		
	} else if (isTheBeginningOfYear()) {
		setDay(31);
		setMonth(DEC);
		setYear(getYear() - 1);		
	} else if (isTheBeginningOfMonth()) {
		setDay(DaysAtMonth[getMonth() - 2]);
		int m = getMonth();
		--m;		
		setMonth((Month)m);
	} else {
		--cDate;
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

int Date::totalDaysFromDate	() const
{
	int dd = getDay();
	int mm = getMonth();
	int yyyy = getYear();

	int totalDays = 0;
	totalDays += (yyyy - YEAR_TO_COUNT_DAYS) * DAYS_A_YEAR;	
	--yyyy; 
	while (yyyy > YEAR_TO_COUNT_DAYS) {
		if (yyyy % 4 == 0 && (yyyy % 100 != 0 || yyyy % 400 == 0)) {
			++totalDays;
		}
		--yyyy;
	}

	int i = 1;
	while (mm - i >= 0) {
		totalDays += DaysAtMonth[mm - i]; 
		++i;
	}

	if (mm > FEB && isLeapYear()) {
		++totalDays;	
	}

	totalDays += dd;

	return totalDays;
}

bool Date::isTheEndOfMonth() const
{
	if ((isLeapYear() && getMonth() == FEB && getDay() == 29) || (getDay() == DaysAtMonth[getMonth() - 1])) {
		return true;
	}		
	return false;
}

bool Date::isTheBeginningOfMonth()  const
{
	return getDay() == 1;
}

bool Date::isTheEndOfYear() const
{
	return getMonth() == DEC && getDay() == 31;
}

bool Date::isTheBeginningOfYear() const
{
	return getMonth() == JAN && getDay() == 1;
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