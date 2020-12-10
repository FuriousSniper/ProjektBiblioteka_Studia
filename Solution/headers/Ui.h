#ifndef Ui_h
#define Ui_h
#include "..\headers\Osoba.h"
#include "..\headers\Data.h"
#include "..\headers\Autor.h"
#include "..\headers\Czytelnik.h"
#include "..\headers\AdresZamieszkania.h"
#include <iostream>
#include <string>
using namespace std;
class Ui {
private:
public:
	//funkcja do tworzenia obiektu klasy Osoba przez uzytkownika
	//zwraca ona obiekt, ktory tworzy
	Osoba createOsoba();

	//funkcja do tworzenia obiektu klasy Autor przez uzytkownika
	//zwraca ona obiekt, ktory tworzy
	Autor createAutor();

	//funkcja do tworzenia obiektu klasy Czytelnik przez uzytkownika
	//zwraca ona obiekt, ktory tworzy
	Czytelnik createCzytelnik();

	//funkcja do tworzenia obiektu klasy Adres przez uzytkownika
	//zwraca ona obiekt, ktory tworzy
	AdresZamieszkania createAdres();
	//konstruktor obiektu Ui pozwalajacego na korzystanie z funkcji
	Ui();
};

#endif