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

	void printAdresZamieszkania() const;
	AdresZamieszkania(string, string, string, int);
	AdresZamieszkania();
	string getMiasto();
	string getKodPocztowy();
	string getUlica();
	int getNumerMieszkania();
};

#endif
