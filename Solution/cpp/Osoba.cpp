#include "..\headers\Osoba.h"

string Osoba::getNazwisko() {
	return this->nazwisko;
}

int Osoba::setImie(string imie) {
	this->imie = imie;
	return 1;
}

string Osoba::getImie() {
	return this->imie;
}

int Osoba::setNazwisko(string nazwisko) {
	this->nazwisko = nazwisko;
	return 1;
}

int Osoba::getWiek() {
	return this->wiek;
}

int Osoba::setWiek(int wiek) {
	this->wiek = wiek;
	return wiek;
}

Data Osoba::getDataUrodzenia() {
	return this->dataUrodzenia;
}

void Osoba::setDataUrodzenia(int d, int m, int r) {
	Data D = Data(d, m, r);
	this->dataUrodzenia =D;
}

Osoba::Osoba(string imie, string nazwisko, int d, int m, int r):imie(imie),nazwisko(nazwisko){
	setDataUrodzenia(d, m, r);
}

Osoba::Osoba(string imie, string nazwisko) : imie(imie), nazwisko(nazwisko) {
}


