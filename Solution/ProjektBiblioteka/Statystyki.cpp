#include "..\headers\Statystyki.h"

Statistics::Statistics() : dataPierszegoWypozyczenia(Data()), iloscWypozyczonychOdDolaczenia(0), preferowaneTematy(NULL), dataDolaczenia(Data()) {}

Statistics::Statistics(Date dataPW, int iloscWOD, string* prefTem, Date dataDol) : dataPierszegoWypozyczenia(dataPW), iloscWypozyczonychOdDolaczenia(iloscWOD), preferowaneTematy(prefTem), dataDolaczenia(dataDol) {}


