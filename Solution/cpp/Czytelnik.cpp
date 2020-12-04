#include "..\headers\Czytelnik.h"
#include <string>
#include "..\headers\Data.h"
#include "..\headers\DaneKontaktowe.h"
#include "..\headers\AdresZamieszkania.h"
using namespace std;
string Czytelnik::getId() {
	//TODO
}
Egzemplarz** Czytelnik::getZaleglosci(){
	//TODO
}
int Czytelnik::setZaleglosci(Egzemplarz** egzemplarze) {
	//TODO
}
Data Czytelnik::getDataPierwszegoWypozyczenia() {
	//TODO
}
string Czytelnik::getOfertySpecjalne() {
	//TODO
}
int Czytelnik::getIloscWypozyczonychOdDolaczenia() {
	//TODO
}
string* Czytelnik::getPreferowaneTematy() {
	//TODO
}
int Czytelnik::setPreferowaneTematy(string* tematy) {
	//TODO
}
Egzemplarz* Czytelnik::wypozyczKsiazke(Egzemplarz* ksiazka) {
	//TODO
}
int Czytelnik::oddajKsiazke(Egzemplarz* ksiazka) {
	//TODO
}
bool Czytelnik::sprawdzDostepnoscKsiazki(Egzemplarz* ksiazka) {
	//TODO
}
Egzemplarz** Czytelnik::getWypozyczoneObecnie() {
	//TODO
}
Data Czytelnik::sprawdzTerminOddania(Egzemplarz* ksiazka) {
	//TODO
}
int Czytelnik::zmienTerminOddania(Data termin) {
	//TODO
}
int Czytelnik::zarezerwujKsiazke(Egzemplarz* ksiazka) {
	//TODO
}
Data Czytelnik::getDataDolaczenia() {
	//TODO
}
int Czytelnik::setDaneKontaktowe(DaneKontaktowe dane) {
	//TODO
}
int Czytelnik::getDaneKontaktowe() {
	//TODO
}
Czytelnik::Czytelnik(string imie, string nazwisko, Data dataUrodzenia, string* preferowaneTematy) {
	//TODO
}
Czytelnik::Czytelnik(string imie, string nazwisko, Data dataUrodzenia) {
	//TODO
}
