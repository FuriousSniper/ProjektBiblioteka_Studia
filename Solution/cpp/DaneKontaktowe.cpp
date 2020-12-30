#include "..\headers\DaneKontaktowe.h"
#include "..\headers\AdresZamieszkania.h"
#include <string>
#include <iostream>

void DaneKontaktowe::printDaneKontaktowe() {
	cout << "Dane kontaktowe:" << endl << "\tTelefon: " << this->telefon << endl << "\tEmail: " << this->email << endl << "\tAdres zamieszkania: ";
	adres.printAdresZamieszkania();
}

DaneKontaktowe::DaneKontaktowe(string email, string telefon, AdresZamieszkania adres): email(email), telefon(telefon), adres(adres) {}

DaneKontaktowe::DaneKontaktowe() : email("nie podano"), telefon("nie podano"), adres(AdresZamieszkania()) {}