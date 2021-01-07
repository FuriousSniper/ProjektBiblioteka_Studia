#include "..\headers\Data.h"
#include <iostream>

void Date::printData() const {
	cout << this->day << "." << this->month << "." << this->year <<"r."<< endl;
}
int Date::setDay(int dzien) {
	this->day = dzien;
	return this->day;
}
int Date::getDay() {
	return this->day;
}
int Date::setMonth(int m) {
	this->month = m;
	return this->month;
}
int Date::getMonth() {
	return this->month;
}
int Date::setYear(int r) {
	this->year = r;
	return this->year;
}
int Date::getYear() {
	return this->year;
}
Date::Date():day(0),month(0),year(0){}
Date::Date(int dzien, int miesiac, int rok) : day(dzien), month(miesiac), year(rok){}


