#ifndef ADRESZAMIESZKANIA_H
#define ADRESZAMIESZKANIA_H

class AdresZamieszkania {

public:
	string miasto;
	string kodPocztowy;
	string ulica;

	void printAdresZamieszkania();

	AdresZamieszkania(string miasto, string kodPocztowy, string ulica);
};

#endif
