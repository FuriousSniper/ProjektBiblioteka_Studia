#ifndef DATA_H
#define DATA_H
#include <string>
using namespace std;
class Data {

public:
	int rok;
	int miesiac;
	int dzien;
	int godzina;
	int minuta;

	void printData();
	int setDzien(int dzien);
	int getDzien();
	int setMiesiac(int m);
	int getMiesiac();
	int setRok(int r);
	int getRok();
	Data();
	Data(int dzien, int miesiac, int rok);
	Data(int dzien, int miesiac, int rok, int godzina, int minuta);
};

#endif
