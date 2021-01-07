#include "..\headers\Autor.h"

int Author::addBook(Book* ksiazka) {
	// TODO - implement Autor::dodajKsiazke
	throw "Not yet implemented";
}

int Author::addBooks(Book** ksiazki) {
	// TODO - implement Autor::dodajKsiazki
	throw "Not yet implemented";
}

Author::Author(string firstName, string lastName, int day, int month, int year):Person(firstName,lastName,day,month,year){
}

Author::Author(string firstName, string LastName, int day, int month, int year, Book* book): Person(firstName, LastName, day, month, year){
	addBook(book);
}

Author::Author(string firstName, string lastName, int day, int month, int year, Book** books) : Person(firstName, lastName, day, month, year),books(books) {
	// TODO - implement Autor::Autor
	throw "Not yet implemented";
}
