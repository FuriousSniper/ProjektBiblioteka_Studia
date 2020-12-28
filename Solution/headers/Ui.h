#ifndef Ui_h
#define Ui_h
#include "..\headers\Osoba.h"
#include "..\headers\Data.h"
#include "..\headers\Autor.h"
#include "..\headers\Czytelnik.h"
#include "..\headers\AdresZamieszkania.h"
#include "../ProjektBiblioteka/Libraries/sqlite3/sqlite3.h";
#include <iostream>
#include <string>
#include <vector>
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
	
	//funkcja do wyboru pierwszej akcji uzytkownika. 
	//umozliwia wybranie logowania lub rejestracji
	// 1 - logowanie
	// 2 - rejestracja
	// inne - blad
	int signInUpMenu();

	//funkcja w ktorej uzytkownik wybiera typ konta, na ktore sie loguje
	// 1- czytelnik
	// 2 - bibliotekarz
	// inne - blad
	int chooseUserType();
	//konstruktor obiektu Ui pozwalajacego na korzystanie z funkcji
	Ui();
	//funkcja w ktorej uzytkownik wybiera typ konta, na ktore sie rejestruje
	int chooseUserTypeRegistration();
	bool confirmVerification();

	//funkcja dodajaca ksiazke do biblioteki.
	//po callu wymagane jest wpisanie tytulu i kategorii, aby dodac ksiazke
	bool addBook();

	int getBooks();

	//funkcja do zliczania ilosci wypozyczonych ksiazek przez czytelnika
	int getNumberOfLentBooks(Czytelnik c);

	//metoda do wypozyczania ksiazek. jako argumenty przyjmuje obiekt zalogowanego czytelnika oraz nr isbn wypozyczanej ksiazki. zwraca wartosc odpowiadajaca kodowi bledu (1 - sukces)
	int lendBook(Czytelnik c, string isbn);

	//metoda dodajaca egzemplarz danej ksiazki do bazy danych
	int addEgzemplarz();
	//metoda dodajaca egzemplarz danej ksiazki do bazy danych. jako parametr przyjmuje nr isbn dodawanej ksiazki, co pozwala na uproszczenie funkcji dodawania ksiazek.
	int addEgzemplarz2(string isbn, string tytul);


	//funkcja do splitowania stringa za pomoca delimitera. arg 1 - string do podzielenia. arg 2 - delimiter. zwraca vector (uzywany jako tablica do prostego przejscia i wykonania czegos)
	std::vector<std::string> split_string(std::string stringToBeSplitted, std::string delimeter);
};

#endif
