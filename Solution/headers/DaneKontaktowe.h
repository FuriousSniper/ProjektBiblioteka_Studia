#ifndef DANEKONTAKTOWE_H
#define DANEKONTAKTOWE_H
#include <string>
#include "Czytelnik.h"
class Czytelnik;
using namespace std;
class DaneKontaktowe {

public:
	string email;
	string telefon;

	void printDaneKontaktowe();

	Czytelnik* getCzytelnik();

	DaneKontaktowe(string email, string telefon);
};

#endif
