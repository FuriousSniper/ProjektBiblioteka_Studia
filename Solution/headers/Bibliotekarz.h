#ifndef BIBLIOTEKARZ_H
#define BIBLIOTEKARZ_H

class Bibliotekarz : Osoba {

private:
	string identyfikator;
	string haslo;
	DaneKontaktowe kontakt;

public:
	void zmienHaslo(string haslo);

	void zmienDaneKontaktowe(DaneKontaktowe kontakt);

	void printInfOBibliotekarzu();

	Bibliotekarz(string id, string haslo);

	void getBiblioteka();
};

#endif
