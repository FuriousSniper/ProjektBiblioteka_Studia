#include "..\headers\AdresZamieszkania.h"
#include <iostream>

void AdresZamieszkania::printAdresZamieszkania() {
	cout << "ul. " << ulica << " " << numerMieszkania << " " << miasto << " " << kodPocztowy << endl;
}

AdresZamieszkania::AdresZamieszkania(string miasto, string kodPocztowy, string ulica, int numerMieszkania) : miasto(miasto), kodPocztowy(kodPocztowy), ulica(ulica), numerMieszkania(numerMieszkania) {};

