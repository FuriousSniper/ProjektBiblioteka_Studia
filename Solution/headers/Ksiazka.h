#ifndef KSIAZKA_H
#define KSIAZKA_H
#include "Czytelnik.h"
#include "Autor.h"
#include "Data.h"
#include "Czytelnik.h"
using namespace std;

class BookCopy;
class Author;
class Book {

private:
	string tytul;
	Author* autorzy;
	string* tagi;
	string kategoria;
	BookCopy** egzemplarze;
	int id;
	int iloscEgzemplarzy;
	Date dataPremiery;
	int iloscEgzemplarzyKsiazki;

public:
	string getTytul();
	Author* getAutorzy();
	string* getTagi();
	void setTagi(string* tagi);
	Date getDataPremiery();
	void dodajEgzemplarz(BookCopy* egzemplarz);
	BookCopy** getEgzemplarze();
	int usunEgzemplarz(BookCopy* e);
	int getId();
	string getKategoria();
	int getIloscEgzemplarzy();
	Book(string tytul, Author* autorzy, int id, Date dataPremiery);
	Book(string tytul, Author* autorzy, int id, Date dataPremiery, BookCopy* egzemplarz);
	Book(string tytul, Author* autorzy, int id, Date dataPremiery, BookCopy** egzemplarze);
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