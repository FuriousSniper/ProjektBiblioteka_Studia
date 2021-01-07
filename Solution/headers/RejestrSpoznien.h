#ifndef REJESTRSPOZNIEN_H
#define REJESTRSPOZNIEN_H
#include "Czytelnik.h"
using namespace std;
class RejestrSpoznien {

private:
	Reader spoz_osoba;

public:
	void addRejestrSpoznien(Reader spoz_osoba);
	void removeRejestrSpoznien(Reader spoz_osoba);
	void printRejestrSpoznien();
};

#endif
