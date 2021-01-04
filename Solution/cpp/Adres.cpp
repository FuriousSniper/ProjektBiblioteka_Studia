#include "..\headers\Adres.h"
#include <iostream>

void Adres::printAdres() const {
	cout << "ul. " << ulica << " " << numerMieszkania << " " << miasto << " " << kodPocztowy << endl;
}

Adres::Adres(string miasto, string kodPocztowy, string ulica, int numerMieszkania) : miasto(miasto), kodPocztowy(kodPocztowy), ulica(ulica), numerMieszkania(numerMieszkania) {};

Adres::Adres() : miasto("nie podano"), kodPocztowy("nie podano"), ulica("nie podano"), numerMieszkania(0) {}

string Adres::getKodPocztowy() {
	return this->kodPocztowy;
}
string Adres::getMiasto() {
	return this->miasto;
}
string Adres::getUlica() {
	return this->ulica;
}
int Adres::getNumerMieszkania() {
	return this->numerMieszkania;
}