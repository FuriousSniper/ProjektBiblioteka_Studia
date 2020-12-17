#ifndef OSOBA_H
#define OSOBA_H
#include <string>
#include "Data.h"

using namespace std;

class Osoba {

private:

	const string imie;
	const string nazwisko;
	int wiek;
	const Data dataUrodzenia;

public:

	//Wywali�em settery do p�l sta�ych (wcze�niej nie by�y w og�le sta�e, a logika wskazuje, �e powinny by�)

	string getNazwisko();
	string getImie();
	int getWiek();
	int setWiek(int wiek);
	Osoba(string imie, string nazwisko, int d, int m, int r);
	Osoba(string imie, string nazwisko);
	Data getDataUrodzenia();
	void printOsoba();
};

#endif
