#ifndef CZYTELNIK_H
#define CZYTELNIK_H
using namespace std;

#include <string>
#include "Date.h"
#include "Adress.h"
#include "BookCopy.h"
#include "Person.h"

class BookCopy;
class Person;

class Reader: public Person {

private:

	const int ID;
	//string* preferredCategories;
	string password;

public:

	Reader(string firstName, string lastName, int id);
	Reader(string firstName, string lastName, string emailAdress, string phoneNumber, int day, int month, int year, Adress, string password, int ID);
	Reader();
	void printReaderInfo();
	void setPassword(string newPassword);
	string getPassword();
	const int getID();
};

#endif

//w bazie danych CZYTELNIK
/*
	"ID INT PRIMARY        KEY      ,"
	"listaZaleglosci       TEXT     ,"
	"dataPierwszegoWypozyczenia     DATE     ,"
	"iloscWypozyczonychOdDolaczenia  INT             ,"
	"preferowaneTematy     TEXT             ,"
	"dataDolaczenia        DATE             ,"
	"miasto				   TEXT             ,"
	"kodPocztowy           TEXT             ,"
	"ulica                 TEXT             ,"
	"imie                  TEXT             ,"
	"nazwisko              TEXT             ,"
	"wiek                  TEXT             ,"
	"dataUrodzenia         DATE             ,"
	"haslo				   TEXT				,"
	"numerMieszkania       TEXT             
	"ksiazka1			   TEXT				,"
	"ksiazka2			   TEXT				,"
	"ksiazka3			   TEXT				,"
	);";
*/
