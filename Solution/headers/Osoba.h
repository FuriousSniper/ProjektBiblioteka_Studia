#ifndef OSOBA_H
#define OSOBA_H
#include <string>
#include "Data.h"
using namespace std;
class Osoba {

private:
	string imie;
	string nazwisko;
	int wiek;
	Data dataUrodzenia;

public:
	string getNazwisko();

	int setImie(string imie);

	string getImie();

	int setNazwisko(string nazwisko);

	int getWiek();

	int setWiek(int wiek);

	Osoba(string imie, string nazwisko, Data dataUrodzenia);

	Osoba(string imie, string nazwisko);

	Data getDataUrodzenia();
};

#endif
