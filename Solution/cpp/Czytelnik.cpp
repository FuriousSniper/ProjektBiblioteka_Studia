#include "..\headers\Czytelnik.h"
#include <string>
#include <iostream>
#include "..\headers\Data.h"
#include "..\headers\Adres.h"

using namespace std;
const int Reader::getID() {
	return ID;
}

string* Reader::getPrefferedCategories() {
	return preferredCategories;
}
int Reader::setPrefferedCategories(string* categories) {
	this->preferredCategories = categories;
}
void Reader::printReaderInfo() {
	printPerson();
	cout << "Dane charakterystyczne dla czytelnika: " << endl;
	cout << "\tID: " << this->ID << endl;
}
void Reader::setPassword(string newPassword) {
	this->password = newPassword;
}
string Reader::getPassword() {
	return this->password;
}

Reader::Reader(string firstName, string lastName, int id) : Person(firstName, lastName),ID(id) {}
Reader::Reader(string firstName, string lastName, int day, int month, int year, string* preferredCategories, int ID): Person(firstName,lastName, day, month,year),
preferredCategories(preferredCategories), ID(ID) {}  

Reader::Reader(string firstName, string lastName, string emailAdress, string phoneNumber, int day, int month, int year, Adress adress, string password, int ID): ID(ID), Person(firstName,lastName, emailAdress, phoneNumber, day,month,year, adress), password(password) {}
Reader::Reader() : Person(), ID(0), preferredCategories(NULL) {}
