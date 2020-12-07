#ifndef BIBLIOTEKARZ_H
#define BIBLIOTEKARZ_H
#include "Osoba.h"
#include <string>
#include "DaneKontaktowe.h"
using namespace std;
class Bibliotekarz : Osoba {

private:
	string id;
	string haslo;
	DaneKontaktowe kontakt;

public:
	void zmienHaslo(string haslo);

	void zmienDaneKontaktowe(DaneKontaktowe kontakt);

	void printInfOBibliotekarzu();

	void getBiblioteka();

	Bibliotekarz(string id, string haslo);

	Bibliotekarz(string id, string haslo, string imie, string nazwisko);

	
};

#endif
