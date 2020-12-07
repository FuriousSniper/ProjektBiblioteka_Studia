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

	Autor(string imie, string nazwisko, Data dataUrodzenia);

	Autor(string imie, string nazwisko, Data dataUrodzenia, Ksiazka* ksiazka);

	Autor(string imie, string nazwisko, Data dataUrodzenia, Ksiazka** ksiazki);
};

#endif
