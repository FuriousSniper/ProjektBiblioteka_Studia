#include "..\headers\Autor.h"

int Autor::dodajKsiazke(Ksiazka* ksiazka) {
	// TODO - implement Autor::dodajKsiazke
	throw "Not yet implemented";
}

int Autor::dodajKsiazki(Ksiazka** ksiazki) {
	// TODO - implement Autor::dodajKsiazki
	throw "Not yet implemented";
}

Autor::Autor(string imie, string nazwisko, Data dataUrodzenia):Osoba(imie,nazwisko,dataUrodzenia){
	// TODO - implement Autor::Autor
	throw "Not yet implemented";
}

Autor::Autor(string imie, string nazwisko, Data dataUrodzenia, Ksiazka* ksiazka): Osoba(imie, nazwisko, dataUrodzenia){
	dodajKsiazke(ksiazka);
}

Autor::Autor(string imie, string nazwisko, Data dataUrodzenia, Ksiazka** ksiazki) : Osoba(imie, nazwisko, dataUrodzenia),dziela(ksiazki) {
	// TODO - implement Autor::Autor
	throw "Not yet implemented";
}
