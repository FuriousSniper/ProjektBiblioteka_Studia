#ifndef KSIAZKA_H
#define KSIAZKA_H
#include "Czytelnik.h"
#include "Autor.h"
#include "Data.h"
#include "Czytelnik.h"
using namespace std;
class Egzemplarz;
class Autor;
class Ksiazka {

private:
	string tytul;
	Autor* autorzy;
	string* tagi;
	string kategoria;
	Egzemplarz** egzemplarze;
	int id;
	int iloscEgzemplarzy;
	Data dataPremiery;
	int iloscEgzemplarzyKsiazki;

public:
	string getTytul();
	Autor* getAutorzy();
	string* getTagi();
	void setTagi(string* tagi);
	Data getDataPremiery();
	void dodajEgzemplarz(Egzemplarz* egzemplarz);
	Egzemplarz** getEgzemplarze();
	int usunEgzemplarz(Egzemplarz* e);
	int getId();
	string getKategoria();
	int getIloscEgzemplarzy();
	Ksiazka(string tytul, Autor* autorzy, int id, Data dataPremiery);
	Ksiazka(string tytul, Autor* autorzy, int id, Data dataPremiery, Egzemplarz* egzemplarz);
	Ksiazka(string tytul, Autor* autorzy, int id, Data dataPremiery, Egzemplarz** egzemplarze);
};

#endif
