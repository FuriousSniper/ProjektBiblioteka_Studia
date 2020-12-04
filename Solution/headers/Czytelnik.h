#ifndef CZYTELNIK
#define CZYTELNIK
using namespace std;
#include <string.h>
#include "..\headers\Data.h"
#include "..\headers\DaneKontaktowe.h"
#include "..\headers\AdresZamieszkania.h"
class Czytelnik {

private:
	string id;
	Egzemplarz** listaZaleglosci;
	Data dataPierwszegoWypozyczenia;
	int iloscWypozyczonychObecnie;
	int iloscWypozyczonychOdDolaczenia;
	string* preferowaneTematy;
	Data dataDolaczenia;
	DaneKontaktowe kontakt;
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
	Egzemplarz* wypozyczKsiazke(Egzemplarz* ksiazka);
	int oddajKsiazke(Egzemplarz* ksiazka);
	bool sprawdzDostepnoscKsiazki(Egzemplarz* ksiazka);
	Egzemplarz** getWypozyczoneObecnie();
	Data sprawdzTerminOddania(Egzemplarz* ksiazka);
	int zmienTerminOddania(Data termin);
	int zarezerwujKsiazke(Egzemplarz* ksiazka);
	Data getDataDolaczenia();
	int setDaneKontaktowe(DaneKontaktowe dane);
	int getDaneKontaktowe();
	Czytelnik(string imie, string nazwisko, Data dataUrodzenia, string* preferowaneTematy);
	Czytelnik(string imie, string nazwisko, Data dataUrodzenia);
};

#endif
