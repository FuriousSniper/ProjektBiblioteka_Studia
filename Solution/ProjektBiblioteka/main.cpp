#include <iostream>
#include "..\headers\Osoba.h";
#include "..\headers\Ui.h";
#include "..\headers\Autor.h";
#include "..\headers\AdresZamieszkania.h";
using namespace std;

int main() {

	/*
	//utworzenie instancji obiektu Ui
	Ui ui = Ui();
	cout << "Witamy w programie Biblioteka" << endl;
	int start = ui.signInUpMenu();
	int login;
	//cout << n << endl;
	if (start == 1)
		login = ui.chooseUserType();
	*/

	AdresZamieszkania* adres = new AdresZamieszkania("Janow", "56-567", "Fiolkowa", 4);
	adres->printAdresZamieszkania();

	Data* data = new Data(12,12,2000, 14, 57);
	data->printData();

	Autor* autor = new Autor("Jan", "Kowalski", 20, 4, 1976);
	autor->printOsoba();

	delete adres;
	delete data;
	delete autor;

	system("pause");

	return 0;
}