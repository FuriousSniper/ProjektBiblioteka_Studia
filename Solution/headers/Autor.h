#ifndef AUTOR_H
#define AUTOR_H

class Autor : public Osoba {


public:
	int dodajKsiazke(Ksiazka* ksiazka);

	int dodajKsiazki(Ksiazka** ksiazki);

	Autor(string imie, string nazwisko, data dataUrodzenia);

	Autor(string imie, string nazwisko, data dataUrodzenia, Ksiazka* ksiazka);

	Autor(string imie, string nazwisko, data dataUrodzenia, Ksiazka** ksiazki);
};

#endif
