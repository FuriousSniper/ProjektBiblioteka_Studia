#include "..\headers\AdresZamieszkania.h"
#include <iostream>

void AdresZamieszkania::printAdresZamieszkania() {
	cout << "ul. " << ulica << " " << numerMieszkania << " " << miasto << " " << kodPocztowy << endl;
}

AdresZamieszkania::AdresZamieszkania(string miasto, string kodPocztowy, string ulica, int numerMieszkania) : miasto(miasto), kodPocztowy(kodPocztowy), ulica(ulica), numerMieszkania(numerMieszkania) {};

string AdresZamieszkania::getKodPocztowy() {
	return this->kodPocztowy;
}
string AdresZamieszkania::getMiasto() {
	return this->miasto;
}
string AdresZamieszkania::getUlica() {
	return this->ulica;
}
int AdresZamieszkania::getNumerMieszkania() {
	return this->numerMieszkania;
}