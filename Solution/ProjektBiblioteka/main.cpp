#include <iostream>
#include "..\headers\Osoba.h";
#include "..\headers\Ui.h";
#include "..\headers\Autor.h";
using namespace std;

int main() {
	//utworzenie instancji obiektu Ui
	Ui ui = Ui();
	cout << "Witamy w programie Biblioteka" << endl;
	int start = ui.signInUpMenu();
	int login;
	//cout << n << endl;
	if (start == 1)
		login = ui.chooseUserType();
	return 0;
}