#include "..\headers\DaneKontaktowe.h"
#include "..\headers\AdresZamieszkania.h"
#include <string>
#include <iostream>
#include "AdresZamieszkania.cpp"

void DaneKontaktowe::printDaneKontaktowe() {
	cout << "Dane kontaktowe:" << endl << "\tTelefon: " << this->telefon << endl << "\tEmail: " << this->email << endl << "\tAdres zamieszkania: ";
}

DaneKontaktowe::DaneKontaktowe(string email, string telefon): email(email), telefon(telefon) {}

DaneKontaktowe::DaneKontaktowe() : email("nie podano"), telefon("nie podano") {}