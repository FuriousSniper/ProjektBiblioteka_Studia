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

	delete adres;
	delete data;

	system("pause");

	return 0;
}