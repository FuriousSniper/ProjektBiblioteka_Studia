#include "..\headers\Statystyki.h"

Statystyki::Statystyki() : dataPierszegoWypozyczenia(Data()), iloscWypozyczonychOdDolaczenia(0), preferowaneTematy(NULL), dataDolaczenia(Data()) {}

Statystyki::Statystyki(Data dataPW, int iloscWOD, string* prefTem, Data dataDol) : dataPierszegoWypozyczenia(dataPW), iloscWypozyczonychOdDolaczenia(iloscWOD), preferowaneTematy(prefTem), dataDolaczenia(dataDol) {}


