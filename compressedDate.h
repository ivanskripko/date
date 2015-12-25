#ifndef COMPRESSEDDATE_H_
#define COMPRESSEDDATE_H_

#include <fstream>

#define DAYS_A_YEAR 365
#define YEAR_TO_COUNT_DAYS 1970

typedef unsigned int datec_t;

using namespace std;

class Date
{

public:
	enum Month {JAN = 1, FEB, MAR, APR, MAY, JUN, JUL, AUG,
			SEP, OCT, NOV, DEC, MONTHS = 12};
	
private:
	static const int monthShift = 5;
	static const int yearShift = monthShift + 4;
	static const int dayMask = 31;
	static const int monthMask = 15;
	static const int yearMask = 8388607; // остаток сохраняем под год, хотя 16383 хватило бы для YYYY

	datec_t cDate;

public:
	Date();
	Date(int d, Month m, int y);
	Date(const Date& d2)
	{
		cDate = d2.cDate;
	}
	~Date()
	{	
	}

	void setDay(int newDay);	
	void setMonth(Month newMonth);
	void setYear(int newYear);
	int getYear() const;
	int getMonth() const;
	int getDay() const;

	bool isLeapYear() const;

	bool operator <  (const Date& date2) const;
	bool operator >  (const Date& date2) const;
	bool operator == (const Date& date2) const;
	bool operator != (const Date& date2) const;

	Date& operator ++ ();
	Date  operator ++ (int);
	Date& operator -- (); 
	Date  operator -- (int);

	int operator - (const Date& date2) const;

	static Date getCurrentDate();

private: 
	static const int DaysAtMonth[MONTHS];

	bool isTheEndOfMonth() const;
	bool isTheBeginningOfMonth() const;
	bool isTheEndOfYear() const;
	bool isTheBeginningOfYear() const;	

	int totalDaysFromDate() const;
};

ostream& operator << (ostream& os, const Date& date);

istream& operator >> (istream& is, Date& d);

#endif