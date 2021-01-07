#ifndef EGZEMPLARZ_H
#define EGZEMPLARZ_H
#include "..\headers\Czytelnik.h"
#include "Ksiazka.h"
#include "Data.h"

class Reader;
using namespace std;
class Book;

class BookCopy {

private:

	int id;
	const int amountOfPages;
	const string isbnNumber;
	const string publisher;

public:

	int getId();
	void setId(int id);
	int getAmountOfPages();
	string getIsbnNumber();
	string getPublisher();

	BookCopy(int amountOfPages, string isbnNumber, string publisher);
	BookCopy();
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
