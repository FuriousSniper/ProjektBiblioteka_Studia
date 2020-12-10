#include <iostream>
#include "..\headers\Osoba.h";
#include "..\headers\Ui.h";
#include "..\headers\Autor.h";
using namespace std;

int main() {
	//utworzenie instancji obiektu Ui
	Ui ui = Ui();
	//Osoba o = ui.createOsoba();
	//cout << o.getImie();
	//Czytelnik c = ui.createCzytelnik();
	//cout << c.getImie();
	AdresZamieszkania a = ui.createAdres();
	return 0;
}