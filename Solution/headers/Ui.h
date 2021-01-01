#ifndef Ui_h
#define Ui_h
#include "..\headers\Osoba.h"
#include "..\headers\Data.h"
#include "..\headers\Autor.h"
#include "..\headers\Czytelnik.h"
#include "..\headers\AdresZamieszkania.h"
#include "..\headers\Bibliotekarz.h"
#include "..\ProjektBiblioteka\Libraries\sqlite3\sqlite3.h";
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

	//funkcja do tworzenia obiektu klasy Czytelnik
	//zwraca ona obiekt, ktory tworzy

	Czytelnik createCzytelnik(sqlite3* database);

	//metoda do tworzenia obiektu klasy Bibliotekarz przez użytkownika,
	//zwraca utworzony obiekt.

	Bibliotekarz createBibliotekarz(sqlite3* database);

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

	bool addCzytelnik(Czytelnik new_user, sqlite3* database);
	bool addBibliotekarz(Bibliotekarz new_user, sqlite3* database);
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

	//metoda pozwalajaca na dodawanie nowego autora (od zera)
	int addAutor();
	//dodawanie nowego autora od zera
	int addAutor2(string imie, string ksiazka);
	//aktualizacja, dodawanie nowego autora
	int addAutor3(string imie, string ksiazka);
	//funkcja do splitowania stringa za pomoca delimitera. arg 1 - string do podzielenia. arg 2 - delimiter. zwraca vector (uzywany jako tablica do prostego przejscia i wykonania czegos)
	std::vector<std::string> split_string(std::string stringToBeSplitted, std::string delimeter);
};

#endif
