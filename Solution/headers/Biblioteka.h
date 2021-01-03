#ifndef BIBLIOTEKA_H
#define BIBLIOTEKA_H

#include <iostream>
#include "Adres.h"
#include <map>
#include "..\ProjektBiblioteka\Libraries\sqlite3\sqlite3.h"

using namespace std;

class Biblioteka{

	//Obiekt tej klasy przechowuje informacje nt. biblioteki. Z zalozenia jest on tworzony zawsze
	//przy uruchomieniu programu. Dane pobierane sa z bazy danych.

	string emailKontaktowy;
	string telefonKontaktowy;
	Adres adres;
	map<string, string> godzinyOtwarcia;  //Tablica CzasPracy, 7 elementowa, kazdy element odpowiada danemu dniu tygodnia.
	int iloscEgzemplarzy;

public:

	Biblioteka(string emailKontaktowy, string telefonKontaktowy, Adres adres, map<string, string> godzinyOtwarcia, int iloscEgzemplarzy);
	void printInfo();

	//Metody wykorzystywane przy wyczywaniu danych biblioteki do pamieci.

	static map<string, string> wczytywanieGodzin(sqlite3* bazaDanych);

private:

	//Metody wykorzystywane tylko i wylacznie w innych metodach tej klasy.

	void printGodzinyOtwarcia();
	static map<string, string> wczytywanieGodzinBlad();

};

#endif

