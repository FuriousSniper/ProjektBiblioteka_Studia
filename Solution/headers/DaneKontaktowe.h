#ifndef DANEKONTAKTOWE_H
#define DANEKONTAKTOWE_H
#include <string>
#include "Czytelnik.h"
#include "AdresZamieszkania.h"
class Czytelnik;
using namespace std;

class DaneKontaktowe {

public:

	string email;
	string telefon;
	AdresZamieszkania adres;

	void printDaneKontaktowe();
	DaneKontaktowe(string email, string telefon, AdresZamieszkania adres);
	DaneKontaktowe();
};

#endif
