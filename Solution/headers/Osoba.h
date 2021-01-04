#ifndef OSOBA_H
#define OSOBA_H
#include <string>
#include "Data.h"
#include "Adres.h"

using namespace std;

class Osoba {

private:

	const string imie;
	const string nazwisko;
	int wiek;
	const Data dataUrodzenia;
	string email;
	string telefon;
	Adres adres;

public:

	string getNazwisko();
	string getImie();
	string getEmail();
	string getTelefon();
	Adres getAdresZamieszkania();
	void setAdresZamieszkania(Adres adres);
	Data getDataUrodzenia();
	int getWiek();

	void setDaneKontaktowe(string email, string telefon);
	int setWiek(int wiek);
	void setTelefon(string telefon);
	void setEmail(string email);

	Osoba(string imie, string nazwisko, int d, int m, int r);
	Osoba(string imie, string nazwisko, string email, string telefon, int d, int m, int r, Adres adres);
	Osoba(string imie, string nazwisko);
	Osoba();

	void printOsoba();
};

#endif
