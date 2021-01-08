#ifndef BIBLIOTEKARZ_H
#define BIBLIOTEKARZ_H
#include "Person.h"
#include <string>
#include "Adress.h"

using namespace std;
class Librarian : public Person {

private:

	const int ID;
	string password;

public:

	Librarian(string firstName, string lastName, int ID);
	Librarian(string firstName, string lastName, string emailAdress, string phoneNumber, int day, int month, int year, Adress adress, string password, int ID);

	void setPassword(string password);
	string getPassword();
	int getID();
	void printLibrarianInfo();
};

#endif
