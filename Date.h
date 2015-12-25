#ifndef DATE_H_
#define DATE_H_

#include <fstream>

#define DAYS_A_YEAR 365
#define YEAR_TO_COUNT_DAYS 1970

using namespace std;

class Date
{

public:
	enum Month {JAN = 1, FEB, MAR, APR, MAY, JUN, JUL, AUG,
			SEP, OCT, NOV, DEC, MONTHS = 12};
	
private:
	int dd;
	Month mm;
	int yyyy;

public:

	Date() : dd(1), mm(Date::JAN), yyyy(1970)
	{
	}

	Date(int d, Month m, int y) : dd(d), mm(m), yyyy(y)
	{
	}

	Date(const Date& d2)
	{
		dd = d2.dd;
		mm = d2.mm;
		yyyy = d2.yyyy;
	}

	~Date()
	{	
	}

	int getYear() const
	{
		return yyyy;
	}

	void setYear(int year)
	{
		yyyy = year;
	}

	int getMonth() const
	{
		return mm;
	}

	void setMonth(Month month)
	{
		mm = month;
	}

	int getDay() const
	{
		return dd;
	}

	void setDay(int day)
	{
		dd = day;
	}

	// функция для определения, является ли год даты високосным
	bool isLeapYear() const;

	// операция сравнения дат
	bool operator <  (const Date& date2) const;
	bool operator >  (const Date& date2) const;
	bool operator == (const Date& date2) const;
	bool operator != (const Date& date2) const;

	// операции инкремента и декремента. Увеличивает и уменьшают дату на один день
	Date& operator ++ ();
	Date  operator ++ (int);
	Date& operator -- (); 
	Date  operator -- (int);

	// разница в днях между датами
	int operator - (const Date& date2) const;

	// функция возвращает текущую дату
	static Date getCurrentDate();

private: 
	// количество дней в месяце. Скрыт, т.к. для внутреннего использования, менять нельзя
	static const int DaysAtMonth[MONTHS];

	// для внутреннего использования
	bool isTheEndOfMonth() const;
	bool isTheBeginningOfMonth() const;
	bool isTheEndOfYear() const;
	bool isTheBeginningOfYear() const;	

	// считает количество дней прошедших с даты (напр. от Рождества)
	int totalDaysFromDate() const;
};

// операция вывода даты в поток, в принципе, можно сделать friend
ostream& operator << (ostream& os, const Date& date);

// Операция ввода даты из потока в формате dd.mm.yyyy, в принципе, можно сделать friend
istream& operator >> (istream& is, Date& d);

#endif