#include "..\headers\Egzemplarz.h"
#include "..\headers\RejestrSpoznien.h"
#include "..\headers\Czytelnik.h"
#include "..\headers\Data.h"
using namespace std;

int BookCopy::getId() {
	return this -> id;
}
void BookCopy::setId(int id) {
	this -> id = id;
}
int BookCopy::getAmountOfPages() {
	return this-> amountOfPages;
}
string BookCopy::getIsbnNumber() {
	return this-> isbnNumber;
}
string BookCopy::getPublisher() {
	return this-> publisher;
}
BookCopy::BookCopy(int amountOfPages, string isbnNumber, string publisher) : amountOfPages(amountOfPages), isbnNumber(isbnNumber), publisher(publisher) {
}
BookCopy::BookCopy() : amountOfPages(0), isbnNumber("brak"), publisher("brak") {} 
