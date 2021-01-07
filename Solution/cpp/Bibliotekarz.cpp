#include "..\headers\Bibliotekarz.h"
#include "..\headers\Osoba.h"
#include <string>
#include <iostream>
using namespace std;

void Librarian :: setPassword(string password) {
	this->password = password;
}
string Librarian::getPassword() {
	return this->password;
}

int Librarian::getID() {
	return this->ID;
}

void Librarian::printLibrarianInfo() {
	printPerson();
	cout << "\nDane charakterystyczne dla bibliotekarza: " << endl;
	cout << "\tID: " << this->ID << endl;
}

Librarian::Librarian(string firstName, string lastName, int ID) : Person(firstName, lastName), ID(ID) {}

Librarian::Librarian(string firstName, string lastName, string emailAdress, string phoneNumber, int day, int month, int year, Adress adress, string password, int ID) : Person(firstName, lastName, emailAdress, phoneNumber, day,month,year,adress), ID(ID), password(password) {}

