#ifndef AUTOR_H
#define AUTOR_H
#include "..\headers\Osoba.h"
#include "..\headers\Data.h"
#include "Ksiazka.h"
#include <string>
class Ksiazka;
using namespace std;
class Autor : public Osoba {
private:
	Ksiazka** dziela;

public:
	int dodajKsiazke(Ksiazka* ksiazka);

	int dodajKsiazki(Ksiazka** ksiazki);

	Autor(string imie, string nazwisko, int d, int m, int r);

	Autor(string imie, string nazwisko, int d, int m, int r, Ksiazka* ksiazka);

	Autor(string imie, string nazwisko, int d, int m, int r, Ksiazka** ksiazki);
};

#endif

//w bazie danych AUTOR
/*
	ID INT PRIMARY        KEY      NOT NULL,"	
	imie				   TEXT				,"	//imie autora
	nazwisko			   TEXT				,"	//nazwisko autora
	dataUrodzenia		   DATE				,"	//data urodzenia autora
	ksiazki				   TEXT					//tytuly ksiazek ktore autor napisal. wpisywac z delimiterem "||"
*/