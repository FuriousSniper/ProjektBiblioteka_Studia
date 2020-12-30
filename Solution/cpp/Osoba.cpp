#include "..\headers\Osoba.h"
#include <iostream>
#include <ctime>

string Osoba::getNazwisko() {
	return this->nazwisko;
}

string Osoba::getImie() {
	return this->imie;
}

int Osoba::getWiek() {
	return this->wiek;
}

Data Osoba::getDataUrodzenia() {
	return this->dataUrodzenia;
}

int Osoba::setWiek(int age) {
	this->wiek = age;
	return this->wiek;
}

void Osoba::printOsoba() {
	
	//TODO: uwzglêdnienie drukowania wieku (na razie ze wzglêdu na brak inicjalizacji pola tego nie robi).

	cout << this->imie << " " << this->nazwisko << ", data urodzenia: ";
	dataUrodzenia.printData();
}

Osoba::Osoba(string imie, string nazwisko, int d, int m, int r):imie(imie),nazwisko(nazwisko), dataUrodzenia(Data(d,m,r)){
	time_t t = time(NULL);
	tm* buf = new tm;
	localtime_s(buf,&t);
	this->wiek = buf->tm_year + 1900 - r;
}

Osoba::Osoba(string imie, string nazwisko) : imie(imie), nazwisko(nazwisko),dataUrodzenia(Data()), wiek(0) {
}


