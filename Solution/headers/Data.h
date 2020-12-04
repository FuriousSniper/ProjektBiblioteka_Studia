#ifndef DATA_H
#define DATA_H
#include <string>
using namespace std;
class Data {

public:
	int rok;
	string miesiac;
	int numerMieszkania;
	int dzien;
	string dzienTygodnia;
	int godzina;
	int minuta;

	void printData();
};

#endif
