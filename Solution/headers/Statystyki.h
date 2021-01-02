#ifndef STATYSTYKI_H
#define STATYSTYKI_H

#include "..\headers\Data.h"


class Statystyki {

	//Statystyki odnosnie konta czytelnika.

	Data dataPierszegoWypozyczenia;
	int iloscWypozyczonychOdDolaczenia;
	string* preferowaneTematy;
	Data dataDolaczenia;

public:

	Statystyki(Data, int, string*, Data);
	Statystyki();
};

#endif


