#ifndef OSOBA_H
#define OSOBA_H
#include <string>
#include "Date.h"
#include "Adress.h"

using namespace std;

class Person {

private:

	const string firstName;
	const string lastName;
	int age;
	const Date birthDate;
	string emailAdress;
	string phoneNumber;
	Adress adress;

public:

	string getLastName();
	string getFirstName();
	string getEmailAdress();
	string getPhoneNumber();
	Adress getAdress();
	void setAdress(Adress adress);
	Date getBirthDate();
	int getAge();
	int setAge(int age);
	void setPhoneNumber(string phoneNumber);
	void setEmailAdress(string emailAdress);

	Person(string firstName, string lastName, int day, int month, int year);
	Person(string firstName, string lastName, string emailAdress, string phoneNumber, int day, int month, int year, Adress adress);
	Person(string firstName, string surname);
	Person();
	void printPersonInfo();
};

#endif
