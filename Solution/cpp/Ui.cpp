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
bool Ui::addBook() {
	system("CLS");
	cout << "Dodawanie ksiazki" << endl;

	string tytul="";
	string autorzy="";
	string tagi = "";
	string kategoria="";
	string egzemplarze="";
	int d, m, r;

	cout << "Podaj tytul\nTytul: ";
	//uzywam getline, zeby pozwolic na spizywanie tytulow ze spacjami.
	getline(cin, tytul);
	cout<< "Podaj autorow. Jesli wielu, wpisywac ze znakami specjalnymi \" || \" pomiedzy. Przyklad: \"Sasha Kostylev || Niko Kovac\" \nAutorzy: ";
	getline(cin, autorzy);
	cout << "Podaj tagi. Jesli kilka, wpisywac ze znakami specjalnymi \" || \" pomiedzy.\nTagi: ";
	getline(cin, tagi);
	cout << "Podaj kategorie\nKategoria: ";
	getline(cin, kategoria);
	cout << "Podaj numery ISBN egzemplarzy. Jesli kilka, wpisywac ze znakami specjalnymi \" || \" pomiedzy. Przyklad: 978-83-246-3342-5||978-83-61040-85-9\nNumery: ";
	getline(cin, egzemplarze);
	cout << "Podaj date wydania (dd mm rrrr): ";
	cin >> d >> m >> r;
	if (tytul != "" && kategoria != "") {
		//dodawanie nowej ksiazki do tabeli
		sqlite3* db;
		sqlite3_stmt* stmt;
		char* error;
		sqlite3_open("main_db.db", &db);
		if (db == NULL)
		{
			printf("Blad przy otwieraniu bazy danych\n");
			return 1;
		}

		string sql2;
		sql2 = "INSERT INTO "
			"KSIAZKA (tytul,autorzy,tagi,kategoria,egzemplarze,dataPremiery) "
			"VALUES ('" +
			tytul + "','" +
			autorzy + "','" +
			tagi + "','" +
			kategoria + "','" +
			egzemplarze + "','" +
			to_string(d) + "-" +
			to_string(m) + "-" +
			to_string(r) +
			"'	);";
		sqlite3_exec(db, sql2.c_str(), NULL, NULL, &error);
		if (error != SQLITE_OK) {
			cout << "blad: " << error << endl;
			system("pause");
		}
	}
	else {
		cout << "Pola \'tytul\' i \'kategoria\' nie moga byc puste!" << endl;
	}
}

int Ui::getBooks() {
	system("CLS");
	cout << "Przegladanie ksiazek\n" << endl;
		//wyswietlanie ksiazek w zwyklym formacie
		sqlite3* db;
		sqlite3_stmt* stmt;
		const char* sql2;
		sql2 = "SELECT tytul, autorzy from KSIAZKA;";
		char* error;
		sqlite3_open("main_db.db", &db);
		if (db == NULL)
		{
			printf("Blad przy otwieraniu bazy danych\n");
			return 1;
		}
		for (;;) {
			//wypisywanie wszystkich ksiazek
			sqlite3_prepare_v2(db, sql2, -1, &stmt, NULL);
			bool done = false;
			string opt;
			int row = 0;
			while (!done) {
				switch (sqlite3_step(stmt)) {
				case SQLITE_ROW:
					for (int i = 0; i < sqlite3_column_count(stmt); i++) {
						cout << sqlite3_column_name(stmt, i) << ": ";
						if (sqlite3_column_text(stmt, i) != NULL)
							cout << sqlite3_column_text(stmt, i) << endl;
					}
					cout << endl;

					row++;
					break;

				case SQLITE_DONE:
					done = true;
					break;

				default:
					fprintf(stderr, "Failed.\n");
					return 1;
				}
			}
			sqlite3_finalize(stmt);
			cout << "Wpisz tytul ksiazki, aby ja wypozyczyc. \nWpisz \'1\', aby dowiedziec sie, ile ksiazek jest wypozyczonych na Twoim koncie.\nWpisz \'2\', aby posortowac liste wzgledem tytulow.\nWpisz \'3\', aby posortowac liste wzgledem autorow\nWpisz \'4\', aby wyjsc z menu\n";
			cout << "Wybor: ";
			getline(cin, opt);
			if (opt == "1") {
				//pokazuje ilosc wypozyczonych ksiazek przez czytelnika
				system("CLS");
				cout << "Ilosc wypozyczonych ksiazek na Twoim koncie to " << endl;
				//TODO=========================================
			}
			if (opt == "2") {
				//sortuje ksiazki wzgledem tytulow
				system("CLS");
				cout << "Sortowanie wzgledem tytulow " << endl;
				sql2 = "SELECT tytul, autorzy from KSIAZKA ORDER BY tytul ASC;";
			}
			if (opt == "3") {
				//sortuje ksiazki wzgledem autorow
				system("CLS");
				cout << "Sortowanie wzgledem autorow " << endl;
				sql2 = "SELECT tytul, autorzy from KSIAZKA ORDER BY autorzy ASC;";
			}
			if (opt == "4") {
				//wyjscie z programu
				return 1;
			}
			else {
				//TODO
				cout << "Probujesz wypozyczyc ksiazke o tytule: " << opt << endl;
					//if(Czytelnik.getIloscWypozyczonych) ==========================================
				string sql = "SELECT * FROM KSIAZKA WHERE tytul='" + opt + "';";
				sqlite3_stmt* stmt2;
				done = false;
				sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt2, NULL);
				//kontrolne wypisywanie, tutaj cos sie robi...
				while (!done) {
					cout << "wypisywanie" << endl;
					switch (sqlite3_step(stmt2)) {
					case SQLITE_ROW:
						for (int i = 0; i < sqlite3_column_count(stmt2); i++) {
							cout << sqlite3_column_name(stmt2, i) << ": ";
							if (sqlite3_column_text(stmt2, i) != NULL)
								cout << sqlite3_column_text(stmt2, i) << endl;
						}
						cout << endl;

						row++;
						break;

					case SQLITE_DONE:
						done = true;
						break;

					default:
						fprintf(stderr, "Failed.\n");
						return 1;
					}
				}
				sqlite3_finalize(stmt2);
				//wypozycza ksiazke o wskazanym tytule (jesli takiej nie ma, to sygnalizuje blad
			}
		}
		sqlite3_finalize(stmt);
		sqlite3_close(db);
}