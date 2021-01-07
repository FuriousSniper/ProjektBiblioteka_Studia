#ifndef STATYSTYKI_H
#define STATYSTYKI_H

#include "..\headers\Data.h"


class Statistics {

	//Statystyki odnosnie konta czytelnika.

	Date dataPierszegoWypozyczenia;
	int iloscWypozyczonychOdDolaczenia;
	string* preferowaneTematy;
	Date dataDolaczenia;

public:

	Statistics(Date, int, string*, Date);
	Statistics();
};

#endif


