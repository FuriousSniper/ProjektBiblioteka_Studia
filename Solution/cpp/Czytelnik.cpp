#include "..\headers\Czytelnik.h"
#include <string>
#include <iostream>
#include "..\headers\Data.h"
#include "..\headers\AdresZamieszkania.h"

using namespace std;
const int Czytelnik::getID() {
	return ID;
}
string Czytelnik::getOfertySpecjalne() {
	//TODO
	throw "not implemented";
}

string* Czytelnik::getPreferowaneTematy() {
	return preferowaneTematy;
}
int Czytelnik::setPreferowaneTematy(string* tematy) {
	//TODO
	throw "not implemented";
}
int Czytelnik::wypozyczKsiazke(Egzemplarz* ksiazka) {
	//TODO
	throw "not implemented";
}
int Czytelnik::oddajKsiazke(Egzemplarz* ksiazka) {
	//TODO
	throw "not implemented";
}
bool Czytelnik::sprawdzDostepnoscKsiazki(Egzemplarz* ksiazka) {
	//TODO
	throw "not implemented";
}
Egzemplarz** Czytelnik::getWypozyczoneObecnie() {
	//TODO
	throw "not implemented";
}
Data Czytelnik::sprawdzTerminOddania(Egzemplarz* ksiazka) {
	//TODO
	throw "not implemented";
}
int Czytelnik::zmienTerminOddania(Data termin) {
	//TODO
	throw "not implemented";
}
int Czytelnik::zarezerwujKsiazke(Egzemplarz* ksiazka) {
	//TODO
	throw "not implemented";
}

void Czytelnik::printInfo() {

	//TODO: dopisaæ inne informacje (np. preferowane tematy itd..)

	printOsoba();
	cout << "Dane charakterystyczne dla czytelnika: " << endl;
	cout << "\tID: " << this->ID << endl;
}
void Czytelnik::setHaslo(string newHaslo) {
	this->haslo = newHaslo;
}

string Czytelnik::getHaslo() {
	return this->haslo;
}

Czytelnik::Czytelnik(string imie, string nazwisko, int id) : Osoba(imie, nazwisko),ID(id) {}
Czytelnik::Czytelnik(string imie, string nazwisko, int d, int m, int r, string* preferowaneTematy, int ID): Osoba(imie,nazwisko, d, m,r),
preferowaneTematy(preferowaneTematy), ID(ID) {}  

Czytelnik::Czytelnik(string imie, string nazwisko, string email, string telefon, int d, int m, int r, AdresZamieszkania adres, int ID): ID(ID), Osoba(imie,nazwisko, email, telefon, d,m,r, adres) {}

