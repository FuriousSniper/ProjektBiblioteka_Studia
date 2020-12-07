#include "..\headers\Ksiazka.h"
#include "..\headers\Data.h"
#include "..\headers\Autor.h"
using namespace std;

string Ksiazka::getTytul() {
	return tytul;
}
Autor* Ksiazka::getAutorzy() {
	return autorzy;
}
string* Ksiazka::getTagi() {
	return tagi;
}
void Ksiazka::setTagi(string* tagi) {
	//TODO
}
Data Ksiazka::getDataPremiery() {
	return dataPremiery;
}
void Ksiazka::dodajEgzemplarz(Egzemplarz* egzemplarz) {
	//TODO

}
Egzemplarz** Ksiazka::getEgzemplarze() {
	return egzemplarze;
}
int Ksiazka::usunEgzemplarz(Egzemplarz* e) {
	//TODO
	return 1;
}
int Ksiazka::getId() {
	return id;
}
string Ksiazka::getKategoria() {
	return kategoria;
}
int Ksiazka::getIloscEgzemplarzy() {
	return iloscEgzemplarzy;
}
Ksiazka::Ksiazka(string tytul, Autor* autorzy, int id, Data dataPremiery) {
	//TODO
}
Ksiazka::Ksiazka(string tytul, Autor* autorzy, int id, Data dataPremiery, Egzemplarz* egzemplarz) {
	//TODO
}
Ksiazka::Ksiazka(string tytul, Autor* autorzy, int id, Data dataPremiery, Egzemplarz** egzemplarze) {
	//TODO
}
