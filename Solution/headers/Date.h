#ifndef DATA_H
#define DATA_H
#include <string>
using namespace std;

class Date {

public:
	int year;
	int month;
	int day;

	void printDate() const;
	int setDay(int dzien);
	int getDay();
	int setMonth(int m);
	int getMonth();
	int setYear(int r);
	int getYear();
	Date();
	Date(int day, int month, int year);
};

#endif
