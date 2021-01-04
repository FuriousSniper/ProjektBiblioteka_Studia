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
#include <regex>


using namespace std;

Adres Ui::createAdres() {

	string miasto;
	cin.clear();
	cout << "Podaj miasto: ";
	getline(cin, miasto);

	string kod;
	cout << "Podaj kod pocztowy: ";
	cin >> kod;
	cin.clear();
	cin.ignore(200, '\n');

	string ulica;
	cout << "Podaj ulice i nr domu Twojego adresu zamieszkania: ";
	getline(cin, ulica);
	cin.clear();

	cout << "Podaj numer Twojego mieszkania (opcjonalne): ";
	int numerMieszkania;
	cin >> numerMieszkania;
	cin.clear();
	cin.ignore(200, '\n');
	Adres adres = Adres(miasto, kod, ulica, numerMieszkania);
	return adres;
}

Osoba Ui::createOsoba(sqlite3* bazaDanych) {

	//Ta metoda z zalozenia wykorzystywana jest w metodzie createUzytkownik oraz createAutor.
	//Tworzy obiekt typu Osoba i go zwraca.

	//Nie sprawdza czy baza jest otwarta bo jest to robione w metodzie sprawdzDostepnoscEmail, ktora
	//wykorzystuje ta baze jako jedyna.

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
	//podawanie danych do obiektu Osoba
	cout << "Podaj imie: ";
	cin >> imie;
	cin.clear();
	cin.ignore(200, '\n');
	cout << "Podaj nazwisko: ";
	cin >> nazwisko;

	do {
		//dzien, miesiac, rok sa typu int a moze wprowadzic jakies znaki.
		system("CLS");
		cin.clear();
		cin.ignore(200, '\n');
		cout << "Podaj date urodzenia (dd mm rrrr): ";
		cin >> dzien >> miesiac >> rok;
	} while (!cin.good());

	while (true) {

		system("CLS");
		cout << "Podaj swoj email: ";
		cin >> email;
		cin.clear();
		cin.ignore(200, '\n');

		//Sprawdzenie czy e-mail zawiera @ oraz . w nazwie domeny. (np. @gmail.com).

		if (!sprawdzPoprawnoscEmail(email)) {
			cout << "Niepoprawny format adresu e-mail. Sprobuj ponownie." << endl;
			system("pause");
		}
		else {
			cout << "Powtorz swoj email: ";
			string email2;
			cin >> email2;
			cin.clear();
			cin.ignore(200, '\n');

			//Sprawdzanie dostepnosci e-maila, bo moze byc taka sytuacja, ze jest juz zajety.
			//Sprawdza tylko wtedy, gdy wprowadzono 2 identyczne e-maile.

			if (email == email2 && sprawdzDostepnoscEmail(bazaDanych, email)) {
				cout << "Podaj swoj nr telefonu: ";
				//Wczytuje linie bo moze podac oddzielony spacjami (np. 678 567 456).
				getline(cin, telefon);
				break;
			}

			//Gdy wprowadzono 2 identyczne e-maile drukuje odpowiedni komunikat i nastepuje przejscie do kolejnej
			//iteracji w celu wprowadzenia maila ponownie.

			else if (email == email2 && !sprawdzDostepnoscEmail(bazaDanych, email)) {
				cout << "Email jest juz zajety. Sprobuj ponownie." << endl;
				system("pause");
			}
			else {
				cout << "Podane adresy nie sa zgodne." << endl;
				system("pause");
			}
		}
	}
	adres = createAdres();
	Osoba osoba = Osoba(imie, nazwisko, email, telefon, dzien, miesiac, rok, adres);
	return osoba;
}

bool Ui::sprawdzPoprawnoscEmail(string email) {

	//Sprawdza poprawnosc email pod katem wystapienia znaku @ oraz . w nazwie domeny.
	const regex format("(\\w+)(\\.|_)?(\\w*)@(\\w+)(\\.(\\w+))+");
	return regex_match(email, format);
}

