#ifndef Ui_h
#define Ui_h
#include "..\headers\Osoba.h"
#include "..\headers\Data.h"
#include "..\headers\Autor.h"
#include "..\headers\Czytelnik.h"
#include "..\headers\Adres.h"
#include "..\headers\Bibliotekarz.h"
#include "..\headers\Biblioteka.h"
#include "..\ProjektBiblioteka\Libraries\sqlite3\sqlite3.h"
#include <string>
#include <vector>

using namespace std;
class Ui {
private:
public:
	//funkcja do tworzenia obiektu klasy Osoba przez uzytkownika
	//zwraca ona obiekt, ktory tworzy
	Osoba createOsoba(sqlite3*bazaDanych);

	//funkcja do tworzenia obiektu klasy Autor przez uzytkownika
	//zwraca ona obiekt, ktory tworzy
	Autor createAutor(sqlite3* bazaDanych);

	//Metoda do tworzenia nowego uzytkownika (bibliotekarza/czytelnika w zaleznosci od trybu).
	//Zwraca wskaznik na nowo utworzony obiekt.
	Osoba* createUzytkownik(int tryb, sqlite3* bazaDanych);

	//Dodaje uzytkownika (bibliotekarza/czytelnika w zaleznosci od trybu) do bazy danych.
	//Przyjmuje wskaznika na obiekt Osoba utworzony przez metode createUzytkownik.
	bool addUzytkownik(int tryb, sqlite3* bazaDanych, Osoba* osoba);

	//Wyswietla menu tworzenia hasla (wykorzystywane w metodzie createUzytkownik).
	string oknoTworzeniaHasla();

	//Sprawdza obecnosc maila przekazanego jako argument w bazach danych Czytelnik oraz Bibliotekarz.
	//Jezeli znajduje sie w jednej z tych baz zwraca false. W przeciwnym razie zwraca true.
	bool sprawdzDostepnoscEmail(sqlite3* bazaDanych, string email);

	//Sprawdza email pod katem wystepowania w nim odpowiedniego zakonczenia (@ oraz nazwy domeny).
	bool sprawdzPoprawnoscEmail(string email);
	
	//funkcja do tworzenia obiektu klasy Adres przez uzytkownika
	//zwraca ona obiekt, ktory tworzy
	Adres createAdres();
	
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

	//Metoda pozwalajaca zarejestrowac sie uzytkownikowi (zarowno bibliotekarzowi jak i czytelnikowi)
	//Tryb okresla typ tworzonego konta (bibliotekarz = 2/czytelnik = 1).
	//Jezeli rejestracja sie powiedzie, zwraca true. W przeciwnym razie zwraca false.
	bool zarejestruj(int tryb, sqlite3* bazaDanych);

	//Metoda pozwalajaca zalogowac sie na konto uzytkownikowi (zarowno bibliotekarzowi jak i czytelnikowi)
	//do metody przekazywany jest tryb okreslajacy osobe ktora sie loguje.
	//Zwraca wskaznik na obiekt typu Czytelnik lub Bibliotekarz w zaleznosci od trybu.
	Osoba* zaloguj(int tryb, sqlite3* bazaDanych);

	//funkcja dodajaca ksiazke do biblioteki.
	//po callu wymagane jest wpisanie tytulu i kategorii, aby dodac ksiazke
	bool addBook();

	int getBooks();

	//funkcja do zliczania ilosci wypozyczonych ksiazek przez czytelnika
	int getNumberOfLentBooks(Czytelnik c);

	//metoda do wypozyczania ksiazek. jako argumenty przyjmuje obiekt zalogowanego czytelnika oraz tytul wypozyczanej ksiazki. zwraca wartosc odpowiadajaca kodowi bledu (1 - sukces), (-1 - blad)
	int lendBook(Czytelnik c, string tytul);

	//metoda pozwalajaca na wyswietlenie ksiazek wypozyczonych przez czytelnika c
	int getUserBooks(Czytelnik c);

	//metoda do zwracania ksiazek. Czytelnik c - zalogowany czytelnik. pobieramy z niego imie i nazwisko potrzebne do zwracania.
	//isbn - nr ksiazki do zwrocenia
	int returnBook(Czytelnik c, string isbn);

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

	//metoda do sprawdzania, czy jakies egzemplarze ksiazki da sie wypozyczyc. parametr - tytul ksiazki do sprawdzenia. zwraca nr isbn egzemplarza gotowego do wypozyczenia
	string checkEgzemplarze(string tytul);

	//Metody wykorzystywane w menu po zalogowaniu czytelnika/bibliotekarza.
	int menuPoZalogowaniuCzytelnika(Czytelnik* czytelnik);
	int menuPoZalogowaniuBibliotekarza(Bibliotekarz*bibliotekarz, Biblioteka*biblioteka, sqlite3*bazaDanych);
	void wyborWMenuCzytelnika(int wybor);
	void wyborWMenuBibliotekarza(int wybor, Bibliotekarz*bibliotekarz, Biblioteka*biblioteka, sqlite3*bazaDanych);

	//Tworzy Bibliotekarza na podstawie danych w rekordzie tabeli Bibliotekarz.
	Bibliotekarz* wczytywanieBibliotekarza(sqlite3_stmt*);

	//Metoda do modyfikacji danych bibliotekarza.
	void zmienDaneBibliotekarza(Bibliotekarz* bibliotekarz, sqlite3* bazaDanych);

	//wczytywanie biblioteki do pamieci.
	//zwraca wskaznik na utworzony obiekt.
	Biblioteka* wczytywanieBiblioteki(sqlite3* bazaDanych);
};

#endif
