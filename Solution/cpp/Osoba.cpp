#include "..\headers\Osoba.h"

string Osoba::getNazwisko() {
	return this->nazwisko;
}

int Osoba::setImie(string imie) {
	// TODO - implement Osoba::setImie
	throw "Not yet implemented";
}

string Osoba::getImie() {
	return this->imie;
}

int Osoba::setNazwisko(string nazwisko) {
	// TODO - implement Osoba::setNazwisko
	throw "Not yet implemented";
}

int Osoba::getWiek() {
	return this->wiek;
}

int Osoba::setWiek(int wiek) {
	// TODO - implement Osoba::setWiek
	throw "Not yet implemented";
}

Osoba::Osoba(string imie, string nazwisko, Data dataUrodzenia):imie(imie),nazwisko(nazwisko),dataUrodzenia(dataUrodzenia){
}

Osoba::Osoba(string imie, string nazwisko) : imie(imie), nazwisko(nazwisko) {
}

Data Osoba::getDataUrodzenia() {
	return this->dataUrodzenia;
}
