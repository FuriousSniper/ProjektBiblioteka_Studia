#ifndef ADRES_H
#define ADRES_H
#include <string>
using namespace std;

class Adress {

public:

	string city;
	string zipCode;
	string street;
	int flatNumber;

	Adress(string city, string zipCode, string street, int flatNumber);
	Adress();

	string getCity();
	string getZipCode();
	string getStreet();
	int getFlatNumber();
	void printAdress() const;
};

#endif
