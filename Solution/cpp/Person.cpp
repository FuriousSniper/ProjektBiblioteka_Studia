#include "..\headers\Person.h"
#include "..\headers\Adress.h"
#include <iostream>
#include <ctime>

string Person::getLastName() {
	return this->lastName;
}

string Person::getFirstName() {
	return this->firstName;
}

int Person::getAge() {
	return this->age;
}

Adress Person::getAdress() {
	return this->adress;
}

string Person :: getEmailAdress() {
	return this->emailAdress;
}

string Person :: getPhoneNumber() {
	return this->phoneNumber;
}

Date Person::getBirthDate() {
	return this->birthDate;
}

int Person::setAge(int age) {
	this->age = age;
	return this->age;
}

void Person::setPhoneNumber(string phoneNumber) {
	this->phoneNumber = phoneNumber;
}

void Person::setEmailAdress(string emailAdress) {
	this->emailAdress = emailAdress;
}
void Person::printPersonInfo() {
	
	cout << "Dane osobowe:" << endl;
	cout << "\timie: " << this->firstName << endl << "\tnazwisko: " << this->lastName << endl << "\tdata urodzenia: ";
	birthDate.printDate();
	cout << "\twiek: ";

	if (age == 0) {
		cout << "nie podano" << endl;
	}
	else {
		cout << this->age << endl;
	}

	cout << "\te-mail: " << this->emailAdress << endl;
	cout << "\ttelefon: " << this->phoneNumber << endl;
	cout << "\tadres zamieszkania: ";
	adress.printAdress();
}
void Person :: setAdress(Adress adress) {
	this->adress = adress;
}
Person::Person(string firstName, string lastName, int day, int month, int year):firstName(firstName),lastName(lastName), birthDate(Date(day,month,year)), 
adress(Adress()), emailAdress("nie podano"), phoneNumber("nie podano"){
	time_t t = time(NULL);
	tm* buf = new tm;
	localtime_s(buf,&t);
	this->age = buf->tm_year + 1900 - year;
}

Person::Person(string firstName, string lastName) : firstName(firstName), lastName(lastName),birthDate(Date()), age(0), emailAdress("nie podano"),phoneNumber("nie podano"),
adress(Adress()){
}

Person::Person() : firstName("nie podano"), lastName("nie podano"), emailAdress("nie podano"), phoneNumber("nie podano"), birthDate(Date()), age(0),
adress(Adress()){}

Person::Person(string firstName, string lastName, string emailAdress, string phoneNumber, int day, int month, int year, Adress adress) : firstName(firstName), lastName(lastName), emailAdress(emailAdress), phoneNumber(phoneNumber), birthDate(Date(day,month,year)), adress(adress) {
	time_t t = time(NULL);
	tm* buf = new tm;
	localtime_s(buf,&t);
	this->age = buf->tm_year + 1900 - year;
}


