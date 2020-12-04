#ifndef DANEKONTAKTOWE_H
#define DANEKONTAKTOWE_H

class DaneKontaktowe {

public:
	string email;
	string telefon;

	void printDaneKontaktowe();

	Czytelnik* getCzytelnik();

	DaneKontaktowe(string email, string telefon);
};

#endif
