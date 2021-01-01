#ifndef DANEKONTAKTOWE_H
#define DANEKONTAKTOWE_H
#include <string>
#include "Czytelnik.h"
class Czytelnik;
using namespace std;

class DaneKontaktowe {
private:

public:
	string email;
	string telefon;
	void printDaneKontaktowe();
	DaneKontaktowe(string email, string telefon);
	DaneKontaktowe();
};

#endif