bool Ui::sprawdzDostepnoscEmail(sqlite3* bazaDanych, string email) {

	//Metoda sluzaca do sprawdzania dostepnosci e-maila

	//Na wypadek gdyby przekazano zamknieta baze.

	if (bazaDanych == NULL) {
		//Proba otworzenia bazy.
		sqlite3_open("..\\ProjektBiblioteka\\main_db.db", &bazaDanych);
		//Jezeli proba sie nie powiodla to nie powodzi sie tez sprawdzanie dostepnosci.
		if (bazaDanych == NULL) {
			return false;
		}
	}

	//Sprawdzam w obydwu tabelach - Czytelnik i Bibliotekarz. Mozna to zrobic za pomoca jednego zapytania
	//SQL.

	sqlite3_stmt* stmt = NULL;
	string zapytanie = "SELECT * FROM Czytelnik WHERE email == '" + email + "';";
	int ret1, ret2;

	sqlite3_prepare_v2(bazaDanych, zapytanie.c_str(), -1, &stmt, NULL);
	//Zapisuje wartosc zwracana przez funkcje do dalszego sprawdzania w warunku.
	ret1 = sqlite3_step(stmt);
	sqlite3_finalize(stmt);

	zapytanie = "SELECT * FROM Bibliotekarz WHERE email == '" + email + "';";
	sqlite3_prepare_v2(bazaDanych, zapytanie.c_str(), -1, &stmt, NULL);
	ret2 = sqlite3_step(stmt);
	sqlite3_finalize(stmt);

	//SQLITE_DONE jest zwracane jezeli nie wystapil zaden blad oraz nie ma zadnego wiersza do oczytu.
	//Jezeli nie znaleziono zadnego rekordu o zadanym e-mailu to oznacza to, ze jest wolny.
	//Mozna ewentualnie dodac rozpatrywanie przypadkow - co sie dzieje w przypadku bledu a co w przypadku
	//SQLITE_ROW. Na razie jest to ujednolicone i zwraca false.

	if (ret1 == SQLITE_DONE && ret2 == SQLITE_DONE) {
		return true;
	}
	else {
		return false;
	}
}

Autor Ui::createAutor(sqlite3* bazaDanych) {
	cout << "Tworzenie nowego Autora" << endl;
	Osoba o = createOsoba(bazaDanych);
	//Autor dziedziczy po Osobie, wiec tworzymy obiekt osoba i przepisujemy wartosci. da sie to zrobic prosciej przypisujac obiekt zamiast poszczegolnych skladowych, ale na razie to nie jest istotne
	Autor a = Autor(o.getImie(), o.getNazwisko(), o.getDataUrodzenia().getDzien(), o.getDataUrodzenia().getMiesiac(), o.getDataUrodzenia().getRok());
	cout << "Pomyslnie utworzono: Autor" << endl;
	return a;
}

string Ui::oknoTworzeniaHasla() {

	string pass1;
	string pass2;

	while (true) {
		cout << "Podaj haslo do swojego konta: ";
		cin >> pass1;
		cin.clear();
		cin.ignore(200, '\n');
		cout << "Potwierdz haslo do swojego konta: ";
		cin >> pass2;
		cin.clear();
		cin.ignore(200, '\n');
		if (pass1 == pass2) {
			return pass1;
		}
		else {
			cout << "Hasla nie sa zgodne! Sprobuj ponownie.\n";
		}
	}
}

