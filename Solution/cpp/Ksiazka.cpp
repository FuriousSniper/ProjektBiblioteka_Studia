#include "..\headers\Ksiazka.h"
#include "..\headers\Data.h"
#include "..\headers\Autor.h"
using namespace std;

string Book::getTytul() {
	return tytul;
}
Author* Book::getAutorzy() {
	return autorzy;
}
string* Book::getTagi() {
	return tagi;
}
void Book::setTagi(string* tagi) {
	//TODO
}
Date Book::getDataPremiery() {
	return dataPremiery;
}
void Book::dodajEgzemplarz(BookCopy* egzemplarz) {
	//TODO

}
BookCopy** Book::getEgzemplarze() {
	return egzemplarze;
}
int Book::usunEgzemplarz(BookCopy* e) {
	//TODO
	return 1;
}
int Book::getId() {
	return id;
}
string Book::getKategoria() {
	return kategoria;
}
int Book::getIloscEgzemplarzy() {
	return iloscEgzemplarzy;
}
Book::Book(string tytul, Author* autorzy, int id, Date dataPremiery) {
	//TODO
}
Book::Book(string tytul, Author* autorzy, int id, Date dataPremiery, BookCopy* egzemplarz) {
	//TODO
}
Book::Book(string tytul, Author* autorzy, int id, Date dataPremiery, BookCopy** egzemplarze) {
	//TODO
}
