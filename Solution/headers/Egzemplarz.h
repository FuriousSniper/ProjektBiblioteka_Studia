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
	string numerISBN;
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
	string getNumerISBN();
	string getWydawnictwo();
	Egzemplarz(int iloscStron, string nrISBN, string wydawnictwo, Data dataZakupu);
	Egzemplarz(int iloscStron, string nrISBN, string wydawnictwo);
	Egzemplarz();

};

#endif
//w bazie danych EGZEMPLARZE
/*
 ID				INT PRIMARY        KEY,	//id w bazie danych
 iloscStron		INT		NOT NULL;	//ilosc stron ksiazki
 numerISBN		TEXT	NOT NULL	//nr isbn ksiazki
 wydawnictwo	TEXT				//nazwa wydawnictwa
 osobaWyp		TEXT				//imie i nazwisko czytelnika, ktory wypozyczyl ksiazke (z bazy danych)
dataWyp			DATE				//data, w ktorej czytelnik wypozyczyl ksiazke
dataOdd			DATE				//data, do ktorej przedluzajacy ma oddac ksiazke
przedluzony		BOOLEAN				//czy ksiazka jest przedluzona?
przetrzymany	INT					//ilosc dni, ktora osoba wypozyczajaca przetrzymala ksiazke po zakonczeniu terminu
ksiazka			TEXT				//tytul ksiazki
*/
