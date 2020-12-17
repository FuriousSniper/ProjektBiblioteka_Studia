#ifndef ADRESZAMIESZKANIA_H
#define ADRESZAMIESZKANIA_H
#include <string>
using namespace std;

class AdresZamieszkania {

public:

	string miasto;
	string kodPocztowy;
	string ulica;
	int numerMieszkania;

	void printAdresZamieszkania();
	AdresZamieszkania(string, string, string, int);
};

#endif
