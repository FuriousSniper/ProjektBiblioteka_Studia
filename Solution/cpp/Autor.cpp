#include "..\headers\Autor.h"

int Autor::dodajKsiazke(Ksiazka* ksiazka) {
	// TODO - implement Autor::dodajKsiazke
	throw "Not yet implemented";
}

int Autor::dodajKsiazki(Ksiazka** ksiazki) {
	// TODO - implement Autor::dodajKsiazki
	throw "Not yet implemented";
}

Autor::Autor(string imie, string nazwisko, int d, int m, int r):Osoba(imie,nazwisko,d,m,r){
}

Autor::Autor(string imie, string nazwisko, int d, int m, int r, Ksiazka* ksiazka): Osoba(imie, nazwisko, d, m, r){
	dodajKsiazke(ksiazka);
}

Autor::Autor(string imie, string nazwisko, int d, int m, int r, Ksiazka** ksiazki) : Osoba(imie, nazwisko, d, m, r),dziela(ksiazki) {
	// TODO - implement Autor::Autor
	throw "Not yet implemented";
}
