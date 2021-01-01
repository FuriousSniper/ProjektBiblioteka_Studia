#pragma once
#include "..\headers\Data.h"


class Statystyki{

	//Statystyki odnosnie konta czytelnika.

	Data dataPierszegoWypozyczenia;
	int iloscWypozyczonychOdDolaczenia;
	string* preferowaneTematy;
	Data dataDolaczenia;

public:

	Statystyki(Data, int, string*, Data);
	Statystyki();
};

