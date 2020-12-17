#include "..\headers\Osoba.h"
#include <iostream>

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

int Osoba::setWiek(int wiek) {
	this->wiek = wiek;
	return this->wiek;
}

void Osoba::printOsoba() {
	
	//TODO: uwzglêdnienie drukowania wieku (na razie ze wzglêdu na brak inicjalizacji pola tego nie robi).

	cout << this->imie << " " << this->nazwisko << ", data urodzenia: ";
	dataUrodzenia.printData();
}

Osoba::Osoba(string imie, string nazwisko, int d, int m, int r):imie(imie),nazwisko(nazwisko), dataUrodzenia(Data(d,m,r)){

	//TODO: obliczanie wieku osoby na podstawie daty urodzenia.
}

Osoba::Osoba(string imie, string nazwisko) : imie(imie), nazwisko(nazwisko),dataUrodzenia(Data()), wiek(0) {
}


