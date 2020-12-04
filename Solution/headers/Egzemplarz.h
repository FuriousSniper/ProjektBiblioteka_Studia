#ifndef EGZEMPLARZ_H
#define EGZEMPLARZ_H
#include "..\headers\Czytelnik.h"
#include "Ksiazka.h"
#include "Data.h"
class Czytelnik;
using namespace std;
class Ksiazka;
class Egzemplarz {

private:
	int iloscStron;
	int numerISBN;
	string wydawnictwo;
	Data dataZakupu;
	Czytelnik* osobaWyp;
	Data dataWyp;
	Data dataOdd;
	int id;
	bool przedluzony = false;
	int przetrzymany = 0;
	Ksiazka* ksiazka;
public:
	Czytelnik* getOsobaWyp();
	int setOsobaWyp(Czytelnik* osobaWyp);
	Data getDataWyp();
	void setDataWyp(Data dataWyp);
	Data getDataOdd();
	void setDataOdd(Data dataOdd);
	int getId();
	void setId(int id);
	bool getPrzedluzony();
	void setPrzedluzony(bool przedluzony);
	int getPrzetrzymany();
	void setPrzetrzymany(int p);
	Data getDataZakupu();
	int getIloscStron();
	int getNumerISBN();
	string getWydawnictwo();
	Egzemplarz(int iloscStron, int nrISBN, string wydawnictwo, Data dataZakupu);
	Egzemplarz(int iloscStron, int nrISBN, string wydawnictwo);

};

#endif
