#include "..\headers\Adres.h"
#include <iostream>

void Adress::printAdress() const {
	cout << "ul. " << street << " " << flatNumber << " " << city << " " << zipCode << endl;
}

Adress::Adress(string city, string zipCode, string street, int flatNumber) : city(city), zipCode(zipCode), street(street), flatNumber(flatNumber) {};

Adress::Adress() : city("nie podano"), zipCode("nie podano"), street("nie podano"), flatNumber(0) {}

string Adress::getZipCode() {
	return this->zipCode;
}
string Adress::getCity() {
	return this->city;
}
string Adress::getStreet() {
	return this->street;
}
int Adress::getFlatNumber() {
	return this->flatNumber;
}