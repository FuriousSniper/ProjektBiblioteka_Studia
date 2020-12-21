#include "..\headers\Egzemplarz.h"
#include "..\headers\RejestrSpoznien.h"
#include "..\headers\Czytelnik.h"
#include "..\headers\Data.h"
using namespace std;
Czytelnik* Egzemplarz::getOsobaWyp() {
	//TODO
	return osobaWyp;
}
int Egzemplarz::setOsobaWyp(Czytelnik* osobaWyp) {
	//TODO
	throw "not implemented";
}
Data Egzemplarz::getDataWyp() {
	//TODO
	throw "not implemented";
}
void Egzemplarz::setDataWyp(Data dataWyp) {
	//TODO
}
Data Egzemplarz::getDataOdd() {
	//TODO
	return dataOdd;
}
void Egzemplarz::setDataOdd(Data dataOdd) {
	//TODO
	
}
int Egzemplarz::getId() {
	//TODO
	return id;
}
void Egzemplarz::setId(int id) {
	//TODO
}
bool Egzemplarz::getPrzedluzony() {
	//TODO
	return przedluzony;
}
void Egzemplarz::setPrzedluzony(bool przedluzony) {
	//TODO
}
int Egzemplarz::getPrzetrzymany() {
	//TODO
	return przetrzymany;
}
void Egzemplarz::setPrzetrzymany(int p) {
	//TODO
}
Data Egzemplarz::getDataZakupu() {
	//TODO
	return dataZakupu;
}
int Egzemplarz::getIloscStron() {
	//TODO
	return iloscStron;
}
string Egzemplarz::getNumerISBN() {
	//TODO
	return numerISBN;
}
string Egzemplarz::getWydawnictwo() {
	//TODO
	return wydawnictwo;
}
Egzemplarz::Egzemplarz(int iloscStron, string nrISBN, string wydawnictwo, Data dataZakupu):iloscStron(iloscStron), numerISBN(nrISBN),wydawnictwo(wydawnictwo),dataZakupu(dataZakupu){
	//TODO
}
Egzemplarz::Egzemplarz(int iloscStron, string nrISBN, string wydawnictwo) : iloscStron(iloscStron), numerISBN(nrISBN), wydawnictwo(wydawnictwo) {
	//TODO
}
