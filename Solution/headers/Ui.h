#ifndef Ui_h
#define Ui_h
#include "Person.h"
#include "Date.h"
#include "Author.h"
#include "Reader.h"
#include "Adress.h"
#include "Librarian.h"
#include "Library.h"
#include "..\ProjektBiblioteka\Libraries\sqlite3\sqlite3.h"
#include <string>
#include <vector>

using namespace std;
class Ui {
private:
public:
	//funkcja do tworzenia obiektu klasy Osoba przez uzytkownika
	//zwraca ona obiekt, ktory tworzy
	Person createPerson(sqlite3*bazaDanych);

	//funkcja do tworzenia obiektu klasy Autor przez uzytkownika
	//zwraca ona obiekt, ktory tworzy
	Author createAuthor(sqlite3* bazaDanych);

	//Metoda do tworzenia nowego uzytkownika (bibliotekarza/czytelnika w zaleznosci od trybu).
	//Zwraca wskaznik na nowo utworzony obiekt.
	Person* createUser(int tryb, sqlite3* bazaDanych);

	//Dodaje uzytkownika (bibliotekarza/czytelnika w zaleznosci od trybu) do bazy danych.
	//Przyjmuje wskaznika na obiekt Osoba utworzony przez metode createUzytkownik.
	bool addUserToDataBase(int tryb, sqlite3* bazaDanych, Person* osoba);

	//Wyswietla menu tworzenia hasla (wykorzystywane w metodzie createUzytkownik).
	string createPasswordWindow();

	//Sprawdza obecnosc maila przekazanego jako argument w bazach danych Czytelnik oraz Bibliotekarz.
	//Jezeli znajduje sie w jednej z tych baz zwraca false. W przeciwnym razie zwraca true.
	bool checkEmailAvailability(sqlite3* bazaDanych, string email);

	//Sprawdza email pod katem wystepowania w nim odpowiedniego zakonczenia (@ oraz nazwy domeny).
	bool validateEmail(string email);
	
	//funkcja do tworzenia obiektu klasy Adres przez uzytkownika
	//zwraca ona obiekt, ktory tworzy
	Adress createAdress();
	
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
	bool registerUser(int tryb, sqlite3* bazaDanych);

	//Metoda pozwalajaca zalogowac sie na konto uzytkownikowi (zarowno bibliotekarzowi jak i czytelnikowi)
	//do metody przekazywany jest tryb okreslajacy osobe ktora sie loguje.
	//Zwraca wskaznik na obiekt typu Czytelnik lub Bibliotekarz w zaleznosci od trybu.
	Person* logIn(int tryb, sqlite3* bazaDanych);

	//funkcja dodajaca ksiazke do biblioteki.
	//po callu wymagane jest wpisanie tytulu i kategorii, aby dodac ksiazke
	bool addBook();

	//metoda pozwalajaca na wypisanie wszystkich ksiazek znajdujacych sie w bazie
	int getBooks();

	//funkcja do zliczania ilosci wypozyczonych ksiazek przez czytelnika
	int getNumberOfLentBooks(Reader c);

	//metoda sprawdzajaca, czy czytelnik wypozyczyl ksiazke podana w argumencie i jesli tak, to zwraca, w ktorej kolumnie jest ona zapisana
	int getSpecificUserBook(Reader c, string isbn);

	//metoda do wypozyczania ksiazek. jako argumenty przyjmuje obiekt zalogowanego czytelnika oraz tytul wypozyczanej ksiazki. zwraca wartosc odpowiadajaca kodowi bledu (1 - sukces), (-1 - blad)
	int lendBook(Reader c, string title);

	//metoda pozwalajaca na wyswietlenie ksiazek wypozyczonych przez czytelnika c
	int getUserBooks(Reader c);

	//metoda do zwracania ksiazek. Czytelnik c - zalogowany czytelnik. pobieramy z niego imie i nazwisko potrzebne do zwracania.
	//isbn - nr ksiazki do zwrocenia
	int returnBook(Reader c, string isbn);

	//metoda dodajaca egzemplarz danej ksiazki do bazy danych
	int addCopy1();
	//metoda dodajaca egzemplarz danej ksiazki do bazy danych. jako parametr przyjmuje nr isbn dodawanej ksiazki, co pozwala na uproszczenie funkcji dodawania ksiazek.
	int addCopy2(string isbn, string title);

	//metoda pozwalajaca na dodawanie nowego autora (od zera)
	int getAuthor();
	//dodawanie nowego autora od zera. parametry - imie oraz tytul ksiazki, ktora autor napisal
	int getAuthor2(string name, string title);
	//aktualizacja, dodawanie nowego autora, sprawdzanie czy taki istnieje, dopisywanie ksiazek
	int addAuthor3(string name, string title);

	//metoda do sprawdzania, czy jakies egzemplarze ksiazki da sie wypozyczyc. parametr - tytul ksiazki do sprawdzenia. zwraca nr isbn egzemplarza gotowego do wypozyczenia
	string checkCopiesList(string title);

	//Metody wykorzystywane w menu po zalogowaniu czytelnika/bibliotekarza.
	int readerMenuChoice(Reader* czytelnik);
	int librarianMenu(Librarian*bibliotekarz, Library*biblioteka, sqlite3*bazaDanych);
	void readerMenu(int wybor);
	void librarianMenuChoice(int wybor, Librarian*bibliotekarz, Library*biblioteka, sqlite3*bazaDanych);

	//Tworzy Bibliotekarza na podstawie danych w rekordzie tabeli Bibliotekarz.
	Librarian* loadLibrarian(sqlite3*dataBase, string query);

	//Metoda do modyfikacji danych bibliotekarza.
	void changeLibrarianData(Librarian* bibliotekarz, sqlite3* bazaDanych);

	//wczytywanie biblioteki do pamieci.
	//zwraca wskaznik na utworzony obiekt.
	Library* loadLibrary(sqlite3* bazaDanych);
};

#endif
