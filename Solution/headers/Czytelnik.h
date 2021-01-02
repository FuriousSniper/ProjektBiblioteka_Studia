#ifndef CZYTELNIK_H
#define CZYTELNIK_H
using namespace std;

#include <string>
#include "Data.h"
#include "AdresZamieszkania.h"
#include "Egzemplarz.h"
#include "Osoba.h"
#include "Statystyki.h"

class Egzemplarz;
class Osoba;

class Czytelnik: public Osoba {

private:

	//TUTAJ JEST BARDZO DZIWNY BLAD, NALEZY JESZCZE W DRUGIM PLIKU DOPISAC DO KONSTRUKTORA I WTEDY SIE ON POJAWIA
	//DaneKontaktowe kontakt;

	//Kazdy Czytelnik, ktory zalega z oddanie posiada swoje ID w rejestrze spoznien. Jezeli nie zalega to jest
	//to ustawione na -1.

	int idRejestrSpoznien;
	const int ID;
	string* preferowaneTematy;
	string haslo;
	Statystyki statystyki;

public:

	const int getID();
	string getOfertySpecjalne();
	string* getPreferowaneTematy();
	int setPreferowaneTematy(string* tematy);
	int wypozyczKsiazke(Egzemplarz* ksiazka);
	int oddajKsiazke(Egzemplarz* ksiazka);
	bool sprawdzDostepnoscKsiazki(Egzemplarz* ksiazka);
	Egzemplarz** getWypozyczoneObecnie();
	Data sprawdzTerminOddania(Egzemplarz* ksiazka);
	int zmienTerminOddania(Data termin);
	int zarezerwujKsiazke(Egzemplarz* ksiazka);
	Czytelnik(string imie, string nazwisko, int id);
	Czytelnik(string imie, string nazwisko, string email, string telefon, int d, int m, int r, AdresZamieszkania, int ID);
	Czytelnik(string imie, string nazwisko, int d, int m, int r, string* preferowaneTematy, int ID);
	void printInfo();
	void setHaslo(string newHaslo);
	string getHaslo();

};

#endif

//w bazie danych CZYTELNIK
/*
	"ID INT PRIMARY        KEY      ,"
	"listaZaleglosci       TEXT     ,"
	"dataPierwszegoWypozyczenia     DATE     ,"
	"iloscWypozyczonychOdDolaczenia  INT             ,"
	"preferowaneTematy     TEXT             ,"
	"dataDolaczenia        DATE             ,"
	"miasto				   TEXT             ,"
	"kodPocztowy           TEXT             ,"
	"ulica                 TEXT             ,"
	"imie                  TEXT             ,"
	"nazwisko              TEXT             ,"
	"wiek                  TEXT             ,"
	"dataUrodzenia         DATE             ,"
	"haslo				   TEXT				,"
	"numerMieszkania       TEXT             
	"ksiazka1			   TEXT				,"
	"ksiazka2			   TEXT				,"
	"ksiazka3			   TEXT				,"
	);";
*/
