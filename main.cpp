#include <iostream>
#include "compressedDate.h"

using namespace std;

int main()
{
	
	Date d1(29, Date::FEB, 2016);
	Date copyDate;
	Date d2 = copyDate;

	cout << "First date (d1): " << d1 << "; Second date (d2): " << d2 << endl;
	cout << "++++d1: " << ++++d1 << endl;
	cout << "----d2: " << ----d2 << endl;


	cout << "d1++: " << d1++ << endl;
	cout << "d2--: " << d2-- << endl;

	cout << "First date (d1): " << d1 << "; Second date (d2): " << d2 << endl;

	cout << "Please input two dates (with dd.mm.yyyy format) to compare and to count days between them: " << endl;
	cin >> d1 >> d2;

	if (d1 != d2) {
		cout << "Dates are different! " << endl;
		if (d1 > d2) { 
			cout << "Date1 is bigger! " << endl;
		} else if (d1 < d2) { 
			cout << "Date2 is bigger! " << endl;
		}
	} else {
		cout << "Dates are equal! " << endl;
	}

	cout << "Its " << d1-d2 << " days between dates! " << endl;

	return 0;
}

