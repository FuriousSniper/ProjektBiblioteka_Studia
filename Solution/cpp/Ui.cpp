#include "..\headers\Ui.h"
#include "..\headers\Osoba.h"
#include "..\headers\Data.h"
#include "..\headers\Autor.h"
#include "..\headers\Czytelnik.h"
#include "..\headers\Adres.h"
#include "..\headers\Biblioteka.h"
#include "..\headers\ElementyPomocnicze.h"
#include "../ProjektBiblioteka/Libraries/sqlite3/sqlite3.h"
#include <string>
#include <exception>
#include <iostream>


using namespace std;

Osoba Ui::createOsoba() {

	string imie;
	string nazwisko;
	int dzien;
	int miesiac;
	int rok;
	string email;
	string telefon;
	Adres adres;

	//czyszczenie ekranu
	system("CLS");
	//podawanie danych do obiktu Osoba
	cout << "Tworzenie nowej Osoby" << endl;
	cout << "Podaj imie: ";
	cin >> imie;
	cout << endl;
	cout << "Podaj nazwisko: ";
	cin >> nazwisko;
	cout << endl;
	cout << "Podaj date urodzenia (dd mm rrrr): ";
	cin >> dzien >> miesiac >> rok;
	
	while (true) {
		system("cls");
		cout << "Podaj swoj email: " << endl;
		cin >> email;
		cin.clear();
		cin.ignore();
		cout << "Powtorz swoj email: " << endl;
		string email2;
		cin >> email2;
		cin.clear();
		cin.ignore();
		if (email == email2) {
			cout << "Podaj swoj nr telefonu: " << endl;
			cin >> telefon;
			cin.clear();
			cin.ignore();
			break;
		}
		else {
			system("cls");
			cout << "Adresy email sie roznia! \n";
			cin.clear();
			cin.ignore();
		}
	}

	adres = createAdres();
	Osoba o = Osoba(imie, nazwisko, email, telefon, dzien, miesiac, rok, adres);
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
Czytelnik Ui::createCzytelnik(sqlite3* database) {

	sqlite3_stmt* stmt;								
	cout << "Tworzenie nowego Czytelnika" << endl;
		Osoba o = Ui::createOsoba();
		int rc = sqlite3_prepare_v2(database, "select MAX(ID) from CZYTELNIK", -1, &stmt, NULL);
		int temp = -1;
		if (sqlite3_step(stmt) == SQLITE_ROW) {		//NOTOWANIE ID NA WYPADEK ZMIANY PLANOW
			temp = sqlite3_column_int(stmt, 0);		//CO DO SPOSOBU LOGOWANIA LUB TYM PODOBNYCH
		}
	++temp;

	Czytelnik c = Czytelnik(o.getImie(), o.getNazwisko(), o.getEmail(), o.getTelefon(), o.getDataUrodzenia().getDzien(), o.getDataUrodzenia().getMiesiac(), o.getDataUrodzenia().getRok(), o.getAdresZamieszkania(), temp);

	
	while (true) {
		system("cls");
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

Bibliotekarz Ui::createBibliotekarz(sqlite3* database) {

	// TODO: polaczyc ta metode z metoda createCzytelnik. Roznia sie drobnymi szczegolami.

	sqlite3_stmt* stmt;
	cout << "Tworzenie nowego Bibliotekarza" << endl;
	Osoba o = Ui::createOsoba();
	int rc = sqlite3_prepare_v2(database, "select MAX(ID) from BIBLIOTEKARZ", -1, &stmt, NULL);
	int temp = -1;
	if (sqlite3_step(stmt) == SQLITE_ROW) {		//NOTOWANIE ID NA WYPADEK ZMIANY PLANOW
		temp = sqlite3_column_int(stmt, 0);		//CO DO SPOSOBU LOGOWANIA LUB TYM PODOBNYCH
	}
	++temp;

	Bibliotekarz b = Bibliotekarz(o.getImie(), o.getNazwisko(), o.getEmail(), o.getTelefon(), o.getDataUrodzenia().getDzien(), o.getDataUrodzenia().getMiesiac(), o.getDataUrodzenia().getRok(), o.getAdresZamieszkania(), temp);


	while (true) {
		system("cls");
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
			b.setHaslo(pass);
			return b;
		}
		else {
			system("cls");
			cout << "Hasla nie sa zgodne!\n";
			cin.clear();
			cin.ignore();
		}
	}
}

bool Ui::addCzytelnik(Czytelnik new_user, sqlite3* database) {
	char* sql_error;
	string sql2;
	int temp = new_user.getID();
	sql2 = "INSERT INTO CZYTELNIK"
		"(listaZaleglosci,dataPierwszegoWypozyczenia,iloscWypozyczonychOdDolaczenia,preferowaneTematy,"
		"dataDolaczenia,miasto,kodPocztowy,ulica,imie,nazwisko,wiek,dataUrodzenia,haslo,numerMieszkania,email,telefon)"
		" VALUES ("
		"	'',"
		"	'',"
		"	0,"
		"	'',"
		"	DATE(),'" +
		new_user.getAdresZamieszkania().getMiasto() + "','" +
		new_user.getAdresZamieszkania().getKodPocztowy() + "','" +
		new_user.getAdresZamieszkania().getUlica() + "','" +
		new_user.getImie() + "','" +
		new_user.getNazwisko() + "','" +
		to_string(new_user.getWiek()) + "','" +
		to_string(new_user.getDataUrodzenia().getDzien()) + "-" +
		to_string(new_user.getDataUrodzenia().getMiesiac()) + "-" +
		to_string(new_user.getDataUrodzenia().getRok()) + "','" +
		new_user.getHaslo() + "','" +
		to_string(new_user.getAdresZamieszkania().getNumerMieszkania()) + "','"+
		new_user.getEmail()+"','"+
		new_user.getTelefon()+"'"
		"	);";
	sqlite3_exec(database, sql2.c_str(), NULL, NULL, &sql_error);
	if (sql_error != SQLITE_OK) {
		cout << "blad: " << sql_error << endl;
		return false;
	}
	return true;
}

bool Ui::addBibliotekarz(Bibliotekarz new_user, sqlite3* database) {

	// TODO polaczyc z metoda addCzytelnik. Rozni sie jedynie zapytaniem.

	char* sql_error;
	string sql2;
	int temp = new_user.getID();
	sql2 = "INSERT INTO BIBLIOTEKARZ"
		"(imie, nazwisko, wiek,"
		"dataUrodzenia, haslo, email, telefon, miasto, kodPocztowy, ulica, numerMieszkania)"
		" VALUES ('" +
		new_user.getImie() + "','" +
		new_user.getNazwisko() + "'," +
		to_string(new_user.getWiek()) + ",'" +
		to_string(new_user.getDataUrodzenia().getDzien()) + "-" +
		to_string(new_user.getDataUrodzenia().getMiesiac()) + "-" +
		to_string(new_user.getDataUrodzenia().getRok()) + "','" +
		new_user.getHaslo() + "','" +
		new_user.getEmail() + "','" +
		new_user.getTelefon() + "','" +
		new_user.getAdresZamieszkania().getMiasto() + "','" +
		new_user.getAdresZamieszkania().getKodPocztowy() + "','" +
		new_user.getAdresZamieszkania().getUlica() + "','" +
		to_string(new_user.getAdresZamieszkania().getNumerMieszkania()) + "');";

	sqlite3_exec(database, sql2.c_str(), NULL, NULL, &sql_error);
	if (sql_error != SQLITE_OK) {
		cout << "blad: " << sql_error << endl;
		return false;
	}
	return true;

}

Adres Ui::createAdres() {
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
	Adres a = Adres(miasto,kod,ulica, numerMieszkania);
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
	string dmr;

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
	cout << "Podaj date wydania (dd-mm-rrrr): ";
	getline(cin, dmr);
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
		//podzielenie autorow i wywolanie funkcji dodajacej/sprawdzajacej czy autor istnieje dla kazdego autora
		if (autorzy.find("||") != string::npos) {
			string delimit = "||";
			vector<string> autors_splitted = ElementyPomocnicze :: split_string(autorzy, delimit);
			for (int i = 0; i < autors_splitted.size(); i++) {
				//metoda sprawdzajaca czy autor istnieje i dodaje go/updatuje jego ksiazki
				addAutor3(autors_splitted[i], tytul);
			}
		}
		else
			addAutor3(autorzy, tytul);
		string sql2;
		sql2 = "INSERT INTO KSIAZKA (tytul,autorzy,tagi,kategoria,egzemplarze,dataPremiery) "
			"VALUES ('" +
			tytul + "','" +
			autorzy + "','" +
			tagi + "','" +
			kategoria + "','" +
			egzemplarze + "','" +
			dmr+
			"'	);";
		cout << "Wykonanie sql" << endl;
		if (db == NULL)
		{
			printf("Blad przy otwieraniu bazy danych\n");
			return 1;
		}
		sqlite3_exec(db, sql2.c_str(), NULL, NULL, &error);
		if (error != SQLITE_OK) {
			cout << "blad: " << error << endl;
			system("pause");
		}
		cout << "Dodano ksiazke do bazy danych" << endl;
		//splitowanie egzemplarzy na czesci
		if (egzemplarze != "") {
			vector<string> splittedString;
			string delimeter = "||";

			splittedString = ElementyPomocnicze :: split_string(egzemplarze, delimeter);
			//dla kazdego egzemplarza wywolywana jest funkcja dodajaca go do bazy danych
			for (int i = 0; i < splittedString.size(); i++) {
				cout << "Dodawanie egzemplarza ksiazki o isbn " << splittedString[i];
				addEgzemplarz2(splittedString[i], tytul);
				system("CLS");
			}
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
}
int Ui::getNumberOfLentBooks(Czytelnik c) {
	sqlite3* db;
	sqlite3_stmt* stmt;
	//Czytelnik c jest zalogowanym czytelnikiem, wiec pola, ktorych uzywamy w getterach sa w pamieci.
	string query = "SELECT ksiazka1, ksiazka2, ksiazka3 from CZYTELNIK WHERE imie='" + c.getImie() + "' AND nazwisko='" + c.getNazwisko() + "';";
	int counter = 0;
	sqlite3_open("main_db.db", &db);
	if (db == NULL)
	{
		printf("Blad przy otwieraniu bazy danych\n");
		return 1;
	}
	sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, NULL);
	sqlite3_step(stmt);
	//wynikiem jest 1 rzad, w ktorym odczytujemy wszystkie 3 kolumny, ktore pobralismy. jesli sa one nullem, to nie zwiekszamy licznika.
	int num_cols = sqlite3_column_count(stmt);
	for (int i = 0; i < num_cols; i++) {
		if (sqlite3_column_text(stmt, i) != NULL)
			counter++;
	}
	sqlite3_finalize(stmt);
	return counter;
}
int Ui::lendBook(Czytelnik c,string tytul) {
	int l = getNumberOfLentBooks(c);
	if (l < 3) {
		sqlite3* db;
		sqlite3_stmt* stmt;
		char* error;
		//Czytelnik c jest zalogowanym czytelnikiem, wiec pola, ktorych uzywamy w getterach sa w pamieci.
		string query = "SELECT ksiazka1, ksiazka2, ksiazka3 from CZYTELNIK WHERE imie='" + c.getImie() + "' AND nazwisko='" + c.getNazwisko() + "';";
		//zmienna, w ktorej zapisujemy wolna kolumne
		int counter = 1;
		sqlite3_open("main_db.db", &db);
		if (db == NULL)
		{
			printf("Blad przy otwieraniu bazy danych\n");
			return 1;
		}
		sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, NULL);
		sqlite3_step(stmt);
		//wynikiem jest 1 row, w ktorym odczytujemy wszystkie 3 kolumny, ktore pobralismy. jesli sa one nullem, to nie zwiekszamy licznika.
		int num_cols = sqlite3_column_count(stmt);
		//znajdujemy kolumne w tabeli odpowiadajaca za "pusta ksiazke". w tamtym miejscu zapisujemy ISBN wypozyczanego egzemplarza
		for (int i = 0; i < num_cols; i++) {
			if (sqlite3_column_text(stmt, i) == NULL)
				break;
			else
				counter++;
		}
		sqlite3_finalize(stmt);

		//sprawdzamy, czy jakies egzemplarze ksiazki sa dostepne
		string isbn = checkEgzemplarze(tytul);
		//jesli nie, to zwracamy bledy
		if (isbn == "false") {
			cout << "Ksiazka o tym tytule nie znajduje sie w bazie" << endl;
			return -1;
		}
		if (isbn == "NOT_AVAILABLE") {
			cout << "Wszystkie ksiazki o tym tytule zostaly wypozyczone" << endl;
			return -1;
		}

		//updatujemy row, czyli konkretniej - kolumne gdzie zapisujemy nowo wypozyczona ksiazke danego czytelnika
		query = "UPDATE CZYTELNIK SET ksiazka" + to_string(counter) + "='" + isbn + "' WHERE imie='" + c.getImie() + "' AND nazwisko='" + c.getNazwisko() + "';";
		int rc = sqlite3_exec(db, query.c_str(), NULL, NULL, &error);
		if (rc != SQLITE_OK) {
			cout << error << endl;
			sqlite3_free(error);
			return -1;
		}

		//koniecznie - updatujemy wypozyczany egzemplarz. zmieniamy date wypozyczenia oraz osobe
		query = "UPDATE EGZEMPLARZE SET osobaWyp='" + c.getImie() + " " + c.getNazwisko() + "', dataWyp=(DATETIME('now')), dataOdd=(DATETIME('now','+1 month')) WHERE numerISBN='" + isbn + "';";
		rc = sqlite3_exec(db, query.c_str(), NULL, NULL, &error);
		if (rc != SQLITE_OK) {
			cout << error << endl;
			sqlite3_free(error);
			return -1;
		}
		std::cout << "Wypozyczono" << std::endl;

		//sukces, zwracamy 1
		return 1;
	}
	else
		//zwracamy blad, bo user nie moze wypozyczyc wiecej niz 3 ksiazek
		cout << "Czytelnik wypozyczyl maksymalna ilosc ksiazek" << endl;
		return -1;
}
int Ui::addEgzemplarz() {
	system("CLS");
	cout << "Dodawanie egzemplarza ksiazki" << endl;
	sqlite3* db;
	sqlite3_stmt* stmt;
	char* error;
	sqlite3_open("main_db.db", &db);
	if (db == NULL)
	{
		printf("Blad przy otwieraniu bazy danych\n");
		return -1;
	}
	string ilosc;
	string isbn;
	string wydawnictwo;
	string tytul;
	string query;
	
	cout << "Podaj ilosc stron\nIlosc stron: ";
	getline(cin, ilosc);
	cout << "Podaj numer ISBN \nNumer ISBN: ";
	getline(cin, isbn);
	cout << "Podaj wydawnictwo \nWydawnictwo: ";
	getline(cin, wydawnictwo);
	cout << "Podaj tytul \nTytul: ";
	getline(cin, tytul);

	query = "INSERT INTO EGZEMPLARZE(iloscStron,numerISBN,wydawnictwo,osobaWyp,dataWyp,dataOdd,przedluzony,przetrzymany,ksiazka) "
		"VALUES(" +
		ilosc + "," +// ilosc stron
		"'" + isbn + "'," + //isbn
		"'" + wydawnictwo + "'," + //wydawnictwo
		"''," + //osoba wypozyczajaca
		"''," + //data wypozyczenia
		"''," + //data oddania
		"0," + //przedluzony
		"0," + //przetrzymany
		"'" + tytul + "' " + //tytul
		");";
	sqlite3_exec(db, query.c_str(), NULL, NULL, &error);
	if (error != SQLITE_OK) {
		cout << "blad: " << error << endl;
		system("pause");
		sqlite3_close(db);
		return -1;
	}
	return 1;

}
int Ui::addEgzemplarz2(string isbn, string tytul) {
	sqlite3* db;
	char* error;
	sqlite3_open("main_db.db", &db);
	if (db == NULL)
	{
		printf("Blad przy otwieraniu bazy danych\n");
		return -1;
	}
	string ilosc;
	string wydawnictwo;
	string query;

	cout << "\nPodaj ilosc stron\nIlosc stron: ";
	getline(cin, ilosc);
	cout << "Podaj wydawnictwo \nWydawnictwo: ";
	getline(cin, wydawnictwo);
	query = "INSERT INTO EGZEMPLARZE(iloscStron,numerISBN,wydawnictwo,osobaWyp,dataWyp,dataOdd,przedluzony,przetrzymany,ksiazka) "
	"VALUES("+
	ilosc + ","+// ilosc stron
	"'" + isbn + "',"+ //isbn
	"'" + wydawnictwo + "',"+ //wydawnictwo
	"'',"+ //osoba wypozyczajaca
	"'',"+ //data wypozyczenia
	"'',"+ //data oddania
	"0,"+ //przedluzony
	"0,"+ //przetrzymany
	"'" + tytul + "' "+ //tytul
	");";
	
	sqlite3_exec(db, query.c_str(), NULL, NULL, &error);
	if (error != SQLITE_OK) {
		cout << "blad: " << error << endl;
		system("pause");
		sqlite3_close(db);
		return -1;
	}
	
	return 1;
}
int Ui::addAutor() {
	system("CLS");
	cout << "Dodawanie autora" << endl;
	sqlite3* db;
	sqlite3_stmt* stmt;
	char* error;
	sqlite3_open("main_db.db", &db);
	if (db == NULL)
	{
		printf("Blad przy otwieraniu bazy danych\n");
		return -1;
	}
	string imie;
	string nazwisko;
	string dataUrodzenia;
	string query;


	cout << "Podaj imie autora\nImie: ";
	getline(cin, imie);
	cout << "Podaj nazwisko autora\nNazwisko: ";
	getline(cin, nazwisko);
	cout << "Podaj date urodzenia autora (dd-mm-rrrr)\nData urodzenia: ";
	getline(cin, dataUrodzenia);


	query = "INSERT INTO AUTOR(imie,nazwisko,dataUrodzenia,ksiazki) "
		"VALUES('" +
		imie + "','" + //isbn
		nazwisko + "','" + //wydawnictwo
		dataUrodzenia + "','" + //przedluzony
		"'" +
		");";
	sqlite3_exec(db, query.c_str(), NULL, NULL, &error);
	if (error != SQLITE_OK) {
		cout << "blad: " << error << endl;
		system("pause");
		sqlite3_close(db);
		return -1;
	}
	return 1;
}
int Ui::addAutor2(string imie, string ksiazka) {
	system("CLS");
	cout << "Dodawanie autora" << endl;
	sqlite3* db;
	sqlite3_stmt* stmt;
	char* error;
	sqlite3_open("main_db.db", &db);
	if (db == NULL)
	{
		printf("Blad przy otwieraniu bazy danych\n");
		return -1;
	}
	string d = " ";
	vector<string> sp = ElementyPomocnicze :: split_string(imie, d);
	string imie2 = sp[0];
	string nazwisko = sp[1];
	string dataUrodzenia;
	string query;


	cout << "Podaj date urodzenia autora "<<imie<<" (dd-mm-rrrr)\nData urodzenia: ";
	getline(cin, dataUrodzenia);


	query = "INSERT INTO AUTOR(imie,nazwisko,dataUrodzenia,ksiazki) "
		"VALUES('" +
		imie2 + "','" + //imie
		nazwisko + "','" + //nazwisko
		dataUrodzenia + "','" + //data urodzenia
		ksiazka + "'" +	//ksiazka
		");";
	sqlite3_exec(db, query.c_str(), NULL, NULL, &error);
	if (error != SQLITE_OK) {
		cout << "blad: " << error << endl;
		system("pause");
		return -1;
	}
	cout << "Dodano nowego autora i przypisano ksiazke" << endl;
	system("PAUSE");
	return 1;
}
int Ui::addAutor3(string imie, string ksiazka) {
	sqlite3* db;
	sqlite3_stmt* stmt;
	char* error;
	sqlite3_open("main_db.db", &db);
	if (db == NULL)
	{
		printf("Blad przy otwieraniu bazy danych\n");
		return -1;
	}
	//rozdzielanie imienia i nazwiska autora
	string d = " ";
	vector<string> sp = ElementyPomocnicze :: split_string(imie, d);
	string imie2 = sp[0];
	string nazwisko = sp[1];
	string query;
	bool exists = false;

	query = "SELECT EXISTS(SELECT 1 from AUTOR WHERE imie='" + imie2 + "' AND nazwisko='" + nazwisko + "' LIMIT 1);";
	sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, NULL);
	bool done = false;
	int row = 0;
	//sprawdzanie, czy autor istnieje w bazie danych
	while (!done) {
		switch (sqlite3_step(stmt)) {
		case SQLITE_ROW:
			//bytes = sqlite3_column_bytes(stmt, 0);
			for (int i = 0; i < sqlite3_column_count(stmt); i++) {
				if (sqlite3_column_text(stmt, i)[0] == '1') {
					exists = true;
				}
			}
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
	
	if (exists) {
		//autor istnieje, wiec sprawdzamy, czy ksiazka, ktora przypisujemy jest juz przypisana. jesli nie, to ja przypisujemy. jesli tak, konczymy i wypisujemy, ze to juz jest
		query = "SELECT ksiazki from AUTOR WHERE imie='" + imie2 + "' AND nazwisko='" + nazwisko + "';";

		//zmienna do ktorej tymczasowo wpisujemy wynik powyzszej kwerendy
		string ksiazki_autora = "";
		sqlite3_stmt* stmt2;

		sqlite3_prepare_v2(db, query.c_str(), -1, &stmt2, NULL);
		//zmienna, ktorej uzywamy, aby zapisac ksiazki, ktorymi aktualizujemy autora
		string to_update = "";
		//pobieramy ksiazki autora
		done = false;
		while (!done) {
			switch (sqlite3_step(stmt2)) {
			case SQLITE_ROW:
				for (int i = 0; i < sqlite3_column_count(stmt2); i++) {
					//przypisujemy pobrane z bazy ksiazki autora (string typu "aaa aaa||bbbbbbb||cccc cc||gggg gg")
					ksiazki_autora = string(reinterpret_cast<const char*>((sqlite3_column_text(stmt2, i))));
				}
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
		//jesli nie istnieja, to bedzie to pierwsza ksiazka autora i przypisujemy mu ja
		//cout << "Ksiazki autora: " << ksiazki_autora << endl;
		if (ksiazki_autora == "") {
			to_update = ksiazka;
		}
		else {
			//splitujemy ksiazki autora pobrane z bazy
			string d2 = "||";
			vector<string> ksiazki_split = ElementyPomocnicze :: split_string(ksiazki_autora, d2);

			//forem sprawdzamy, czy taka ksiazka nie jest juz do autora przypisana
			for (int i = 0; i < ksiazki_split.size(); i++) {
				if (ksiazki_split[i] == ksiazka) {
					cout << "Ksiazka jest juz dopisana do autora" << endl;
					return -1;
				}
			}
			to_update = ksiazki_autora + "||" + ksiazka;
		}
		//updatujemy rekord wstawiajac zmienna to_update do kolumny "ksiazka"
		query = "UPDATE AUTOR SET ksiazki='" + to_update + "' WHERE imie='" + imie2 + "' AND nazwisko='" + nazwisko + "';";
		sqlite3_exec(db, query.c_str(), NULL, NULL, &error);
		if (error != SQLITE_OK) {
			cout << "blad: " << error << endl;
			system("pause");
			sqlite3_close(db);
			return -1;
		}
		cout << "Przypisano ksiazke do autora" << endl;
		return 1;
	}
	
	else {
		//autor nie istnieje, wiec go dodajemy i przypisujemy mu ksiazke
		addAutor2(imie, ksiazka);
		cout << "dodano i powracamy" << endl;
		return 1;
	}
}
string Ui::checkEgzemplarze(string tytul) {
	sqlite3* db;
	sqlite3_stmt* stmt;
	char* error;
	sqlite3_open("main_db.db", &db);
	if (db == NULL)
	{
		printf("Blad przy otwieraniu bazy danych\n");
		return "false";
	}
	string query;
	//resultat z bazy danych - egzemplarze ksiazek
	string egzemplarze;
	//zmienna, ktora zwracamy. defaultowo ustawiamy "kod" bledu jako NOT_AVAILABLE
	string to_return = "NOT_AVAILABLE";
	query = "SELECT egzemplarze from KSIAZKA WHERE tytul='" + tytul + "' LIMIT 1;";
	sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, NULL);
	bool done = false;
	int row = 0;

	//pobranie egzemplarzy ksiazki z tabeli
	while (!done) {
		switch (sqlite3_step(stmt)) {
		case SQLITE_ROW:
			for (int i = 0; i < sqlite3_column_count(stmt); i++) {
				egzemplarze = string(reinterpret_cast<const char*>((sqlite3_column_text(stmt, i))));
			}
			row++;
			break;

		case SQLITE_DONE:
			done = true;
			break;

		default:
			fprintf(stderr, "Failed.\n");
			to_return = "false";
			return to_return;
		}
	}
	sqlite3_finalize(stmt);

	//dzielenie egzemplarzy
	string delimit_1 = "||";
	vector<string> split_egz = ElementyPomocnicze :: split_string(egzemplarze, delimit_1);

	//dla kazdego spradzamy dostepnosc
	for (int i = 0; i < split_egz.size(); i++) {
		sqlite3_stmt* stmt2;
		query = "SELECT dataWyp from EGZEMPLARZE WHERE numerISBN='" + split_egz[i] + "' LIMIT 1;";

		sqlite3_prepare_v2(db, query.c_str(), -1, &stmt2, NULL);
		done = false;
		int row = 0;
		
		//pobranie daty w celu sprawdzenia, czy ksiazka jest dostepna
		while (!done) {
			switch (sqlite3_step(stmt2)) {
			case SQLITE_ROW:
				//zasada dostepnosci - data wypozyczenia jest rowna "". jesli jest inaczej, to egzemplarz nie zostala jeszcze zwrocona
				for (int k = 0; k < sqlite3_column_count(stmt); k++) {
					string row = string(reinterpret_cast<const char*>((sqlite3_column_text(stmt2, k))));
					if (row == "") {
						sqlite3_finalize(stmt2);
						to_return = split_egz[i];
						return to_return;
					}
				}
				row++;
				break;

			case SQLITE_DONE:
				done = true;
				break;

			default:
				fprintf(stderr, "Failed.\n");
				to_return = "error";
				return to_return;
			}
		}
		sqlite3_finalize(stmt2);
	}
	return to_return;
}

Osoba* Ui :: zaloguj(int tryb, sqlite3* bazaDanych) {
	
	//tryb == 1 - logowanie czytelnika
	//tryb == 2 - logowanie bibliotekarza

	//z zalozenia do metody przekazywany jest wskaznik na otwarta juz baze.
	//mozna tego nie robic i otwierac wewnatrz tej metody.

	while (true) {

		system("CLS");

		string imie;
		string nazwisko;
		string haslo;
		int ret;      //Do przypisania wartosci zwracanej przez funkcje sqlite3_step(...).

		cout << "Logowanie do systemu biblioteki." << endl;
		cout << "Podaj imie: ";
		cin >> imie;
		cout << "Podaj nazwisko: ";
		cin >> nazwisko;
		cout << "Podaj haslo: ";
		cin >> haslo;

		string zapytanie;     //zapytanie sql

		//Jedyna roznica w logowaniu bibliotekarza i czytelnika jest zapytanie.

		//Nie bawilem sie w sprawdzanie istnienia za pomoca SQL (WHERE EXISTS) bo nie wiem jak zinterpretowac zwracana wartosc funkcja
		//w bibliotece sqlite3

		if (tryb == 1) {
			zapytanie = "SELECT imie, nazwisko, haslo "
				"FROM Czytelnik "
				"WHERE imie == '" +
				imie + "' AND nazwisko == '" +
				nazwisko + "' AND haslo == '" +
				haslo + "';";
		}
		else if (tryb == 2) {
			zapytanie = "SELECT imie, nazwisko, haslo "
				"FROM Bibliotekarz "
				"WHERE imie == '" +
				imie + "' AND nazwisko == '" +
				nazwisko + "' AND haslo == '" +
				haslo + "';";
		}

		sqlite3_stmt* stmt = NULL;

		sqlite3_prepare_v2(bazaDanych, zapytanie.c_str(), -1, &stmt, NULL);
		ret = sqlite3_step(stmt);
		sqlite3_finalize(stmt);

		//SQLITE_ROW jest zwracane przez sqlite3_step(...) jezeli jest dostepny wiersz do odczytu.
		//Zakladam, ze w bazie nie moze byc jednoczesnie dwoch rekordow o takich samych: imieniu, nazwisku i hasle

		//Czyli nie moze zajsc taka sytuacja, ze w tabeli sa dwa rekordy:
		//Rekord 1: imie = Adam nazwisko = Ligaj haslo = admin
		//Rekord2: imie = Adam nazwisko = Ligaj haslo = admin
		//Wiadomym jest, ze moze byc dwoch uzytkownikow o takim samym imieniu i nazwisku. Jest to praktycznie
		//niemozliwe ze stworza konta o takim samym hasle...

		//A wiec powinien byc tylko jeden wiersz do odczytu (pod warunkiem, ze istnieje i nie wystapily bledy).

		if (ret == SQLITE_ROW) {

			//Jest dostepny wiersz do oczytu czyli czytelnik znajduje sie w bazie.

			cout << "Pomyslnie zalogowano!" << endl;

			if (tryb == 1) {
				//TODO ladowanie otrzymanego rekordu do pamieci (tworzenie obiektu typu Czytelnik).
				//(Brak metody wczytywanieCzytelnika).

				//Tym razem pobieramy wszystkie kolumny (do wczytania).

				zapytanie = zapytanie = "SELECT * "
					"FROM Czytelnik "
					"WHERE imie == '" +
					imie + "' AND nazwisko == '" +
					nazwisko + "' AND haslo == '" +
					haslo + "';";

				sqlite3_prepare_v2(bazaDanych, zapytanie.c_str(), -1, &stmt, NULL);
				sqlite3_step(stmt);

				//To bedzie wykorzystywac metode wczytywanieCzytelnika a nie konsturktor domyslny.

				Czytelnik* czytelnik = new Czytelnik();
				sqlite3_finalize(stmt);
				system("pause");
				return czytelnik;
			}
			else if (tryb == 2) {

				//Metoda wczytywanieBibliotekarza zwraca wskaznik na obiekt dynamiczny typu Bibliotekarz utworzony na
				//podstawie zawartosci rekordu.

				zapytanie =  "SELECT * "
					"FROM Bibliotekarz "
					"WHERE imie == '" +
					imie + "' AND nazwisko == '" +
					nazwisko + "' AND haslo == '" +
					haslo + "';";

				sqlite3_prepare_v2(bazaDanych, zapytanie.c_str(),-1, &stmt, NULL);
				sqlite3_step(stmt);

				Bibliotekarz* bibliotekarz = wczytywanieBibliotekarza(stmt);
				sqlite3_finalize(stmt);
				system("pause");
				return bibliotekarz;
			}
		}
		else {

			int wybor = -1;

			//Jezeli logowanie sie nie powiodlo tj. SQLITE_ROW nie zostalo zwrocone przez funkcje (z roznego powodu),
			//sygnalizujemy wystapienie problemu i oferujemy mozliwosc ponownego logowania.

			//Przyczyna niepowodzenia logowania moze byc np. brak czytelnika w bazie danych, czyli wymagana jest
			//rejestracja.

			cout << "Logowanie sie nie powiodlo. Mozliwe ze uzytkownik o podanych danych nie istnieje." << endl;
			cout << "Jezeli chcesz wrocic do menu glownego wybierz 0." << endl;
			cout << "Jezeli chcesz sprobowac zalogowac sie ponownie, wybierz liczbe inna niz 0: ";
			cin >> wybor;

			if (wybor == 0) {
				return NULL;
			}
		}
	}
}

int Ui :: menuPoZalogowaniuCzytelnika(Czytelnik*czytelnik) {

	//Proste menu wyswietlane po zalogowaniu.
	//Po wyborze umozliwia dalsze operacje np. wypozyczenie ksiazki, aktualizacja danych itd.

	while (true) {
		system("CLS");
		int wybor = 0;
		cout << "Wprowadz odpowiednia liczbe aby kontynuowac." << endl;
		cout << "1: Wyswietl dane o bibliotece" << endl;
		cout << "2: Wyswietl dane o koncie" << endl;
		cout << "3: Wyswietl liste dostepnych ksiazek." << endl;
		cout << "4: Wyswietl liste wypozyczonych ksiazek." << endl;
		cout << "5: Wyswietl liste zaleglosci." << endl;
		cout << "0: Wyloguj i wroc do menu glownego." << endl;
		cout << "Wybor: ";
		cin >> wybor;
		
		if (wybor == 0) {
			return 0;
		}

		wyborWMenuCzytelnika(wybor);
	}
}

void Ui :: wyborWMenuCzytelnika(int wybor) {

	//Wyswietla odpowiednie informacje w zaleznosci od wyboru w menu czytelnika po zalogowaniu.
	//Wybor pozwala na wykonywanie odpowiednich czynnosci np. zmiana danych konta, wypozyczenie/oddanie ksiazki.

	system("CLS");
	switch (wybor) {
	case 1:
		//TODO: dodac wyswietlanie danych o bibliotece.
		cout << "Dane o bibliotece." << endl;
		break;
	case 2:
		//TODO: dodac wyswietlanie danych o koncie.
		cout << "Dane o koncie." << endl;
		break;
		//Po wyswietleniu ma miec mozliwosc modyfikacji niektorych danych.
	case 3:
		//TODO: dodac wyswietlanie listy dostepnych do wypozyczenia ksiazek.
		cout << "Lista dostepnych ksiazek." << endl;
		//Po wyswietleniu ma miec mozliwosc wypozyczenia ksiazki.
		break;
	case 4:
		//TODO: dodac liste wypozyczonych ksiazek.
		cout << "Lista wypozyczonych ksiazek." << endl;
		//Po wyswietleniu ma miec mozliwosc oddania ksiazki.
		break;
	case 5:
		//TODO: dodac wyswietlanie listy zaleglosci.
		cout << "Lista zaleglosci." << endl;
		//Po wyswietleniu ma miec mozliwosc oddania ksiazki.
		break;
	default:
		cout << "Niewlasciwa opcja. Sprobuj ponownie" << endl;
		//Obsluga bledow.
		break;
	}
	system("pause");
}

int Ui :: menuPoZalogowaniuBibliotekarza(Bibliotekarz*bibliotekarz, Biblioteka*biblioteka, sqlite3*bazaDanych) {

	//Proste menu wyswietlane po zalogowaniu bibliotekarza.
	//Po wyborze umozliwia dalsze operacje np. sprawdzenie rejestru spoznien.

	while (true) {

		system("CLS");
		int wybor = 0;
		cout << "Wprowadz odpowiednia liczbe aby kontynuowac." << endl;
		cout << "1: Wyswietl dane o bibliotece" << endl;
		cout << "2: Wyswietl dane o koncie" << endl;
		cout << "3: Wyswietl liste dostepnych ksiazek." << endl;
		cout << "4: Wyswietl liste osob zalegajacych z oddaniem ksiazki." << endl;
		cout << "0: Wyloguj i wroc do menu glownego." << endl;
		cout << "Wybor: ";
		cin >> wybor;

		if (wybor == 0) {
			return 0;
		}
		wyborWMenuBibliotekarza(wybor, bibliotekarz, biblioteka, bazaDanych);
	}
}

void Ui :: wyborWMenuBibliotekarza(int wybor, Bibliotekarz*bibliotekarz, Biblioteka*biblioteka, sqlite3*bazaDanych) {

	//Wyswietla odpowienie informacje w zaleznosci od wyboru w menu.
	//Wybor odpowiedniej opcji w menu pozwala rowniez dokonac roznych akcji np. wyslanie powiadomienia
	//o zaleganiu z oddanie ksiazek.

	system("CLS");
	switch (wybor) {
	case 1:
	{
		biblioteka->printInfo();
		cout << endl;
		cout << "Nie posiadasz uprawnien do zmiany tych danych." << endl;
		break;
	}
	case 2:
	{
		cout << "Dane o koncie." << endl;
		bibliotekarz->printInfOBibliotekarzu();
		cout << endl;
		int wybor1;
		cout << "Aby zmienic dane wprowadz 1. Inaczej wprowadz dowolna liczbe poza 1." << endl;
		cout << "Wybor: ";
		cin >> wybor1;
		cout << endl;
		if (wybor1 == 1) {
			zmienDaneBibliotekarza(bibliotekarz, bazaDanych);
		}
		break;
	}
	case 3:
	{
		//TODO: dodac wyswietlanie listy dostepnych do wypozyczenia ksiazek.
		cout << "Lista dostepnych ksiazek." << endl;
		//Po wyswietleniu ma miec mozliwosc wypozyczenia ksiazki.
		break;
	}
	case 4:
	{
		//TODO: dodac liste wypozyczonych ksiazek.
		cout << "Lista osob z zaleglosciami" << endl;
		//Po wyswietleniu ma miec mozliwosc wyslania powiadomienia o zaleglosciach.
		break;
	}
	default:
	{
		cout << "Niewlasciwa opcja. Sprobuj ponownie" << endl;
		//Obsluga bledow.
		break;
	}
	}
	system("pause");
}

Bibliotekarz* Ui :: wczytywanieBibliotekarza(sqlite3_stmt*stmt) {

	//Baza danych musi byc otwarta.
	//Do metody przekazuje siê obiekt typu stmt (ju¿ przygotowany, utworzony).
	//Z zalozenia jest to metoda do wykorzystania w metodzie logujacej Bibliotekarza.
	//dlatego tez, wiersze w tabeli Czytelnik sa juz gotowe do odczytu (przygotowanie jest robione w 
	//metodzie logujacej).

	int id = sqlite3_column_int(stmt, 0);
	string imie = ElementyPomocnicze :: konwersjaNaString(sqlite3_column_text(stmt, 1));
	string nazwisko = ElementyPomocnicze :: konwersjaNaString(sqlite3_column_text(stmt, 2));
	int wiek = sqlite3_column_int(stmt, 3);
	Data dataUrodzenia = ElementyPomocnicze :: konwersjaNaData(ElementyPomocnicze :: konwersjaNaString(sqlite3_column_text(stmt,4)));
	string haslo = ElementyPomocnicze :: konwersjaNaString(sqlite3_column_text(stmt, 5));
	string email = ElementyPomocnicze :: konwersjaNaString(sqlite3_column_text(stmt, 6));
	string telefon = ElementyPomocnicze :: konwersjaNaString(sqlite3_column_text(stmt, 7));
	string miasto = ElementyPomocnicze :: konwersjaNaString(sqlite3_column_text(stmt, 8));
	string kodPocztowy = ElementyPomocnicze :: konwersjaNaString(sqlite3_column_text(stmt, 9));
	string ulica = ElementyPomocnicze :: konwersjaNaString(sqlite3_column_text(stmt, 10));
	int numerMieszkania = sqlite3_column_int(stmt, 11);

	Adres adres = Adres(miasto, kodPocztowy, ulica, numerMieszkania);

	Bibliotekarz* bibliotekarz = new Bibliotekarz(imie, nazwisko, email, telefon, dataUrodzenia.getDzien(), dataUrodzenia.getMiesiac(), dataUrodzenia.getRok(), adres, id);
	bibliotekarz->setHaslo(haslo);

	return bibliotekarz;
}

void Ui :: zmienDaneBibliotekarza(Bibliotekarz* bibliotekarz, sqlite3*bazaDanych) {

	while (true) {

		int wybor;
		system("CLS");
		cout << "Wybierz co chcesz zmienic." << endl;
		cout << "Pamietaj, ze nie mozna zmienic niektorych danych za pomoca systemu. ";
		cout << "W sprawie ich zmiany skontaktuj sie z dyrekcja biblioteki." << endl;
		cout << "1: Zmiana hasla" << endl;
		cout << "2: Zmiana adresu e-mail" << endl;
		cout << "3: Zmiana numeru telefonu" << endl;
		cout << "0: Przerwanie dokonywania zmian" << endl;
		cin >> wybor;

		string zapytanie;
		sqlite3_stmt* stmt = NULL;

		switch (wybor) {
		case 0:
			return;
		case 1:
		{
			while (true) {
				string haslo1;
				string haslo2;
				cout << "Podaj nowe haslo: ";
				cin >> haslo1;
				cout << "Powtorz haslo: ";
				cin >> haslo2;

				if (haslo1 != haslo2) {
					int wybor1 = -1;
					cout << "Hasla nie sa zgodne. Sprobuj ponownie albo zakoncz (0).";
					cin >> wybor1;
					if (wybor1 == 0) {
						break;
					}
				}
				else {
					zapytanie = "UPDATE Bibliotekarz "
						"SET haslo = '" +
						haslo1 + "' WHERE ID == " + to_string(bibliotekarz->getID()) + ";";
					sqlite3_exec(bazaDanych, zapytanie.c_str(), NULL, NULL, NULL);
					bibliotekarz->setHaslo(haslo1);
					cout << "Pomyslnie zmieniono haslo" << endl;
					system("pause");
					break;
				}
			}
			break;
		}
		case 2:
		{
			string email;
			cout << "Podaj nowy adres email: ";
			cin >> email;

			zapytanie = "UPDATE Bibliotekarz "
				"SET email = '" +
				email + "' WHERE ID == " + to_string(bibliotekarz->getID()) + ";";
			sqlite3_exec(bazaDanych, zapytanie.c_str(), NULL, NULL, NULL);
			bibliotekarz->setEmail(email);
			cout << "Pomyslnie zmieniono adres e-mail" << endl;
			system("pause");
			break;
		}
		case 3:
		{
			string telefon;
			cout << "Podaj nowy nr. telefonu: ";
			cin >> telefon;

			zapytanie = "UPDATE Bibliotekarz "
				"SET telefon = '" +
				telefon + "' WHERE ID == " + to_string(bibliotekarz->getID()) + ";";
			sqlite3_exec(bazaDanych, zapytanie.c_str(), NULL, NULL, NULL);
			bibliotekarz->setTelefon(telefon);
			cout << "Pomyslnie zmieniono nr. telefonu" << endl;
			system("pause");
			break;
		}
		default:
		{
			cout << "Niewlasciwa opcja. Sprobuj ponownie." << endl;
			system("pause");
			break;
		}
		}
	}
}

Biblioteka* Ui :: wczytywanieBiblioteki(sqlite3* bazaDanych) {

	//Wczytuje biblioteke do bazy danych. 

	if (bazaDanych == NULL) {

		//Na wypadek gdyby przekazano NULL'a.

		sqlite3_open("..\\ProjektBiblioteka\\main_db.db", &bazaDanych);

		if (bazaDanych == NULL) {

			//Nie udalo sie otworzyc bazy danych.

			return NULL;
		}
	}

	string zapytanie = "SELECT * FROM BIBLIOTEKA;";
	sqlite3_stmt* stmt = NULL;
	sqlite3_prepare_v2(bazaDanych, zapytanie.c_str(), -1, &stmt, NULL);
	sqlite3_step(stmt);

	string emailKontaktowy = ElementyPomocnicze :: konwersjaNaString(sqlite3_column_text(stmt, 0));
	string telefonKontaktowy = ElementyPomocnicze :: konwersjaNaString(sqlite3_column_text(stmt, 1));
	string miasto = ElementyPomocnicze :: konwersjaNaString(sqlite3_column_text(stmt, 2));
	string kodPocztowy = ElementyPomocnicze :: konwersjaNaString(sqlite3_column_text(stmt, 3));
	string ulica = ElementyPomocnicze :: konwersjaNaString(sqlite3_column_text(stmt, 4));
	int numer = sqlite3_column_int(stmt, 5);
	int iloscEgzemplarzy = sqlite3_column_int(stmt, 6);
	map<string, string> godzinyOtwarcia = Biblioteka :: wczytywanieGodzin(bazaDanych);

	Adres adres = Adres(miasto, kodPocztowy, ulica, numer);

	sqlite3_finalize(stmt);

	Biblioteka* biblioteka = new Biblioteka(emailKontaktowy, telefonKontaktowy, adres, godzinyOtwarcia, iloscEgzemplarzy);

	return biblioteka;
}





