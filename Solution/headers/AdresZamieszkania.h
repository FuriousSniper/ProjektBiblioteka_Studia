#ifndef ADRESZAMIESZKANIA_H
#define ADRESZAMIESZKANIA_H
#include <string>
using namespace std;
class AdresZamieszkania {

public:
	string miasto;
	string kodPocztowy;
	string ulica;

	void printAdresZamieszkania();

	AdresZamieszkania(string miasto, string kodPocztowy, string ulica);
};

#endif
