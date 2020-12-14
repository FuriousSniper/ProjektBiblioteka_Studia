#include "..\headers\Ui.h"
#include "..\headers\Osoba.h"
#include "..\headers\Data.h"
#include "..\headers\Autor.h"
#include "..\headers\Czytelnik.h"
#include "..\headers\AdresZamieszkania.h"
#include <string>
#include <exception>
using namespace std;

Osoba Ui::createOsoba() {
	Osoba o = Osoba("", "");
	string i;
	string n;
	int d;
	int m;
	int r;
	//czyszczenie ekranu
	system("CLS");
	//podawanie danych do obiktu Osoba
	cout << "Tworzenie nowej Osoby" << endl;
	cout << "Podaj imie: ";
	cin >> i;
	cout << endl;
	o.setImie(i);
	cout << "Podaj nazwisko: ";
	cin >> n;
	cout << endl;
	o.setNazwisko(n);
	cout << "Podaj date urodzenia (dd mm rrrr): ";
	cin >> d >> m >> r;
	o.setDataUrodzenia(d, m, r);
	cout << "Pomyslnie utworzono: Osoba" << endl;
	//zwracanie nowo-utworzonego obiektu
	return o;
}
Autor Ui::createAutor() {
	cout << "Tworzenie nowego Autora" << endl;
	Osoba o = Ui::createOsoba();
	//Autor dziedziczy po Osobie, wiec tworzymy obiekt osoba i przepisujemy wartosci. da sie to zrobic prosciej przypisujac obiekt zamiast poszczegolnych skladowych, ale na razie to nie jest istotne
	Autor a = Autor(o.getImie(), o.getNazwisko(), o.getDataUrodzenia().getDzien(), o.getDataUrodzenia().getMiesiac(), o.getDataUrodzenia().getRok());
	cout << "Pomyslnie utworzono: Autor" << endl;
	return a;
}
Czytelnik Ui::createCzytelnik() {
	cout << "Tworzenie nowego Czytelnika" << endl;
	Osoba o = Ui::createOsoba();
	Czytelnik c = Czytelnik(o.getImie(), o.getNazwisko(), o.getDataUrodzenia().getDzien(), o.getDataUrodzenia().getMiesiac(), o.getDataUrodzenia().getRok());
	return c;
}
AdresZamieszkania Ui::createAdres() {
	cout << "Tworzenie adresu" << endl;
	system("CLS");
	string miasto;
	cout << "Podaj miasto: ";
	cin >> miasto;
	string kod;
	cout << "Podaj kod pocztowy: ";
	cin >> kod;
	string ulica;
	cout << "Podaj ulice Twojego adresu zamieszkania: ";
	cin >> ulica;
	AdresZamieszkania a = AdresZamieszkania(miasto,kod,ulica);
	cout<< "Pomyslnie utworzono: Adres" << endl;
	return a;
}
int Ui::signInUpMenu() {
	int n=0;
	system("CLS");
	while (n != 1 && n != 2&&n!=3) {
		
		cout << "Wybierz '1', aby sie zalogowac." << endl;
		cout << "Wybierz '2', aby sie zarejestrowac." << endl;
		cout << "Wybierz '3', aby wyjsc z programu." << endl;
		//dodac error handling
		cout << "Wybor: ";
		cin >> n;
		if (n == 3) {
			cout<<"Zakonczono prace programu"<<endl;
			return 0;
		}
		if (n != 1 && n != 2&&n!=3)
			cout << "Wybierz poprawna wartosc" << endl;
	}
	return n;
}
int Ui::chooseUserType() {
	int n = 0;
	system("CLS");
	//petla, ktora sprawia, ze w przypadku zlej odpowiedzi uzytkownik moze wprowadzic inna
	while (n != 1 && n != 2 && n != 3) {
		cout << "Wybierz '1', aby zalogowac sie na konto Czytelnika." << endl;
		cout << "Wybierz '2', aby zalogowac sie na konto Bibliotekarza." << endl;
		cout << "Wybierz '3', aby wyjsc z programu." << endl;
		//dodac error handling
		cout << "Wybor: ";
		cin >> n;
		if (n == 3) {
			cout << "Zakonczono prace programu" << endl;
			return 0;
		}
		if (n != 1 && n != 2 && n != 3)
			cout << "Wybierz poprawna wartosc" << endl;
	}
	return n;
}
Ui::Ui() {}
