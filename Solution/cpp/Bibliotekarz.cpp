#include "..\headers\Bibliotekarz.h"
#include "..\headers\Osoba.h"
#include <string>
#include <iostream>
using namespace std;

void Bibliotekarz :: setHaslo(string haslo) {
	this->haslo = haslo;
}
string Bibliotekarz::getHaslo() {
	return this->haslo;
}

int Bibliotekarz::getID() {
	return this->ID;
}

void Bibliotekarz::printInfOBibliotekarzu() {
	printOsoba();
	cout << "\nDane charakterystyczne dla bibliotekarza: " << endl;
	cout << "\tID: " << this->ID << endl;
}

Bibliotekarz::Bibliotekarz(string imie, string nazwisko, int ID) : Osoba(imie, nazwisko), ID(ID) {}

Bibliotekarz::Bibliotekarz(string imie, string nazwisko, string email, string telefon, int d, int m, int r, Adres adres, int ID) : Osoba(imie, nazwisko, email, telefon, d,m,r,adres), ID(ID) {}

void Bibliotekarz::getBiblioteka() {
	// TODO - implement Bibliotekarz::getBiblioteka
	throw "Not yet implemented";
}
