#ifndef CZYTELNIK_H
#define CZYTELNIK_H
using namespace std;
#include "DaneKontaktowe.h"
#include <string>
#include "Data.h"

#include "AdresZamieszkania.h"
#include "Egzemplarz.h"
#include "Osoba.h"
class Egzemplarz;
class DaneKontaktowe;
class Osoba;
class Czytelnik: public Osoba {

private:
	//TUTAJ JEST BARDZO DZIWNY BLAD, NALEZY JESZCZE W DRUGIM PLIKU DOPISAC DO KONSTRUKTORA I WTEDY SIE ON POJAWIA
	//DaneKontaktowe kontakt;
	string id;
	Egzemplarz** listaZaleglosci;
	Data dataPierwszegoWypozyczenia;
	int iloscWypozyczonychObecnie;
	int iloscWypozyczonychOdDolaczenia;
	string* preferowaneTematy;
	Data dataDolaczenia;
	
	AdresZamieszkania adres;
	

public:
	string getId();
	Egzemplarz** getZaleglosci();
	int setZaleglosci(Egzemplarz** egzemplarze);
	Data getDataPierwszegoWypozyczenia();
	string getOfertySpecjalne();
	int getIloscWypozyczonychOdDolaczenia();
	string* getPreferowaneTematy();
	int setPreferowaneTematy(string* tematy);
	int wypozyczKsiazke(Egzemplarz* ksiazka);
	int oddajKsiazke(Egzemplarz* ksiazka);
	bool sprawdzDostepnoscKsiazki(Egzemplarz* ksiazka);
	Egzemplarz** getWypozyczoneObecnie();
	Data sprawdzTerminOddania(Egzemplarz* ksiazka);
	int zmienTerminOddania(Data termin);
	int zarezerwujKsiazke(Egzemplarz* ksiazka);
	Data getDataDolaczenia();
	int setDaneKontaktowe(DaneKontaktowe dane);
	DaneKontaktowe getKontakt();
	Czytelnik(string imie, string nazwisko, int d, int m, int r);
	Czytelnik(string imie, string nazwisko, int d, int m, int r, string* preferowaneTematy);
	
};

#endif
