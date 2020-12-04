#ifndef REJESTRSPOZNIEN_H
#define REJESTRSPOZNIEN_H
#include "Czytelnik.h"
using namespace std;
class RejestrSpoznien {

private:
	Czytelnik spoz_osoba;

public:
	void addRejestrSpoznien(Czytelnik spoz_osoba);
	void removeRejestrSpoznien(Czytelnik spoz_osoba);
	void printRejestrSpoznien();
};

#endif
