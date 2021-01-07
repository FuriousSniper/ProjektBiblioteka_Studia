#ifndef KSIAZKA_H
#define KSIAZKA_H
#include "Reader.h"
#include "Author.h"
#include "Date.h"
#include "Reader.h"
using namespace std;

class BookCopy;
class Author;

class Book {

private:

	int id;
	const string title;
	const Author* authors;
	const Date releaseDate;
	string category;
	int amountOfCopies;

public:
	string getTitle();
	const Author* getAuthors();
	Date getReleaseDate();
	int getId();
	string getCategory();
	int getAmountOfCopies();
	Book(string tytul, Author* autorzy, int id, Date dataPremiery);
};

#endif

//w bazie danych KSIAZKA
/*
ID				INT		//id w bazie danych
tytul			TEXT	//tytul ksiazki
autorzy			TEXT	//autorzy ksiazki. moze byc kilku. wpisywac z delimiterem "||". przyklad: "Sasha Kostylev||Niko Kovac"
tagi			TEXT	//tagi ksiazki. przyklad - biznes, bestseller, itd. wpisywac z ||
kategoria		TEXT	//kategoria ksiazki, np. romans, przygodowa, podroznicza
egzemplarze		TEXT	//nr isbn poszczegolnych egzemplarzy (odpowiada tym z tabeli EGZEMPLARZE). wpisywac z delimiterem "||"
dataPremiery	DATE	//data premiery ksiazki
*/