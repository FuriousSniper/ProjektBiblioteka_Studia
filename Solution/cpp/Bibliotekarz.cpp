#include "..\headers\Bibliotekarz.h"
#include "..\headers\Osoba.h"
#include <string>
#include <iostream>
using namespace std;

void Bibliotekarz::zmienHaslo(string haslo) {
	// TODO - implement Bibliotekarz::zmienHaslo
	throw "Not yet implemented";
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

Bibliotekarz::Bibliotekarz(int id, string haslo) : ID(id), haslo(haslo), Osoba() {}

Bibliotekarz::Bibliotekarz(int id, string haslo,string imie, string nazwisko) : Osoba(imie, nazwisko), ID(id), haslo(haslo) {}

void Bibliotekarz::getBiblioteka() {
	// TODO - implement Bibliotekarz::getBiblioteka
	throw "Not yet implemented";
}
