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

Osoba::Osoba(string imie, string nazwisko, Data dataUrodzenia):imie(imie),nazwisko(nazwisko),dataUrodzenia(dataUrodzenia){
}

Osoba::Osoba(string imie, string nazwisko) : imie(imie), nazwisko(nazwisko) {
}


