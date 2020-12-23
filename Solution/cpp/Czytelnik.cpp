#include "..\headers\Czytelnik.h"
#include <string>
#include <iostream>
#include "..\headers\Data.h"
#include "..\headers\DaneKontaktowe.h"
#include "..\headers\AdresZamieszkania.h"
using namespace std;
string Czytelnik::getId() {
	return id;
}
Egzemplarz** Czytelnik::getZaleglosci(){
	return listaZaleglosci;
}
int Czytelnik::setZaleglosci(Egzemplarz** egzemplarze) {
	return 1;
}
Data Czytelnik::getDataPierwszegoWypozyczenia() {
	return dataPierwszegoWypozyczenia;
}
string Czytelnik::getOfertySpecjalne() {
	//TODO
	throw "not implemented";
}
int Czytelnik::getIloscWypozyczonychOdDolaczenia() {
	return iloscWypozyczonychOdDolaczenia;
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
Data Czytelnik::getDataDolaczenia() {
	return dataDolaczenia;
}
int Czytelnik::setAdresZamieszkania(AdresZamieszkania newAdress) {
	this->adres.miasto = newAdress.miasto;
	this->adres.kodPocztowy = newAdress.kodPocztowy;
	this->adres.ulica = newAdress.ulica;
	this->adres.numerMieszkania = newAdress.numerMieszkania;
	return 0;
}
void Czytelnik::printInfo() {
	cout << "\nWyswietlanie informacji o uzytkowniku z ID: " << this->getId() << endl;
	cout << this->getImie() << " " << this->getNazwisko() << ", wiek: " << this->getWiek()<<" lat" << endl;
	cout << this->adres.ulica << "/" << this->adres.numerMieszkania << endl;
	cout << this->adres.kodPocztowy << " " << this->adres.miasto << endl;
}
void Czytelnik::setHaslo(string newHaslo) {
	this->haslo = newHaslo;
}

AdresZamieszkania Czytelnik::getAdres() {
	return this->adres;
}
string Czytelnik::getHaslo() {
	return this->haslo;
}
/*
int Czytelnik::setDaneKontaktowe(DaneKontaktowe dane) {
	if (dane.email != "")
		kontakt.email = dane.email;
	if (dane.telefon != "")
		kontakt.telefon = dane.telefon;

	return 1;
}

DaneKontaktowe Czytelnik::getKontakt() {
	return kontakt;
}
*/
//  ,kontakt("", "")
Czytelnik::Czytelnik(string imie, string nazwisko, int d, int m, int r, string* preferowaneTematy):Osoba(imie,nazwisko, d, m,r),preferowaneTematy(preferowaneTematy),adres("","","",0) {
}
//  ,kontakt("", "")
Czytelnik::Czytelnik(string imie, string nazwisko, int d, int m, int r):Osoba(imie,nazwisko, d,m,r), adres("", "", "",0) {

}
