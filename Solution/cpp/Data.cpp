#include "..\headers\Data.h"

void Data::printData() {
	// TODO - implement Data::printData
	throw "Not yet implemented";
}
int Data::setDzien(int dzien) {
	this->dzien = dzien;
	return this->dzien;
}
int Data::getDzien() {
	return this->dzien;
}
int Data::setMiesiac(int m) {
	this->miesiac = m;
	return this->miesiac;
}
int Data::getMiesiac() {
	return this->miesiac;
}
int Data::setRok(int r) {
	this->rok = r;
	return this->rok;
}
int Data::getRok() {
	return this->rok;
}
Data::Data():dzien(0),miesiac(0),rok(0),godzina(0),minuta(0) {

}
Data::Data(int dzien, int miesiac, int rok) : dzien(dzien), miesiac(miesiac), rok(rok), godzina(0), minuta(0) {

}