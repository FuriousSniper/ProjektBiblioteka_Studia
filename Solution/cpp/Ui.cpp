#include "..\headers\Ui.h"
#include "..\headers\Osoba.h"
#include "..\headers\Data.h"
#include "..\headers\Autor.h"
#include "..\headers\Czytelnik.h"
#include "..\headers\AdresZamieszkania.h"
#include "../ProjektBiblioteka/Libraries/sqlite3/sqlite3.h";
#include <string>
#include <exception>
using namespace std;

Osoba Ui::createOsoba() {
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
	cout << "Podaj nazwisko: ";
	cin >> n;
	cout << endl;
	cout << "Podaj date urodzenia (dd mm rrrr): ";
	cin >> d >> m >> r;
	Osoba o = Osoba(i, n, d, m, r);
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
	while (true) {
		cout << "Podaj haslo do swojego konta! " << endl;
		string pass;
		cin >> pass;
		cin.clear();
		cin.ignore();
		system("cls");
		cout << "Potwierdz haslo do swojego konta!" << endl;
		string pass2;
		cin >> pass2;
		if (pass == pass2) {
			system("cls");
			c.setHaslo(pass);
			return c;
		}
		else {
			system("cls");
			cout << "Hasla nie sa zgodne!\n";
			cin.clear();
			cin.ignore();
		}
	}
}
AdresZamieszkania Ui::createAdres() {
	cout << "Tworzenie adresu" << endl;
	system("CLS");
	string miasto;
	cout << "Podaj miasto: ";
	cin.ignore();
	getline(cin, miasto);
	string kod;
	cout << "Podaj kod pocztowy: ";
	cin >> kod;
	string ulica;
	cout << "Podaj ulice i nr domu Twojego adresu zamieszkania: ";
	cin.ignore();
	getline(cin, ulica);
	cout << "Podaj numer Twojego mieszkania (opcjonalne): ";
	int numerMieszkania;
	cin >> numerMieszkania;
	AdresZamieszkania a = AdresZamieszkania(miasto,kod,ulica, numerMieszkania);
	cout<< "Pomyslnie utworzono: Adres" << endl;
	return a;
}
int Ui::signInUpMenu() {
	int n=0;
	while (true) {
		system("CLS");
		cout << "System obslugi Biblioteki (v. alfa 0.1)\n";
		cout << "Wybierz '1', aby sie zalogowac." << endl;
		cout << "Wybierz '2', aby sie zarejestrowac." << endl;
		cout << "Wybierz '9', aby wyjsc z programu." << endl;
		cout << "Wybor: ";
		cin >> n;
		if (n == 9) {
			cout<<"Zakonczono prace programu"<<endl;
			return 0;
		}
		else if (n == 1 || n == 2) {
			break;
		}
		else {
			cin.clear();
			cin.ignore(1024, '\n');
		}
	}
	return n;
}
int Ui::chooseUserType() {
	int n = 0;
	while (true) {
		system("CLS");
		cout << "System obslugi Biblioteki (v. alfa 0.1)\n";
		cout << "Wybierz '1', aby zalogowac sie na konto Czytelnika." << endl;
		cout << "Wybierz '2', aby zalogowac sie na konto Bibliotekarza." << endl;
		cout << "Wybierz '3', aby powrocic do menu glownego." << endl;
		cout << "Wybierz '9', aby wyjsc z programu." << endl;
		cout << "Wybor: ";
		cin >> n;
		if (n == 9) {
			cout << "Zakonczono prace programu" << endl;
			return 0;
		}
		else if (n == 1 || n == 2 || n == 3) {
			break;
		}
		else {
			cin.clear();
			cin.ignore(1024, '\n');
		}
	}
	return n;
}
Ui::Ui() {}
int Ui::chooseUserTypeRegistration() {
	int n = 0;
	while (true) {
		system("CLS");
		cout << "System obslugi Biblioteki (v. alfa 0.1)\n";
		cout << "Wybierz '1', aby zarejestrowac konto Czytelnika." << endl;
		cout << "Wybierz '2', aby zarejestrowac konto Bibliotekarza." << endl;
		cout << "Wybierz '3', aby powrocic do menu glownego." << endl;
		cout << "Wybierz '9', aby wyjsc z programu." << endl;
		cout << "Uwaga! W przypadku rejestracji Bibliotekarza wymagana jest autoryzacja dyrekcji.\n";
		cout << "Wybor: ";
		cin >> n;
		if (n == 9) {
			cout << "Zakonczono prace programu" << endl;
			return 0;
		}
		else if (n == 1 || n == 2 || n == 3 ) {
			break;
		}
		else {
			cin.clear();
			cin.ignore(1024, '\n');
		}
	}
	return n;
}
bool Ui::confirmVerification() {
	cout << "\nCzy potwierdzasz wyswietlone dane? (T/N) ";
	while (true) {
		char zgoda;
		cin >> zgoda;
		if (zgoda == 't' || zgoda == 'T') {
			return true;
		}
		else if (zgoda == 'n' || zgoda == 'N') {
			return false;
		}
		else {
			cin.clear();
			cin.ignore(1024, '\n');
		}
	}
}