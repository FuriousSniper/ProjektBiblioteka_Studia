#include "..\headers\Book.h"
#include "..\headers\Date.h"
#include "..\headers\Author.h"
using namespace std;

string Book::getTitle() {
	return this -> title;
}
const Author* Book::getAuthors(){
	return this -> authors;
}
Date Book::getReleaseDate() {
	return this -> releaseDate;
}
int Book::getId() {
	return this -> id;
}
string Book::getCategory() {
	return this -> category;
}
int Book::getAmountOfCopies() {
	return this->amountOfCopies;
}
Book::Book(string title, Author* authors, int id, Date releaseDate) : title(title), authors(authors), id(id), releaseDate(releaseDate) {}

