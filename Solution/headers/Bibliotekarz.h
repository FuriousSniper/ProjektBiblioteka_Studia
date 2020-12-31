#ifndef BIBLIOTEKARZ_H
#define BIBLIOTEKARZ_H
#include "Osoba.h"
#include <string>
#include "AdresZamieszkania.h"

using namespace std;
class Bibliotekarz : Osoba {

private:

	const int ID;
	string haslo;

public:

	void zmienHaslo(string haslo);
	string getHaslo();
	int getID();

	void printInfOBibliotekarzu();
	void getBiblioteka();
	Bibliotekarz(int id, string haslo);
	Bibliotekarz(int id, string haslo, string imie, string nazwisko);

};

#endif
