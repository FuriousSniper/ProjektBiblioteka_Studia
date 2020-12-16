#include "..\headers\Data.h"
#include <iostream>

void Data::printData() const {
	cout << this->godzina << ":";

	if (minuta < 10) {
		cout << "0";
	}

	cout << this->minuta << " " << this->dzien << "." << this->miesiac << "." << this->rok <<"r."<< endl;
}
int Data::setDzien(int dzien) {
	this->dzien = dzien;
	return this->dzien;
}
int Data::getDzien() {
	return this->dzien;
}
int Data::setMiesiac(int m) {
	this->miesiac = m;
	return this->miesiac;
}
int Data::getMiesiac() {
	return this->miesiac;
}
int Data::setRok(int r) {
	this->rok = r;
	return this->rok;
}
int Data::getRok() {
	return this->rok;
}
Data::Data():dzien(0),miesiac(NULL),rok(NULL),godzina(0),minuta(0) {}
Data::Data(int dzien, int miesiac, int rok) : dzien(dzien), miesiac(miesiac), rok(rok), godzina(0), minuta(0) {}
Data::Data(int dzien, int miesiac, int rok, int godzina, int minuta) : dzien(dzien), miesiac(miesiac), rok(rok), godzina(godzina), minuta(minuta) {}
