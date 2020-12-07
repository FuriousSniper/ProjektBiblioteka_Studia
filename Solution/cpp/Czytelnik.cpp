#include "..\headers\Czytelnik.h"
#include <string>
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
Czytelnik::Czytelnik(string imie, string nazwisko, Data dataUrodzenia, string* preferowaneTematy):Osoba(imie,nazwisko,dataUrodzenia),preferowaneTematy(preferowaneTematy),adres("","","") {
}
//  ,kontakt("", "")
Czytelnik::Czytelnik(string imie, string nazwisko, Data dataUrodzenia):Osoba(imie,nazwisko, dataUrodzenia), adres("", "", "") {

}
