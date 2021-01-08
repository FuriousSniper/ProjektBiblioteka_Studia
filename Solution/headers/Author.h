#ifndef AUTOR_H
#define AUTOR_H
#include "Person.h"
#include "Date.h"
#include "Book.h"
#include <string>

class Book;
using namespace std;

class Author : public Person {

private:
	Book** books;

public:

	Author(string firstName, string lastName, int day, int month, int year);
	Author(string firstName, string lastName, int day, int month, int year, Book* book);
	Author(string firstName, string lastName, int day, int month, int year, Book** books);

	int addBook(Book* book);
	int addBooks(Book** books);
};

#endif

//w bazie danych AUTOR
/*
	ID INT PRIMARY        KEY      NOT NULL,"	
	imie				   TEXT				,"	//imie autora
	nazwisko			   TEXT				,"	//nazwisko autora
	dataUrodzenia		   DATE				,"	//data urodzenia autora
	ksiazki				   TEXT					//tytuly ksiazek ktore autor napisal. wpisywac z delimiterem "||"
*/