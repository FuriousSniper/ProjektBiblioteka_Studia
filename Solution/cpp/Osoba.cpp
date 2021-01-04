#include "..\headers\Osoba.h"
#include "..\headers\Adres.h"
#include <iostream>
#include <ctime>

string Osoba::getNazwisko() {
	return this->nazwisko;
}

string Osoba::getImie() {
	return this->imie;
}

int Osoba::getWiek() {
	return this->wiek;
}

Adres Osoba::getAdresZamieszkania() {
	return this->adres;
}

string Osoba :: getEmail() {
	return this->email;
}

string Osoba :: getTelefon() {
	return this->telefon;
}

Data Osoba::getDataUrodzenia() {
	return this->dataUrodzenia;
}

int Osoba::setWiek(int age) {
	this->wiek = age;
	return this->wiek;
}

void Osoba::setTelefon(string telefon) {
	this->telefon = telefon;
}

void Osoba::setEmail(string email) {
	this->email = email;
}

void Osoba::printOsoba() {
	
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
	adres.printAdres();
}

void Osoba::setDaneKontaktowe(string email, string telefon) {
	this->email = email;
	this->telefon = telefon;
}

void Osoba :: setAdresZamieszkania(Adres adres) {
	this->adres = adres;
}

Osoba::Osoba(string imie, string nazwisko, int d, int m, int r):imie(imie),nazwisko(nazwisko), dataUrodzenia(Data(d,m,r)), 
adres(Adres()), email("nie podano"), telefon("nie podano"){
	time_t t = time(NULL);
	tm* buf = new tm;
	localtime_s(buf,&t);
	this->wiek = buf->tm_year + 1900 - r;
}

Osoba::Osoba(string imie, string nazwisko) : imie(imie), nazwisko(nazwisko),dataUrodzenia(Data()), wiek(0), email("nie podano"),telefon("nie podano"),
adres(Adres()){
}

Osoba::Osoba() : imie("nie podano"), nazwisko("nie podano"), email("nie podano"), telefon("nie podano"), dataUrodzenia(Data()), wiek(0),
adres(Adres()){}

Osoba::Osoba(string imie, string nazwisko, string email, string telefon, int d, int m, int r, Adres adres) : imie(imie), nazwisko(nazwisko), email(email), telefon(telefon), dataUrodzenia(Data(d,m,r)), adres(adres) {
	time_t t = time(NULL);
	tm* buf = new tm;
	localtime_s(buf,&t);
	this->wiek = buf->tm_year + 1900 - r;
}