Osoba* Ui::createUzytkownik(int tryb, sqlite3* bazaDanych) {

	//Tworzenie czytelnika/bibliotekarza w zaleznosci od wybranego trybu.

	if (bazaDanych == NULL) {
		sqlite3_open("..\\ProjektBiblioteka\\main_db.db", &bazaDanych);
		if (bazaDanych == NULL) {
			return NULL;
		}
	}
	if (tryb != 1 && tryb != 2) {
		return NULL;
	}

	sqlite3_stmt* stmt = NULL;
	int temp = -1;

	//W zaleznosci od trybu przygotowuje odpowienie zapytanie.

	if (tryb == 1) {
		cout << "Tworzenie czytelnika." << endl;
		sqlite3_prepare_v2(bazaDanych, "select MAX(ID) from CZYTELNIK", -1, &stmt, NULL);
	}
	else if (tryb == 2) {
		cout << "Tworzenie bibliotekarza." << endl;
		sqlite3_prepare_v2(bazaDanych, "select MAX(ID) from BIBLIOTEKARZ", -1, &stmt, NULL);
	}

	//Jezeli tabela zawiera jakies rekordy to pobierz Id.

	if (sqlite3_step(stmt) == SQLITE_ROW) {
		temp = sqlite3_column_int(stmt, 0);
	}
	temp++;

	//Tworzenie obiektu pomocniczego osoba.
	Osoba osoba = createOsoba(bazaDanych);
	//Okno tworzenia hasla dla osoby.
	string haslo = oknoTworzeniaHasla();

	//W zaleznosci od wybranego trybu tworzenie czytelnika lub bibliotekarza.
	if (tryb == 1) {
		Czytelnik* czytelnik = new Czytelnik(osoba.getImie(), osoba.getNazwisko(), osoba.getEmail(), osoba.getTelefon(), osoba.getDataUrodzenia().getDzien(), osoba.getDataUrodzenia().getMiesiac(), osoba.getDataUrodzenia().getRok(), osoba.getAdresZamieszkania(), haslo, temp);
		return czytelnik;
	}
	else if (tryb == 2) {
		Bibliotekarz* bibliotekarz = new Bibliotekarz(osoba.getImie(), osoba.getNazwisko(), osoba.getEmail(), osoba.getTelefon(), osoba.getDataUrodzenia().getDzien(), osoba.getDataUrodzenia().getMiesiac(), osoba.getDataUrodzenia().getRok(), osoba.getAdresZamieszkania(), haslo, temp);
		return bibliotekarz;
	}
}

bool Ui::addUzytkownik(int tryb, sqlite3* bazaDanych, Osoba* osoba) {

	//Metoda dodajaca uzytkownika (czytelnika/biblitotekarza) do bazy danych w zaleznosci od wybranego trybu.

	if (tryb != 1 && tryb != 2 || osoba == NULL) {
		return false;
	}

	if (bazaDanych == NULL) {
		sqlite3_open("main_db.db", &bazaDanych);
		if (bazaDanych == NULL) {
			return false;
		}
	}

	string zapytanie;
	char* blad;

	//Dodawanie czytelnika lub biblitekarza w zaleznosci od trybu.

	if (tryb == 1) {

		//Wartaloby sprawdzic przypadek, gdy przekaze do funkcji wskaznik na bibliotekarza (Bibliotekarz*).
		Czytelnik* czytelnik = reinterpret_cast<Czytelnik*>(osoba);

		zapytanie = "INSERT INTO CZYTELNIK"
			"(listaZaleglosci,dataPierwszegoWypozyczenia,iloscWypozyczonychOdDolaczenia,preferowaneTematy,"	"dataDolaczenia,miasto,kodPocztowy,ulica,imie,nazwisko,wiek,dataUrodzenia,haslo,numerMieszkania,"
			"email,telefon)"
			" VALUES ("
			"	'',"
			"	'',"
			"	0,"
			"	'',"
			"	DATE(),'" +
			czytelnik->getAdresZamieszkania().getMiasto() + "','" +
			czytelnik->getAdresZamieszkania().getKodPocztowy() + "','" +
			czytelnik->getAdresZamieszkania().getUlica() + "','" +
			czytelnik->getImie() + "','" +
			czytelnik->getNazwisko() + "','" +
			to_string(czytelnik->getWiek()) + "','" +
			to_string(czytelnik->getDataUrodzenia().getDzien()) + "-" +
			to_string(czytelnik->getDataUrodzenia().getMiesiac()) + "-" +
			to_string(czytelnik->getDataUrodzenia().getRok()) + "','" +
			czytelnik->getHaslo() + "','" +
			to_string(czytelnik->getAdresZamieszkania().getNumerMieszkania()) + "','" +
			czytelnik->getEmail() + "','" +
			czytelnik->getTelefon() + "'"
			"	);";
	}
	else if (tryb == 2) {

		//Wartaloby sprawdzic przypadek, gdy przekaze do funkcji wskaznik na czytelnika (Czytelnik*).
		Bibliotekarz* bibliotekarz = reinterpret_cast<Bibliotekarz*>(osoba);

		zapytanie = "INSERT INTO BIBLIOTEKARZ"
			"(imie, nazwisko, wiek,"
			"dataUrodzenia, haslo, email, telefon, miasto, kodPocztowy, ulica, numerMieszkania)"
			" VALUES ('" +
			bibliotekarz->getImie() + "','" +
			bibliotekarz->getNazwisko() + "'," +
			to_string(bibliotekarz->getWiek()) + ",'" +
			to_string(bibliotekarz->getDataUrodzenia().getDzien()) + "-" +
			to_string(bibliotekarz->getDataUrodzenia().getMiesiac()) + "-" +
			to_string(bibliotekarz->getDataUrodzenia().getRok()) + "','" +
			bibliotekarz->getHaslo() + "','" +
			bibliotekarz->getEmail() + "','" +
			bibliotekarz->getTelefon() + "','" +
			bibliotekarz->getAdresZamieszkania().getMiasto() + "','" +
			bibliotekarz->getAdresZamieszkania().getKodPocztowy() + "','" +
			bibliotekarz->getAdresZamieszkania().getUlica() + "','" +
			to_string(bibliotekarz->getAdresZamieszkania().getNumerMieszkania()) + "');";
	}

	//Wykonaj zapytanie.
	sqlite3_exec(bazaDanych, zapytanie.c_str(), NULL, NULL, &blad);

	//Ewentualnie wyswietla blad.
	if (blad != SQLITE_OK) {
		cout << "Wystapil blad: " << blad << endl;
		return false;
	}
	return true;
}

