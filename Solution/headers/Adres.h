#ifndef ADRES_H
#define ADRES_H
#include <string>
using namespace std;

class Adres {

public:

	string miasto;
	string kodPocztowy;
	string ulica;
	int numerMieszkania;

	void printAdres() const;
	Adres(string, string, string, int);
	Adres();
	string getMiasto();
	string getKodPocztowy();
	string getUlica();
	int getNumerMieszkania();
};

#endif
