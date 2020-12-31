#ifndef BIBLIOTEKARZ_H
#define BIBLIOTEKARZ_H
#include "Osoba.h"
#include <string>
#include "AdresZamieszkania.h"

using namespace std;
class Bibliotekarz : public Osoba {

private:

	const int ID;
	string haslo;

public:

	void setHaslo(string haslo);
	string getHaslo();
	int getID();

	void printInfOBibliotekarzu();
	void getBiblioteka();
	Bibliotekarz(string imie, string nazwisko, int ID);
	Bibliotekarz(string imie, string nazwisko, string email, string telefon, int d, int m, int r, AdresZamieszkania adres, int ID);

};

#endif