int Ui::signInUpMenu() {
	int n = 0;
	while (true) {
		system("CLS");
		cout << "System obslugi Biblioteki (v. alfa 0.1)\n";
		cout << "Wybierz '1', aby sie zalogowac." << endl;
		cout << "Wybierz '2', aby sie zarejestrowac." << endl;
		cout << "Wybierz '9', aby wyjsc z programu." << endl;
		cout << "Wybor: ";
		cin >> n;
		if (n == 9) {
			cout << "Zakonczono prace programu" << endl;
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
		cout << "Wybierz '9', aby wyjsc z programu." << endl;
		cout << "Wybierz '3', aby powrocic do menu glownego." << endl;
		cout << "Uwaga! W przypadku rejestracji Bibliotekarza wymagana jest autoryzacja dyrekcji.\n";
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

	string tytul = "";
	string autorzy = "";
	string tagi = "";
	string kategoria = "";
	string egzemplarze = "";
	string dmr;

	cout << "Podaj tytul\nTytul: ";
	//uzywam getline, zeby pozwolic na spizywanie tytulow ze spacjami.
	getline(cin, tytul);
	cout << "Podaj autorow. Jesli wielu, wpisywac ze znakami specjalnymi \" || \" pomiedzy. Przyklad: \"Sasha Kostylev || Niko Kovac\" \nAutorzy: ";
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
			vector<string> autors_splitted = ElementyPomocnicze::split_string(autorzy, delimit);
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
			dmr +
			"'	);";
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

			splittedString = ElementyPomocnicze::split_string(egzemplarze, delimeter);
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
int Ui::getSpecificUserBook(Czytelnik c, string isbn) {
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
		if (sqlite3_column_text(stmt, i) != NULL) {
			//zmienna, do ktorej przypisujemy wynik query (1 kolumna)
			string result = string(reinterpret_cast<const char*>((sqlite3_column_text(stmt, i))));
			//porownanie resultatu z numerem isbn, ktorego szukamy
			if (result == isbn) {
				sqlite3_finalize(stmt);
				sqlite3_close(db);
				return i + 1;
			}
		}
	}
	sqlite3_finalize(stmt);
	cout << "Czytelnik " << c.getImie() << " " << c.getNazwisko() << " nie wypozyczyl takiej ksiazki!" << endl;
	return -1;
}
int Ui::lendBook(Czytelnik c, string tytul) {
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
int Ui::returnBook(Czytelnik c, string isbn) {
	string imie = c.getImie();
	string nazwisko = c.getNazwisko();
	sqlite3* db;
	sqlite3_stmt* stmt;
	string query;
	char* error;
	//zmienna, ktora ustawiamy, w zaleznosci od poprawnosci numeru isbn zwracanej ksiazki
	bool exists = false;

	//sprawdzanie, czy ksiazka jest wypozyczona przez usera i jesli tak, to zwraca kolumne w tabeli, w ktorej ksiazka jest umieszczona
	int user_book_column = getSpecificUserBook(c, isbn);

	//ustawianie zmiennej w zaleznosci od istnienia ksiazki
	if (user_book_column != -1)
		exists = true;

	if (exists) {
		sqlite3_open("main_db.db", &db);
		if (db == NULL)
		{
			printf("Blad przy otwieraniu bazy danych\n");
			return -1;
		}
		//updatowanie egzemplarza. clearowanie pol ustawianych przy wypozyczeniu
		query = "UPDATE EGZEMPLARZE SET dataWyp='', dataOdd='', osobaWyp='' WHERE numerISBN='" + isbn + "';";
		sqlite3_exec(db, query.c_str(), NULL, NULL, &error);
		if (error != SQLITE_OK) {
			cout << "blad: " << error << endl;
			system("pause");
			sqlite3_close(db);
			return -1;
		}
		//updatowanie czytelnika
		query = "UPDATE CZYTELNIK SET ksiazka" + to_string(user_book_column) + "='' WHERE imie='" + imie + "' AND nazwisko='" + nazwisko + "' ;";
		sqlite3_exec(db, query.c_str(), NULL, NULL, &error);
		if (error != SQLITE_OK) {
			cout << "blad: " << error << endl;
			system("pause");
			sqlite3_close(db);
			return -1;
		}
	}
	else {
		return -1;
	}
	return 0;
}
int Ui::getUserBooks(Czytelnik c) {
	string imie = c.getImie();
	string nazwisko = c.getNazwisko();
	sqlite3* db;
	sqlite3_stmt* stmt;
	char* error;

	sqlite3_open("main_db.db", &db);
	if (db == NULL)
	{
		printf("Blad przy otwieraniu bazy danych\n");
		return -1;
	}
	//numery isbn ksiazek, ktore czytelnik wypozyczyl
	string k1 = "";
	string k2 = "";
	string k3 = "";
	string query;
	query = "SELECT ksiazka1, ksiazka2, ksiazka3 from CZYTELNIK WHERE imie='" + imie + "' AND nazwisko='" + nazwisko + "';";
	sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, NULL);
	bool done = false;
	int row = 0;

	//pobranie egzemplarzy ksiazki z tabeli
	while (!done) {
		switch (sqlite3_step(stmt)) {
		case SQLITE_ROW:
			for (int i = 0; i < sqlite3_column_count(stmt); i++) {
				if (i == 0) {
					if (sqlite3_column_text(stmt, i) != NULL)
						k1 = string(reinterpret_cast<const char*>((sqlite3_column_text(stmt, i))));
				}
				if (i == 1) {
					if (sqlite3_column_text(stmt, i) != NULL)
						k2 = string(reinterpret_cast<const char*>((sqlite3_column_text(stmt, i))));
				}
				if (i == 2) {
					if (sqlite3_column_text(stmt, i) != NULL)
						k3 = string(reinterpret_cast<const char*>((sqlite3_column_text(stmt, i))));
				}

			}
			row++;
			break;

		case SQLITE_DONE:
			done = true;
			break;

		default:
			fprintf(stderr, "Failed.\n");
			return -1;
		}
	}
	sqlite3_finalize(stmt);
	//drabinka przypadkow, w celu utworzenia poprawnego query do bazy danych
	if (k1 == "" && k2 == "" && k3 == "") {	//000
		cout << "Brak wypozyczonych ksiazek" << endl;
		return 1;
	}

	if (k1 != "" && k2 == "" && k3 == "") {	//100
		query = "SELECT ksiazka, numerISBN FROM EGZEMPLARZE WHERE numerISBN='" + k1 + "';";
	}
	if (k1 == "" && k2 != "" && k3 == "") {	//010
		query = "SELECT ksiazka, numerISBN FROM EGZEMPLARZE WHERE numerISBN='" + k2 + "';";
	}
	if (k1 == "" && k2 == "" && k3 != "") { //001
		query = "SELECT ksiazka, numerISBN FROM EGZEMPLARZE WHERE numerISBN='" + k3 + "';";
	}

	if (k1 != "" && k2 != "" && k3 == "") { //110
		query = "SELECT ksiazka, numerISBN FROM EGZEMPLARZE WHERE numerISBN='" + k1 + "' OR numerISBN='" + k2 + "';";
	}
	if (k1 != "" && k2 == "" && k3 != "") { //101
		query = "SELECT ksiazka, numerISBN FROM EGZEMPLARZE WHERE numerISBN='" + k1 + "' OR numerISBN='" + k3 + "';";
	}
	if (k1 == "" && k2 != "" && k3 != "") { //011
		query = "SELECT ksiazka, numerISBN FROM EGZEMPLARZE WHERE numerISBN='" + k2 + "' OR numerISBN='" + k3 + "';";
	}

	if (k1 != "" && k2 != "" && k3 != "") { //111
		query = "SELECT ksiazka, numerISBN FROM EGZEMPLARZE WHERE numerISBN='" + k1 + "' OR numerISBN='" + k2 + "' OR numerISBN='" + k3 + "';";
	}
	sqlite3_stmt* stmt2;
	done = false;
	row = 0;
	//wypisywanie na ekran ksiazek i numerow isbn ksiazek
	cout << "Ksiazki Czytelnika " << imie << " " << nazwisko << ": " << endl;
	sqlite3_prepare_v2(db, query.c_str(), -1, &stmt2, NULL);
	while (!done) {
		switch (sqlite3_step(stmt2)) {
		case SQLITE_ROW:
			if (sqlite3_column_text(stmt2, 0) != NULL)
				cout << "tytul: " << sqlite3_column_text(stmt, 0) << endl;
			if (sqlite3_column_text(stmt2, 1) != NULL)
				cout << "numer ISBN: " << sqlite3_column_text(stmt2, 1) << endl << endl;
			row++;
			break;

		case SQLITE_DONE:
			done = true;
			break;

		default:
			fprintf(stderr, "Failed.\n");
			return -1;
		}
	}
	sqlite3_finalize(stmt2);
	return 1;
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
	vector<string> sp = ElementyPomocnicze::split_string(imie, d);
	string imie2 = sp[0];
	string nazwisko = sp[1];
	string dataUrodzenia;
	string query;


	cout << "Podaj date urodzenia autora " << imie << " (dd-mm-rrrr)\nData urodzenia: ";
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
	vector<string> sp = ElementyPomocnicze::split_string(imie, d);
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
			vector<string> ksiazki_split = ElementyPomocnicze::split_string(ksiazki_autora, d2);

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
	vector<string> split_egz = ElementyPomocnicze::split_string(egzemplarze, delimit_1);

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

Osoba* Ui::zaloguj(int tryb, sqlite3* bazaDanych) {

	//tryb == 1 - logowanie czytelnika
	//tryb == 2 - logowanie bibliotekarza

	if (bazaDanych == NULL) {
		sqlite3_open("..\\ProjektBiblioteka\\main_db.db", &bazaDanych);
		if (bazaDanych == NULL) {
			return NULL;
		}
	}

	while (true) {

		system("CLS");

		string email;
		string haslo;
		int ret;      //Do przypisania wartosci zwracanej przez funkcje sqlite3_step(...).

		cout << "Logowanie do systemu biblioteki." << endl;
		cout << "Podaj adres e-mail konta: ";
		cin >> email;
		cout << "Podaj haslo: ";
		cin >> haslo;

		string zapytanie;     //zapytanie sql

		//Jedyna roznica w logowaniu bibliotekarza i czytelnika jest zapytanie.

		//Nie bawilem sie w sprawdzanie istnienia za pomoca SQL (WHERE EXISTS) bo nie wiem jak zinterpretowac zwracana wartosc funkcja
		//w bibliotece sqlite3

		if (tryb == 1) {
			zapytanie = "SELECT imie, nazwisko, haslo "
				"FROM Czytelnik "
				"WHERE email == '" +
				email + "' AND haslo == '" +
				haslo + "';";
		}
		else if (tryb == 2) {
			zapytanie = "SELECT imie, nazwisko, haslo "
				"FROM Bibliotekarz "
				"WHERE email == '" +
				email + "' AND haslo == '" +
				haslo + "';";
		}

		sqlite3_stmt* stmt = NULL;

		sqlite3_prepare_v2(bazaDanych, zapytanie.c_str(), -1, &stmt, NULL);
		ret = sqlite3_step(stmt);
		sqlite3_finalize(stmt);

		//SQLITE_ROW jest zwracane przez sqlite3_step(...) jezeli jest dostepny wiersz do odczytu.
		//Zakladam, ze w bazie nie moze byc jednoczesnie dwoch rekordow o takich samych: emailu i hasle

		//Czyli nie moze zajsc taka sytuacja, ze w tabeli sa dwa rekordy:
		//Rekord 1: email = roj@gmail.com haslo = admin
		//Rekord 2: email = roj@gmail.com haslo = admin

		if (ret == SQLITE_ROW) {

			//Jest dostepny wiersz do oczytu czyli czytelnik znajduje sie w bazie.

			cout << "Pomyslnie zalogowano!" << endl;

			if (tryb == 1) {
				//TODO ladowanie otrzymanego rekordu do pamieci (tworzenie obiektu typu Czytelnik).
				//(Brak metody wczytywanieCzytelnika).

				//Tym razem pobieramy wszystkie kolumny (do wczytania).

				zapytanie = zapytanie = "SELECT * "
					"FROM Czytelnik "
					"WHERE email == '" +
					email + "' AND haslo == '" +
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

				zapytanie = "SELECT * "
					"FROM Bibliotekarz "
					"WHERE email == '" +
					email + "' AND haslo == '" +
					haslo + "';";

				sqlite3_prepare_v2(bazaDanych, zapytanie.c_str(), -1, &stmt, NULL);
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

int Ui::menuPoZalogowaniuCzytelnika(Czytelnik* czytelnik) {

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

void Ui::wyborWMenuCzytelnika(int wybor) {

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

int Ui::menuPoZalogowaniuBibliotekarza(Bibliotekarz* bibliotekarz, Biblioteka* biblioteka, sqlite3* bazaDanych) {

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

void Ui::wyborWMenuBibliotekarza(int wybor, Bibliotekarz* bibliotekarz, Biblioteka* biblioteka, sqlite3* bazaDanych) {

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

Bibliotekarz* Ui::wczytywanieBibliotekarza(sqlite3_stmt* stmt) {

	//Baza danych musi byc otwarta.
	//Do metody przekazuje siê obiekt typu stmt (ju¿ przygotowany, utworzony).
	//Z zalozenia jest to metoda do wykorzystania w metodzie logujacej Bibliotekarza.
	//dlatego tez, wiersze w tabeli Czytelnik sa juz gotowe do odczytu (przygotowanie jest robione w 
	//metodzie logujacej).

	int id = sqlite3_column_int(stmt, 0);
	string imie = ElementyPomocnicze::konwersjaNaString(sqlite3_column_text(stmt, 1));
	string nazwisko = ElementyPomocnicze::konwersjaNaString(sqlite3_column_text(stmt, 2));
	int wiek = sqlite3_column_int(stmt, 3);
	Data dataUrodzenia = ElementyPomocnicze::konwersjaNaData(ElementyPomocnicze::konwersjaNaString(sqlite3_column_text(stmt, 4)));
	string haslo = ElementyPomocnicze::konwersjaNaString(sqlite3_column_text(stmt, 5));
	string email = ElementyPomocnicze::konwersjaNaString(sqlite3_column_text(stmt, 6));
	string telefon = ElementyPomocnicze::konwersjaNaString(sqlite3_column_text(stmt, 7));
	string miasto = ElementyPomocnicze::konwersjaNaString(sqlite3_column_text(stmt, 8));
	string kodPocztowy = ElementyPomocnicze::konwersjaNaString(sqlite3_column_text(stmt, 9));
	string ulica = ElementyPomocnicze::konwersjaNaString(sqlite3_column_text(stmt, 10));
	int numerMieszkania = sqlite3_column_int(stmt, 11);

	Adres adres = Adres(miasto, kodPocztowy, ulica, numerMieszkania);

	Bibliotekarz* bibliotekarz = new Bibliotekarz(imie, nazwisko, email, telefon, dataUrodzenia.getDzien(), dataUrodzenia.getMiesiac(), dataUrodzenia.getRok(), adres, haslo, id);

	return bibliotekarz;
}


void Ui::zmienDaneBibliotekarza(Bibliotekarz* bibliotekarz, sqlite3* bazaDanych) {

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

Biblioteka* Ui::wczytywanieBiblioteki(sqlite3* bazaDanych) {

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

	string emailKontaktowy = ElementyPomocnicze::konwersjaNaString(sqlite3_column_text(stmt, 0));
	string telefonKontaktowy = ElementyPomocnicze::konwersjaNaString(sqlite3_column_text(stmt, 1));
	string miasto = ElementyPomocnicze::konwersjaNaString(sqlite3_column_text(stmt, 2));
	string kodPocztowy = ElementyPomocnicze::konwersjaNaString(sqlite3_column_text(stmt, 3));
	string ulica = ElementyPomocnicze::konwersjaNaString(sqlite3_column_text(stmt, 4));
	int numer = sqlite3_column_int(stmt, 5);
	int iloscEgzemplarzy = sqlite3_column_int(stmt, 6);
	map<string, string> godzinyOtwarcia = Biblioteka::wczytywanieGodzin(bazaDanych);

	Adres adres = Adres(miasto, kodPocztowy, ulica, numer);

	sqlite3_finalize(stmt);

	Biblioteka* biblioteka = new Biblioteka(emailKontaktowy, telefonKontaktowy, adres, godzinyOtwarcia, iloscEgzemplarzy);

	return biblioteka;
}

bool Ui::zarejestruj(int tryb, sqlite3* bazaDanych) {

	//Rejestracja bibliotekarza lub czytelnika w zaleznosci od wybranego trybu.

	if (tryb != 1 && tryb != 2) {
		return false;
	}
	if (bazaDanych == NULL) {
		sqlite3_open("..\\ProjektBiblioteka\\main_db.db", &bazaDanych);
		if (bazaDanych == NULL) {
			return false;
		}
	}
	if (tryb == 1) {
		Osoba* osoba = createUzytkownik(1, bazaDanych);
		if (osoba == NULL) {
			return false;
		}
		Czytelnik* czytelnik = reinterpret_cast<Czytelnik*>(osoba);
		czytelnik->printInfo();

		if (confirmVerification()) {

			if (addUzytkownik(1, bazaDanych, czytelnik)) {
				cout << "Pomyslnie dodano czytelnika." << endl;
				system("pause");
				//Po rejestracji kasuje czytelnika (musi sie nastepnie zalogowac).
				delete czytelnik;
				return true;
			}
			else {
				cout << "Blad przy dodawaniu czytelnika do bazy danych." << endl;
				system("pause");
				delete czytelnik;
				return false;
			}
		}
	}

	else if (tryb == 2) {
		Osoba* osoba = createUzytkownik(2, bazaDanych);
		if (osoba == NULL) {
			return false;
		}
		Bibliotekarz* bibliotekarz = reinterpret_cast<Bibliotekarz*>(osoba);
		bibliotekarz->printInfOBibliotekarzu();

		if (confirmVerification()) {

			if (addUzytkownik(2, bazaDanych, bibliotekarz)) {
				cout << "Pomyslnie dodano bibliotekarza." << endl;
				system("pause");
				delete bibliotekarz;
				return true;
			}
			else {
				cout << "Blad przy dodawaniu bibliotekarza do bazy danych." << endl;
				system("pause");
				delete bibliotekarz;
				return false;
			}
		}
	}
}
