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

	//metoda do tworzenia obiektu klasy Bibliotekarz przez u¿ytkownika,
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

	//Metoda pozwalajaca zalogowac sie na konto uzytkownikowi (zarowno bibliotekarzowi jak i czytelnikowi)
	//do metody przekazywany jest tryb okreslajacy osobe ktora sie loguje.
	//Zwraca wskaznik na obiekt typu Czytelnik lub Bibliotekarz w zaleznosci od trybu.

	bool zaloguj(int tryb, sqlite3* bazaDanych);

	bool addCzytelnik(Czytelnik new_user, sqlite3* database);
	bool addBibliotekarz(Bibliotekarz new_user, sqlite3* database);
	//funkcja dodajaca ksiazke do biblioteki.
	//po callu wymagane jest wpisanie tytulu i kategorii, aby dodac ksiazke
	bool addBook();

	int getBooks();

	//funkcja do zliczania ilosci wypozyczonych ksiazek przez czytelnika
	int getNumberOfLentBooks(Czytelnik c);

	//metoda do wypozyczania ksiazek. jako argumenty przyjmuje obiekt zalogowanego czytelnika oraz tytul wypozyczanej ksiazki. zwraca wartosc odpowiadajaca kodowi bledu (1 - sukces), (-1 - blad)
	int lendBook(Czytelnik c, string tytul);

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
	//metoda do sprawdzania, czy jakies egzemplarze ksiazki da sie wypozyczyc. parametr - tytul ksiazki do sprawdzenia. zwraca nr isbn egzemplarza gotowego do wypozyczenia
	string checkEgzemplarze(string tytul);
	//Metody wykorzystywane w menu po zalogowaniu czytelnika/bibliotekarza.

	int menuPoZalogowaniuCzytelnika(Czytelnik* czytelnik);
	int menuPoZalogowaniuBibliotekarza(Bibliotekarz*bibliotekarz, sqlite3*bazaDanych);
	void wyborWMenuCzytelnika(int wybor);
	void wyborWMenuBibliotekarza(int wybor, Bibliotekarz*bibliotekarz, sqlite3*bazaDanych);

private:

	//Metody prywatne, bo sa wykorzystywane tylko wewnatrz klasy (wewnatrz innych metod klasy).

	//Konwertuje string'a (WAZNE: musi byc to data pobrana z bazy danych) na obiekt typu Data.
	Data konwersjaNaData(string napis);

	//Konwertuje wskaznik (const unsigned char*) zwracany przez funkcje sqlite3_column_text
	//na string (const char*).
	string konwersjaNaString(const unsigned char*);

	//Tworzy Bibliotekarza na podstawie danych w rekordzie tabeli Bibliotekarz.
	Bibliotekarz* wczytywanieBibliotekarza(sqlite3_stmt*);

	//Metoda do modyfikacji danych bibliotekarza.

	void zmienDaneBibliotekarza(Bibliotekarz* bibliotekarz, sqlite3* bazaDanych);

};

#endif
