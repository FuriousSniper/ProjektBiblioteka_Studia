#ifndef BIBLIOTEKARZ_H
#define BIBLIOTEKARZ_H
#include "Osoba.h"
#include <string>
using namespace std;
class Bibliotekarz : Osoba {

private:
	string id;
	string haslo;

public:
	void zmienHaslo(string haslo);


	void printInfOBibliotekarzu();

	void getBiblioteka();

	Bibliotekarz(string id, string haslo);

	Bibliotekarz(string id, string haslo, string imie, string nazwisko);
	
};

#endif
