#ifndef OSOBA_H
#define OSOBA_H
#include <string>
#include "Data.h"
#include "Adres.h"

using namespace std;

class Person {

private:

	const string imie;
	const string nazwisko;
	int wiek;
	const Date dataUrodzenia;
	string email;
	string telefon;
	Adress adres;

public:

	string getLastName();
	string getFirstName();
	string getEmailAdress();
	string getPhoneNumber();
	Adress getAdress();
	void setAdresZamieszkania(Adress adres);
	Date getBirthDate();
	int getAge();

	void setDaneKontaktowe(string email, string telefon);
	int setWiek(int wiek);
	void setPhoneNumber(string telefon);
	void setEmailAdress(string email);

	Person(string imie, string nazwisko, int d, int m, int r);
	Person(string imie, string nazwisko, string email, string telefon, int d, int m, int r, Adress adres);
	Person(string imie, string nazwisko);
	Person();

	void printPerson();
};

#endif
