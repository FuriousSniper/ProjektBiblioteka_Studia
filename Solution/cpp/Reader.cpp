#include "..\headers\Reader.h"
#include <string>
#include <iostream>
#include "..\headers\Date.h"
#include "..\headers\Adress.h"

using namespace std;
const int Reader::getID() {
	return ID;
}

void Reader::printReaderInfo() {
	printPersonInfo();
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

Reader::Reader(string firstName, string lastName, string emailAdress, string phoneNumber, int day, int month, int year, Adress adress, string password, int ID): ID(ID), Person(firstName,lastName, emailAdress, phoneNumber, day,month,year, adress), password(password) {}
Reader::Reader() : Person(), ID(0){}
