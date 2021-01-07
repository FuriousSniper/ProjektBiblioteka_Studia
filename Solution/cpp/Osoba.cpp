#include "..\headers\Osoba.h"
#include "..\headers\Adres.h"
#include <iostream>
#include <ctime>

string Person::getLastName() {
	return this->nazwisko;
}

string Person::getFirstName() {
	return this->imie;
}

int Person::getAge() {
	return this->wiek;
}

Adress Person::getAdress() {
	return this->adres;
}

string Person :: getEmailAdress() {
	return this->email;
}

string Person :: getPhoneNumber() {
	return this->telefon;
}

Date Person::getBirthDate() {
	return this->dataUrodzenia;
}

int Person::setWiek(int age) {
	this->wiek = age;
	return this->wiek;
}

void Person::setPhoneNumber(string telefon) {
	this->telefon = telefon;
}

void Person::setEmailAdress(string email) {
	this->email = email;
}

void Person::printPerson() {
	
	cout << "Dane osobowe:" << endl;
	cout << "\timie: " << this->imie << endl << "\tnazwisko: " << this->nazwisko << endl << "\tdata urodzenia: ";
	dataUrodzenia.printData();
	cout << "\twiek: ";

	if (wiek == 0) {
		cout << "nie podano" << endl;
	}
	else {
		cout << this->wiek << endl;
	}

	cout << "\te-mail: " << this->email << endl;
	cout << "\ttelefon: " << this->telefon << endl;
	cout << "\tadres zamieszkania: ";
	adres.printAdress();
}

void Person::setDaneKontaktowe(string email, string telefon) {
	this->email = email;
	this->telefon = telefon;
}

void Person :: setAdresZamieszkania(Adress adres) {
	this->adres = adres;
}

Person::Person(string imie, string nazwisko, int d, int m, int r):imie(imie),nazwisko(nazwisko), dataUrodzenia(Data(d,m,r)), 
adres(Adres()), email("nie podano"), telefon("nie podano"){
	time_t t = time(NULL);
	tm* buf = new tm;
	localtime_s(buf,&t);
	this->wiek = buf->tm_year + 1900 - r;
}

Person::Person(string imie, string nazwisko) : imie(imie), nazwisko(nazwisko),dataUrodzenia(Data()), wiek(0), email("nie podano"),telefon("nie podano"),
adres(Adres()){
}

Person::Person() : imie("nie podano"), nazwisko("nie podano"), email("nie podano"), telefon("nie podano"), dataUrodzenia(Data()), wiek(0),
adres(Adres()){}

Person::Person(string imie, string nazwisko, string email, string telefon, int d, int m, int r, Adress adres) : imie(imie), nazwisko(nazwisko), email(email), telefon(telefon), dataUrodzenia(Data(d,m,r)), adres(adres) {
	time_t t = time(NULL);
	tm* buf = new tm;
	localtime_s(buf,&t);
	this->wiek = buf->tm_year + 1900 - r;
}


