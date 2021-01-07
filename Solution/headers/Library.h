#ifndef BIBLIOTEKA_H
#define BIBLIOTEKA_H
#include <iostream>
#include "Adress.h"
#include <map>
#include "..\ProjektBiblioteka\Libraries\sqlite3\sqlite3.h"

using namespace std;

class Library{

	//Obiekt tej klasy przechowuje informacje nt. biblioteki. Z zalozenia jest on tworzony zawsze
	//przy uruchomieniu programu. Dane pobierane sa z bazy danych.

	string contactEmailAdress;
	string contactPhoneNumber;
	Adress adress;
	map<string, string> openingHours;  //Tablica CzasPracy, 7 elementowa, kazdy element odpowiada danemu dniu tygodnia.
	int numberOfCopies;

public:

	Library(string contactEmailAdress, string contactPhoneNumber, Adress adress, map<string, string> openingHours, int numberOfCopies);
	void printLibraryInfo();
	static map<string, string> loadOpeningHours(sqlite3* dataBase);

private:

	void printOpeningHours();
	static map<string, string> loadOpeningHoursError();
};

#endif

