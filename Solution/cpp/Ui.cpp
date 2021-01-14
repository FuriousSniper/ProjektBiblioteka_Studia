#include "..\headers\Ui.h"
#include "..\headers\Person.h"
#include "..\headers\Date.h"
#include "..\headers\Author.h"
#include "..\headers\Reader.h"
#include "..\headers\Adress.h"
#include "..\headers\Library.h"
#include "..\headers\Utilities.h"
#include "..\ProjektBiblioteka\Libraries\sqlite3\sqlite3.h"
#include <string>
#include <exception>
#include <iostream>
#include <regex>


using namespace std;

Adress Ui::createAdress() {

	string city;
	cin.clear();
	cout << "Podaj miasto: ";
	getline(cin, city);
	cin.clear();

	string zipCode;
	cout << "Podaj kod pocztowy: ";
	cin >> zipCode;
	cin.clear();
	cin.ignore(200, '\n');

	string street;
	cout << "Podaj ulice i nr domu Twojego adresu zamieszkania: ";
	getline(cin, street);
	cin.clear();

	cout << "Podaj numer Twojego mieszkania (opcjonalne): ";
	int flatNumber;
	cin >> flatNumber;
	cin.clear();
	cin.ignore(200, '\n');
	Adress adress = Adress(city, zipCode, street, flatNumber);
	return adress;
}

Person Ui::createPerson(sqlite3* bazaDanych) {

	//Ta metoda z zalozenia wykorzystywana jest w metodzie createUzytkownik oraz createAutor.
	//Tworzy obiekt typu Osoba i go zwraca.
	//Nie sprawdza czy baza jest otwarta bo jest to robione w metodzie sprawdzDostepnoscEmail, ktora
	//wykorzystuje ta baze jako jedyna.

	string firstName;
	string LastName;
	int day;
	int month;
	int year;
	string emailAdress;
	string phoneNumber;
	Adress adress;

	system("CLS");
	cout << "Podaj imie: ";
	cin >> firstName;
	cin.clear();
	cin.ignore(200, '\n');
	cout << "Podaj nazwisko: ";
	cin >> LastName;

	do {
		system("CLS");
		cin.clear();
		cin.ignore(200, '\n');
		cout << "Podaj date urodzenia (dd mm rrrr): ";
		cin >> day >> month >> year;
	} while (!cin.good());

	while (true) {

		system("CLS");
		cout << "Podaj swoj email: ";
		cin >> emailAdress;
		cin.clear();
		cin.ignore(200, '\n');

		//Sprawdzenie czy e-mail zawiera @ oraz . w nazwie domeny. (np. @gmail.com).

		if (!validateEmail(emailAdress)) {
			cout << "Niepoprawny format adresu e-mail. Sprobuj ponownie." << endl;
			system("pause");
		}
		else {
			cout << "Powtorz swoj email: ";
			string emailAdress2;
			cin >> emailAdress2;
			cin.clear();
			cin.ignore(200, '\n');

			//Sprawdzanie dostepnosci e-maila, bo moze byc taka sytuacja, ze jest juz zajety.
			//Sprawdza tylko wtedy, gdy wprowadzono 2 identyczne e-maile.

			if (emailAdress == emailAdress2 && checkEmailAvailability(bazaDanych, emailAdress)) {
				cout << "Podaj swoj nr telefonu: ";
				//Wczytuje linie bo moze podac oddzielony spacjami (np. 678 567 456).
				getline(cin, phoneNumber);
				cin.clear();
				break;
			}

			//Gdy wprowadzono 2 identyczne e-maile drukuje odpowiedni komunikat i nastepuje przejscie do kolejnej
			//iteracji w celu wprowadzenia maila ponownie.

			else if (emailAdress == emailAdress2 && !checkEmailAvailability(bazaDanych, emailAdress)) {
				cout << "Email jest juz zajety. Sprobuj ponownie." << endl;
				system("pause");
			}
			else {
				cout << "Podane adresy nie sa zgodne." << endl;
				system("pause");
			}
		}
	}
	adress = createAdress();
	Person person = Person(firstName, LastName, emailAdress, phoneNumber, day, month, year, adress);
	return person;
}

bool Ui::validateEmail(string emailAdress) {

	//Sprawdza poprawnosc email pod katem wystapienia znaku @ oraz . w nazwie domeny.
	const regex format("(\\w+)(\\.|_)?(\\w*)@(\\w+)(\\.(\\w+))+");
	return regex_match(emailAdress, format);
}

bool Ui::checkEmailAvailability(sqlite3* dataBase, string emailAdress) {

	//Metoda sluzaca do sprawdzania dostepnosci e-maila
	//Na wypadek gdyby przekazano zamknieta baze.

	if (dataBase == NULL) {
		//Proba otworzenia bazy.
		sqlite3_open("..\\ProjektBiblioteka\\main_db.db", &dataBase);
		//Jezeli proba sie nie powiodla to nie powodzi sie tez sprawdzanie dostepnosci.
		if (dataBase == NULL) {
			return false;
		}
	}

	//Sprawdzam w obydwu tabelach - Czytelnik i Bibliotekarz. Mozna to zrobic za pomoca jednego zapytania
	//SQL.

	sqlite3_stmt* stmt = NULL;
	string query = "SELECT * FROM Czytelnik WHERE email == '" + emailAdress + "';";
	int retValue1, retValue2;

	sqlite3_prepare_v2(dataBase, query.c_str(), -1, &stmt, NULL);
	//Zapisuje wartosc zwracana przez funkcje do dalszego sprawdzania w warunku.
	retValue1 = sqlite3_step(stmt);
	sqlite3_finalize(stmt);

	query = "SELECT * FROM Bibliotekarz WHERE email == '" + emailAdress + "';";
	sqlite3_prepare_v2(dataBase, query.c_str(), -1, &stmt, NULL);
	retValue2 = sqlite3_step(stmt);
	sqlite3_finalize(stmt);

	//SQLITE_DONE jest zwracane jezeli nie wystapil zaden blad oraz nie ma zadnego wiersza do oczytu.
	//Jezeli nie znaleziono zadnego rekordu o zadanym e-mailu to oznacza to, ze jest wolny.
	//Mozna ewentualnie dodac rozpatrywanie przypadkow - co sie dzieje w przypadku bledu a co w przypadku
	//SQLITE_ROW. Na razie jest to ujednolicone i zwraca false.

	if (retValue1 == SQLITE_DONE && retValue2 == SQLITE_DONE) {
		return true;
	}
	else {
		return false;
	}
}

Author Ui::createAuthor(sqlite3* dataBase) {
	cout << "Tworzenie nowego Autora" << endl;
	Person person = createPerson(dataBase);
	//Autor dziedziczy po Osobie, wiec tworzymy obiekt osoba i przepisujemy wartosci. da sie to zrobic prosciej przypisujac obiekt zamiast poszczegolnych skladowych, ale na razie to nie jest istotne
	Author author = Author(person.getFirstName(), person.getLastName(), person.getBirthDate().getDay(), person.getBirthDate().getMonth(), person.getBirthDate().getYear());
	cout << "Pomyslnie utworzono: Autor" << endl;
	return author;
}

string Ui::createPasswordWindow() {

	string password1;
	string password2;

	while (true) {
		cout << "Podaj haslo do swojego konta: ";
		cin >> password1;
		cin.clear();
		cin.ignore(200, '\n');
		cout << "Potwierdz haslo do swojego konta: ";
		cin >> password2;
		cin.clear();
		cin.ignore(200, '\n');
		if (password1 == password2) {
			return password1;
		}
		else {
			cout << "Hasla nie sa zgodne! Sprobuj ponownie.\n";
		}
	}
}

Person* Ui::createUser(int mode, sqlite3* dataBase) {

	//Tworzenie czytelnika/bibliotekarza w zaleznosci od wybranego trybu.

	if (dataBase == NULL) {
		sqlite3_open("..\\ProjektBiblioteka\\main_db.db", &dataBase);
		if (dataBase == NULL) {
			return NULL;
		}
	}
	if (mode != 1 && mode != 2) {
		return NULL;
	}

	sqlite3_stmt* stmt = NULL;
	int temp = -1;

	//W zaleznosci od trybu przygotowuje odpowienie zapytanie.

	if (mode == 1) {
		cout << "Tworzenie czytelnika." << endl;
		sqlite3_prepare_v2(dataBase, "select MAX(ID) from CZYTELNIK", -1, &stmt, NULL);
	}
	else if (mode == 2) {
		cout << "Tworzenie bibliotekarza." << endl;
		sqlite3_prepare_v2(dataBase, "select MAX(ID) from BIBLIOTEKARZ", -1, &stmt, NULL);
	}

	//Jezeli tabela zawiera jakies rekordy to pobierz Id.

	if (sqlite3_step(stmt) == SQLITE_ROW) {
		temp = sqlite3_column_int(stmt, 0);
	}
	temp++;

	//Tworzenie obiektu pomocniczego osoba.
	Person person = createPerson(dataBase);
	//Okno tworzenia hasla dla osoby.
	string password = createPasswordWindow();

	//W zaleznosci od wybranego trybu tworzenie czytelnika lub bibliotekarza.
	if (mode == 1) {
		Reader* reader = new Reader(person.getFirstName(), person.getLastName(), person.getEmailAdress(), person.getPhoneNumber(), person.getBirthDate().getDay(), person.getBirthDate().getMonth(), person.getBirthDate().getYear(), person.getAdress(), password, temp);
		return reader;
	}
	else if (mode == 2) {
		Librarian* librarian = new Librarian(person.getFirstName(), person.getLastName(), person.getEmailAdress(), person.getPhoneNumber(), person.getBirthDate().getDay(), person.getBirthDate().getMonth(), person.getBirthDate().getYear(), person.getAdress(), password, temp);
		return librarian;
	}
}

bool Ui::addUserToDataBase(int mode, sqlite3* dataBase, Person* person) {

	//Metoda dodajaca uzytkownika (czytelnika/biblitotekarza) do bazy danych w zaleznosci od wybranego trybu.

	if (mode != 1 && mode != 2 || person == NULL) {
		return false;
	}

	if (dataBase == NULL) {
		sqlite3_open("main_db.db", &dataBase);
		if (dataBase == NULL) {
			return false;
		}
	}

	string query;
	char* error;

	//Dodawanie czytelnika lub biblitekarza w zaleznosci od trybu.

	if (mode == 1) {

		//Wartaloby sprawdzic przypadek, gdy przekaze do funkcji wskaznik na bibliotekarza (Bibliotekarz*).
		Reader* reader = reinterpret_cast<Reader*>(person);

		query = "INSERT INTO CZYTELNIK"
			"(listaZaleglosci,dataPierwszegoWypozyczenia,iloscWypozyczonychOdDolaczenia,preferowaneTematy,"	"dataDolaczenia,miasto,kodPocztowy,ulica,imie,nazwisko,wiek,dataUrodzenia,haslo,numerMieszkania,"
			"email,telefon)"
			" VALUES ("
			"	'',"
			"	'',"
			"	0,"
			"	'',"
			"	DATE(),'" +
			reader->getAdress().getCity() + "','" +
			reader->getAdress().getZipCode() + "','" +
			reader->getAdress().getStreet() + "','" +
			reader->getFirstName() + "','" +
			reader->getLastName() + "','" +
			to_string(reader->getAge()) + "','" +
			to_string(reader->getBirthDate().getDay()) + "-" +
			to_string(reader->getBirthDate().getMonth()) + "-" +
			to_string(reader->getBirthDate().getYear()) + "','" +
			reader->getPassword() + "','" +
			to_string(reader->getAdress().getFlatNumber()) + "','" +
			reader->getEmailAdress() + "','" +
			reader->getPhoneNumber() + "'"
			"	);";
	}
	else if (mode == 2) {

		//Wartaloby sprawdzic przypadek, gdy przekaze do funkcji wskaznik na czytelnika (Czytelnik*).
		Librarian* librarian = reinterpret_cast<Librarian*>(person);

		query = "INSERT INTO BIBLIOTEKARZ"
			"(imie, nazwisko, wiek,"
			"dataUrodzenia, haslo, email, telefon, miasto, kodPocztowy, ulica, numerMieszkania)"
			" VALUES ('" +
			librarian->getFirstName() + "','" +
			librarian->getLastName() + "'," +
			to_string(librarian->getAge()) + ",'" +
			to_string(librarian->getBirthDate().getDay()) + "-" +
			to_string(librarian->getBirthDate().getMonth()) + "-" +
			to_string(librarian->getBirthDate().getYear()) + "','" +
			librarian->getPassword() + "','" +
			librarian->getEmailAdress() + "','" +
			librarian->getPhoneNumber() + "','" +
			librarian->getAdress().getCity() + "','" +
			librarian->getAdress().getZipCode() + "','" +
			librarian->getAdress().getStreet() + "','" +
			to_string(librarian->getAdress().getFlatNumber()) + "');";
	}

	//Wykonaj zapytanie.
	sqlite3_exec(dataBase, query.c_str(), NULL, NULL, &error);

	//Ewentualnie wyswietla blad.
	if (error != SQLITE_OK) {
		cout << "Wystapil blad: " << error << endl;
		return false;
	}
	return true;
}

int Ui::signInUpMenu() {
	int choice = 0;
	while (true) {
		system("CLS");
		cout << "System obslugi Biblioteki (v. alfa 0.1)\n";
		cout << "Wybierz '1', aby sie zalogowac." << endl;
		cout << "Wybierz '2', aby sie zarejestrowac." << endl;
		cout << "Wybierz '9', aby wyjsc z programu." << endl;
		cout << "Wybor: ";
		cin >> choice;
		if (choice == 9) {
			cout << "Zakonczono prace programu" << endl;
			return 0;
		}
		else if (choice == 1 || choice == 2) {
			break;
		}
		else {
			cin.clear();
			cin.ignore(1024, '\n');
		}
	}
	return choice;
}
int Ui::chooseUserType() {
	int choice = 0;
	while (true) {
		system("CLS");
		cout << "System obslugi Biblioteki (v. alfa 0.1)\n";
		cout << "Wybierz '1', aby zalogowac sie na konto Czytelnika." << endl;
		cout << "Wybierz '2', aby zalogowac sie na konto Bibliotekarza." << endl;
		cout << "Wybierz '3', aby powrocic do menu glownego." << endl;
		cout << "Wybierz '9', aby wyjsc z programu." << endl;
		cout << "Wybor: ";
		cin >> choice;
		if (choice == 9) {
			cout << "Zakonczono prace programu" << endl;
			return 0;
		}
		else if (choice == 1 || choice == 2 || choice == 3) {
			break;
		}
		else {
			cin.clear();
			cin.ignore(1024, '\n');
		}
	}
	return choice;
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
	//funkcja dodajaca ksiazke do biblioteki.
	//po callu wymagane jest wpisanie tytulu i kategorii, aby dodac ksiazke

	system("CLS");
	cout << "Dodawanie ksiazki" << endl;

	string title = "";
	string authors = "";
	string tags = "";
	string category = "";
	string ex = "";
	string dmr;

	cout << "Podaj tytul\nTytul: ";
	//uzywam getline, zeby pozwolic na spizywanie titleow ze spacjami.
	getline(cin, title);
	cout << "Podaj autorow. Jesli wielu, wpisywac ze znakami specjalnymi \" || \" pomiedzy. Przyklad: \"Sasha Kostylev || Niko Kovac\" \nAutorzy: ";
	getline(cin, authors);
	cout << "Podaj tagi. Jesli kilka, wpisywac ze znakami specjalnymi \" || \" pomiedzy.\nTagi: ";
	getline(cin, tags);
	cout << "Podaj kategorie\nKategoria: ";
	getline(cin, category);
	cout << "Podaj numery ISBN egzemplarzy. Jesli kilka, wpisywac ze znakami specjalnymi \" || \" pomiedzy. Przyklad: 978-83-246-3342-5||978-83-61040-85-9\nNumery: ";
	getline(cin, ex);
	cout << "Podaj date wydania (dd-mm-rrrr): ";
	getline(cin, dmr);
	if (title != "" && category != "") {
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
		if (authors.find("||") != string::npos) {
			string delimit = "||";
			vector<string> autors_splitted = Utilities::splitString(authors, delimit);
			for (int i = 0; i < autors_splitted.size(); i++) {
				//metoda sprawdzajaca czy autor istnieje i dodaje go/updatuje jego ksiazki
				addAuthor3(autors_splitted[i], title);
			}
		}
		else
			addAuthor3(authors, title);
		string sql2;
		sql2 = "INSERT INTO KSIAZKA (tytul,autorzy,tagi,kategoria,egzemplarze,dataPremiery) "
			"VALUES ('" +
			title + "','" +
			authors + "','" +
			tags + "','" +
			category + "','" +
			ex + "','" +
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
		if (ex != "") {
			vector<string> splittedString;
			string delimeter = "||";

			splittedString = Utilities::splitString(ex, delimeter);
			//dla kazdego egzemplarza wywolywana jest funkcja dodajaca go do bazy danych
			for (int i = 0; i < splittedString.size(); i++) {
				cout << "Dodawanie egzemplarza ksiazki o isbn " << splittedString[i];
				addCopy2(splittedString[i], title);
				system("CLS");
			}
		}
	}
	else {
		cout << "Pola \'tytul\' i \'kategoria\' nie moga byc puste!" << endl;
		return -1;
	}
}
int Ui::getBooks(Reader r,int mode) {

	//Dla mode == 1 - wypisanie ksiazek dla bibliotekarza.
	//Dla mode == 2 - wypisanie ksiazek dla czytelnika (dodatkowo umozliwia wypozyczenie ksiazki i inne operacje).

	//metoda pozwalajaca na wypisanie wszystkich ksiazek znajdujacych sie w bazie

	if (mode != 1 && mode != 2) {
		return -1;
	}

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

		//Jezeli jest czytelnikiem (mode == 1) do daje mozliwosc wypozyczenia i innych operacji.

		if (mode == 2) {
			return 1;
		}

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
			lendBook(r, opt);
		}
	}
	sqlite3_finalize(stmt);
}
int Ui::getBooks2(Librarian r, int mode) {

	//Dla mode == 1 - wypisanie ksiazek dla bibliotekarza.
	//Dla mode == 2 - wypisanie ksiazek dla czytelnika (dodatkowo umozliwia wypozyczenie ksiazki i inne operacje).

	//metoda pozwalajaca na wypisanie wszystkich ksiazek znajdujacych sie w bazie

	if (mode != 1 && mode != 2) {
		return -1;
	}

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

		//Jezeli jest czytelnikiem (mode == 1) do daje mozliwosc wypozyczenia i innych operacji.

		if (mode == 2) {
			return 1;
		}

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
		}
	}
	sqlite3_finalize(stmt);
}
int Ui::getNumberOfLentBooks(Reader reader) {
	//funkcja do zliczania ilosci wypozyczonych ksiazek przez czytelnika

	sqlite3* db;
	sqlite3_stmt* stmt;
	//Czytelnik c jest zalogowanym czytelnikiem, wiec pola, ktorych uzywamy w getterach sa w pamieci.
	string query = "SELECT ksiazka1, ksiazka2, ksiazka3 from CZYTELNIK WHERE imie='" + reader.getFirstName() + "' AND nazwisko='" + reader.getLastName() + "';";
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
int Ui::getSpecificUserBook(Reader reader, string isbn) {
	//metoda sprawdzajaca, czy czytelnik wypozyczyl ksiazke podana w argumencie i jesli tak, to zwraca, w ktorej kolumnie jest ona zapisana

	sqlite3* db;
	sqlite3_stmt* stmt;
	//Czytelnik c jest zalogowanym czytelnikiem, wiec pola, ktorych uzywamy w getterach sa w pamieci.
	string query = "SELECT ksiazka1, ksiazka2, ksiazka3 from CZYTELNIK WHERE imie='" + reader.getFirstName() + "' AND nazwisko='" + reader.getLastName() + "';";
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
	cout << "Czytelnik " << reader.getFirstName() << " " << reader.getLastName() << " nie wypozyczyl takiej ksiazki!" << endl;
	return -1;
}
int Ui::lendBook(Reader reader, string title) {
	//metoda do wypozyczania ksiazek. jako argumenty przyjmuje obiekt zalogowanego czytelnika oraz tytul wypozyczanej ksiazki. zwraca wartosc odpowiadajaca kodowi bledu (1 - sukces), (-1 - blad)

	int l = getNumberOfLentBooks(reader);
	if (l < 3) {
		sqlite3* db;
		sqlite3_stmt* stmt;
		char* error;
		//Czytelnik c jest zalogowanym czytelnikiem, wiec pola, ktorych uzywamy w getterach sa w pamieci.
		string query = "SELECT ksiazka1, ksiazka2, ksiazka3 from CZYTELNIK WHERE imie='" + reader.getFirstName() + "' AND nazwisko='" + reader.getLastName() + "';";
		//zmienna, w ktorej zapisujemy wolna kolumne
		int counter = 1;
		sqlite3_open("main_db.db", &db);
		if (db == NULL)
		{
			printf("Blad przy otwieraniu bazy danych\n");
			return -1;
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
		string isbn = checkCopiesList(title);
		//jesli nie, to zwracamy bledy
		if (isbn == "false") {
			cout << "Ksiazka o tym tytule nie znajduje sie w bazie" << endl;
			sqlite3_close(db);
			return -1;
		}
		if (isbn == "NOT_AVAILABLE") {
			cout << "Wszystkie ksiazki o tym tytule zostaly wypozyczone" << endl;
			sqlite3_close(db);
			return -1;
		}

		//updatujemy row, czyli konkretniej - kolumne gdzie zapisujemy nowo wypozyczona ksiazke danego czytelnika
		query = "UPDATE CZYTELNIK SET ksiazka" + to_string(counter) + "='" + isbn + "' WHERE imie='" + reader.getFirstName() + "' AND nazwisko='" + reader.getLastName() + "';";
		int rc = sqlite3_exec(db, query.c_str(), NULL, NULL, &error);
		if (rc != SQLITE_OK) {
			cout << error << endl;
			sqlite3_free(error);
			return -1;
		}

		//koniecznie - updatujemy wypozyczany egzemplarz. zmieniamy date wypozyczenia oraz osobe
		query = "UPDATE EGZEMPLARZE SET osobaWyp='" + reader.getFirstName() + " " + reader.getLastName() + "', dataWyp=(DATETIME('now')), dataOdd=(DATETIME('now','+1 month')) WHERE numerISBN='" + isbn + "';";
		rc = sqlite3_exec(db, query.c_str(), NULL, NULL, &error);
		if (rc != SQLITE_OK) {
			cout << error << endl;
			sqlite3_free(error);
			sqlite3_close(db);
			return -1;
		}
		std::cout << "Wypozyczono" << std::endl;
		system("pause");
		sqlite3_close(db);
		//sukces, zwracamy 1
		return 1;
	}
	else
		//zwracamy blad, bo user nie moze wypozyczyc wiecej niz 3 ksiazek
		cout << "Czytelnik wypozyczyl maksymalna ilosc ksiazek" << endl;
	return -1;
}
int Ui::returnBook(Reader reader, string isbnNumber) {
	//metoda pozwalajaca na wyswietlenie ksiazek wypozyczonych przez czytelnika c

	string name = reader.getFirstName();
	string surname = reader.getLastName();
	sqlite3* db;
	sqlite3_stmt* stmt;
	string query;
	char* error;
	//zmienna, ktora ustawiamy, w zaleznosci od poprawnosci numeru isbn zwracanej ksiazki
	bool exists = false;

	//sprawdzanie, czy ksiazka jest wypozyczona przez usera i jesli tak, to zwraca kolumne w tabeli, w ktorej ksiazka jest umieszczona
	int user_book_column = getSpecificUserBook(reader, isbnNumber);

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
		query = "UPDATE EGZEMPLARZE SET dataWyp='', dataOdd='', osobaWyp='' WHERE numerISBN='" + isbnNumber + "';";
		sqlite3_exec(db, query.c_str(), NULL, NULL, &error);
		if (error != SQLITE_OK) {
			cout << "blad: " << error << endl;
			system("pause");
			sqlite3_close(db);
			return -1;
		}
		//updatowanie czytelnika
		query = "UPDATE CZYTELNIK SET ksiazka" + to_string(user_book_column) + "='' WHERE imie='" + name + "' AND nazwisko='" + surname + "' ;";
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
int Ui::getUserBooks(Reader reader) {
	//metoda do zwracania ksiazek. Czytelnik c - zalogowany czytelnik. pobieramy z niego imie i nazwisko potrzebne do zwracania.
	//isbn - nr ksiazki do zwrocenia

	string name = reader.getFirstName();
	string surname = reader.getLastName();
	sqlite3* db;
	sqlite3_stmt* stmt;
	char* error;

	sqlite3_open("main_db.db", &db);
	if (db == NULL)
	{
		printf("Blad przy otwieraniu bazy danych\n");
		return -1;
	}
	//numery isbn ksiazek, ktore czytelnik wypozyczyl. pobierane z tabeli CZYTELNIK w bazie danych z kolumn ksiazka1, ksiazka2, ksiazka3
	string k1 = "";
	string k2 = "";
	string k3 = "";
	string query;
	query = "SELECT ksiazka1, ksiazka2, ksiazka3 from CZYTELNIK WHERE imie='" + name + "' AND nazwisko='" + surname + "';";
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
	cout << "Ksiazki Czytelnika " << name << " " << surname << ": " << endl;
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
	sqlite3_close(db);
	return 1;
}
int Ui::addCopy1() {
	//metoda dodajaca egzemplarz danej ksiazki do bazy danych

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
	string amount;
	string isbn;
	string ph;
	string title;
	string query;

	cout << "Podaj ilosc stron\nIlosc stron: ";
	getline(cin, amount);
	cout << "Podaj numer ISBN \nNumer ISBN: ";
	getline(cin, isbn);
	cout << "Podaj wydawnictwo \nWydawnictwo: ";
	getline(cin, ph);
	cout << "Podaj tytul \nTytul: ";
	getline(cin, title);

	query = "INSERT INTO EGZEMPLARZE(iloscStron,numerISBN,wydawnictwo,osobaWyp,dataWyp,dataOdd,przedluzony,przetrzymany,ksiazka) "
		"VALUES(" +
		amount + "," +// ilosc stron
		"'" + isbn + "'," + //isbn
		"'" + ph + "'," + //wydawnictwo
		"''," + //osoba wypozyczajaca
		"''," + //data wypozyczenia
		"''," + //data oddania
		"0," + //przedluzony
		"0," + //przetrzymany
		"'" + title + "' " + //tytul
		");";
	sqlite3_exec(db, query.c_str(), NULL, NULL, &error);
	if (error != SQLITE_OK) {
		cout << "blad: " << error << endl;
		system("pause");
		sqlite3_close(db);
		return -1;
	}
	sqlite3_close(db);
	return 1;

}
int Ui::addCopy2(string isbnNumber, string title) {
	//metoda dodajaca egzemplarz danej ksiazki do bazy danych. jako parametr przyjmuje nr isbn dodawanej ksiazki, co pozwala na uproszczenie funkcji dodawania ksiazek.

	sqlite3* db;
	char* error;
	sqlite3_open("main_db.db", &db);
	if (db == NULL)
	{
		printf("Blad przy otwieraniu bazy danych\n");
		return -1;
	}
	string amount;
	string ph;
	string query;

	cout << "\nPodaj ilosc stron\nIlosc stron: ";
	getline(cin, amount);
	cout << "Podaj wydawnictwo \nWydawnictwo: ";
	getline(cin, ph);
	query = "INSERT INTO EGZEMPLARZE(iloscStron,numerISBN,wydawnictwo,osobaWyp,dataWyp,dataOdd,przedluzony,przetrzymany,ksiazka) "
		"VALUES(" +
		amount + "," +// ilosc stron
		"'" + isbnNumber + "'," + //isbn
		"'" + ph + "'," + //wydawnictwo
		"''," + //osoba wypozyczajaca
		"''," + //data wypozyczenia
		"''," + //data oddania
		"0," + //przedluzony
		"0," + //przetrzymany
		"'" + title + "' " + //tytul
		");";

	sqlite3_exec(db, query.c_str(), NULL, NULL, &error);
	if (error != SQLITE_OK) {
		cout << "blad: " << error << endl;
		system("pause");
		sqlite3_close(db);
		return -1;
	}
	cout << "Dodano egzemplarz do bazy" << endl;
	sqlite3_close(db);
	return 1;
}
int Ui::getAuthor() {
	//metoda pozwalajaca na dodawanie nowego autora (od zera)

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
	string name;
	string surname;
	string dmr = "1-1-1";
	string query;


	cout << "Podaj imie autora\nImie: ";
	getline(cin, name);
	cout << "Podaj nazwisko autora\nNazwisko: ";
	getline(cin, surname);


	query = "INSERT INTO AUTOR(imie,nazwisko,dataUrodzenia,ksiazki) "
		"VALUES('" +
		name + "','" + //imie
		surname + "','" + //nazwisko
		dmr + "','" + //data urodzenia (niepotrzebna, wiec ustawiona na 1-1-1
		"'" +
		");";
	sqlite3_exec(db, query.c_str(), NULL, NULL, &error);
	if (error != SQLITE_OK) {
		cout << "blad: " << error << endl;
		system("pause");
		sqlite3_close(db);
		return -1;
	}
	cout << "Dodano nowego autora do bazy danych" << endl;
	sqlite3_close(db);
	return 1;
}
int Ui::getAuthor2(string firstName, string title) {
	//dodawanie nowego autora od zera. parametry - imie oraz tytul ksiazki, ktora autor napisal

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
	//delimiter, do podzialu na imie i nazwisko autora
	string d = " ";
	vector<string> sp = Utilities::splitString(firstName, d);
	string name2 = sp[0];
	string surname = sp[1];
	string dmr = "1-1-1";
	string query;

	query = "INSERT INTO AUTOR(imie,nazwisko,dataUrodzenia,ksiazki) "
		"VALUES('" +
		name2 + "','" + //imie
		surname + "','" + //nazwisko
		dmr + "','" + //data urodzenia
		title + "'" +	//ksiazka
		");";
	sqlite3_exec(db, query.c_str(), NULL, NULL, &error);
	if (error != SQLITE_OK) {
		cout << "blad: " << error << endl;
		system("pause");
		return -1;
	}
	cout << "Dodano nowego autora i przypisano ksiazke" << endl;
	sqlite3_close(db);
	system("PAUSE");
	return 1;
}
int Ui::addAuthor3(string firstName, string title) {
	//aktualizacja, dodawanie nowego autora, sprawdzanie czy taki istnieje, dopisywanie ksiazek
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
	vector<string> sp = Utilities::splitString(firstName, d);
	string name2 = sp[0];
	string surname = sp[1];
	string query;
	//zmienna, za pomoa ktorej sprawdzamy istnienie autora i wykonanie odpowiednych przypadkow
	bool exists = false;

	query = "SELECT EXISTS(SELECT 1 from AUTOR WHERE imie='" + name2 + "' AND nazwisko='" + surname + "' LIMIT 1);";
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
		query = "SELECT ksiazki from AUTOR WHERE imie='" + name2 + "' AND nazwisko='" + surname + "';";

		//zmienna do ktorej tymczasowo wpisujemy wynik powyzszej kwerendy
		string books = "";
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
					books = string(reinterpret_cast<const char*>((sqlite3_column_text(stmt2, i))));
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
		if (books == "") {
			to_update = title;
		}
		else {
			//splitujemy ksiazki autora pobrane z bazy
			string d2 = "||";
			vector<string> books_split = Utilities::splitString(books, d2);

			//forem sprawdzamy, czy taka ksiazka nie jest juz do autora przypisana
			for (int i = 0; i < books_split.size(); i++) {
				if (books_split[i] == title) {
					cout << "Ksiazka jest juz dopisana do autora" << endl;
					return -1;
				}
			}
			to_update = books + "||" + title;
		}
		//updatujemy rekord wstawiajac zmienna to_update do kolumny "ksiazka"
		query = "UPDATE AUTOR SET ksiazki='" + to_update + "' WHERE imie='" + name2 + "' AND nazwisko='" + surname + "';";
		sqlite3_exec(db, query.c_str(), NULL, NULL, &error);
		if (error != SQLITE_OK) {
			cout << "blad: " << error << endl;
			system("pause");
			sqlite3_close(db);
			return -1;
		}
		cout << "Przypisano ksiazke do autora" << endl;
		sqlite3_close(db);
		return 1;
	}

	else {
		//autor nie istnieje, wiec go dodajemy i przypisujemy mu ksiazke
		getAuthor2(firstName, title);
		sqlite3_close(db);
		//cout << "dodano i powracamy" << endl;
		return 1;
	}
}
string Ui::checkCopiesList(string title) {
	//metoda do sprawdzania, czy jakies egzemplarze ksiazki da sie wypozyczyc. parametr - tytul ksiazki do sprawdzenia. zwraca nr isbn egzemplarza gotowego do wypozyczenia

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
	string ex;
	//zmienna, ktora zwracamy. defaultowo ustawiamy "kod" bledu jako NOT_AVAILABLE
	string to_return = "NOT_AVAILABLE";
	query = "SELECT egzemplarze from KSIAZKA WHERE tytul='" + title + "' LIMIT 1;";
	sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, NULL);
	bool done = false;
	int row = 0;

	//pobranie egzemplarzy ksiazki z tabeli
	while (!done) {
		switch (sqlite3_step(stmt)) {
		case SQLITE_ROW:
			for (int i = 0; i < sqlite3_column_count(stmt); i++) {
				ex = string(reinterpret_cast<const char*>((sqlite3_column_text(stmt, i))));
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
	vector<string> split_ex = Utilities::splitString(ex, delimit_1);

	//dla kazdego spradzamy dostepnosc
	for (int i = 0; i < split_ex.size(); i++) {
		sqlite3_stmt* stmt2;
		query = "SELECT dataWyp from EGZEMPLARZE WHERE numerISBN='" + split_ex[i] + "' LIMIT 1;";

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
						to_return = split_ex[i];
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
	sqlite3_close(db);
	return to_return;
}



Person* Ui::logIn(int mode, sqlite3* dataBase) {

	//mode == 1 - logowanie czytelnika
	//mode == 2 - logowanie bibliotekarza

	if (dataBase == NULL) {
		sqlite3_open("..\\ProjektBiblioteka\\main_db.db", &dataBase);
		if (dataBase == NULL) {
			return NULL;
		}
	}

	while (true) {

		system("CLS");

		string emailAdress;
		string password;
		int retValue;      //Do przypisania wartosci zwracanej przez funkcje sqlite3_step(...).

		cout << "Logowanie do systemu biblioteki." << endl;
		cout << "Podaj adres e-mail konta: ";
		cin >> emailAdress;
		cin.clear();
		cin.ignore(200, '\n');
		cout << "Podaj haslo: ";
		cin >> password;
		cin.clear();
		cin.ignore(200, '\n');

		string query;     //zapytanie sql

		//Jedyna roznica w logowaniu bibliotekarza i czytelnika jest zapytanie.

		if (mode == 1) {
			query = "SELECT imie, nazwisko, haslo "
				"FROM Czytelnik "
				"WHERE email == '" +
				emailAdress + "' AND haslo == '" +
				password + "';";
		}
		else if (mode == 2) {
			query = "SELECT imie, nazwisko, haslo "
				"FROM Bibliotekarz "
				"WHERE email == '" +
				emailAdress + "' AND haslo == '" +
				password + "';";
		}

		sqlite3_stmt* stmt = NULL;
		sqlite3_prepare_v2(dataBase, query.c_str(), -1, &stmt, NULL);
		retValue = sqlite3_step(stmt);
		sqlite3_finalize(stmt);

		//SQLITE_ROW jest zwracane przez sqlite3_step(...) jezeli jest dostepny wiersz do odczytu.
		//Zakladam, ze w bazie nie moze byc jednoczesnie dwoch rekordow o takich samych: emailu i hasle

		//Czyli nie moze zajsc taka sytuacja, ze w tabeli sa dwa rekordy:
		//Rekord 1: email = roj@gmail.com haslo = admin
		//Rekord 2: email = roj@gmail.com haslo = admin

		if (retValue == SQLITE_ROW) {

			//Jest dostepny wiersz do oczytu czyli czytelnik znajduje sie w bazie.

			cout << "Pomyslnie zalogowano!" << endl;

			if (mode == 1) {
				query = "SELECT * "
					"FROM Czytelnik "
					"WHERE email == '" +
					emailAdress + "' AND haslo == '" +
					password + "';";

				Reader* reader = loadReader(dataBase, query);
				system("pause");
				return reader;
			}
			else if (mode == 2) {

				//Metoda wczytywanieBibliotekarza zwraca wskaznik na obiekt dynamiczny typu Bibliotekarz utworzony na
				//podstawie zawartosci rekordu.

				query = "SELECT * "
					"FROM Bibliotekarz "
					"WHERE email == '" +
					emailAdress + "' AND haslo == '" +
					password + "';";

				Librarian* librarian = loadLibrarian(dataBase, query);
				system("pause");
				return librarian;
			}
		}
		else {

			int choice = -1;

			//Jezeli logowanie sie nie powiodlo tj. SQLITE_ROW nie zostalo zwrocone przez funkcje (z roznego powodu),
			//sygnalizujemy wystapienie problemu i oferujemy mozliwosc ponownego logowania.

			//Przyczyna niepowodzenia logowania moze byc np. brak czytelnika w bazie danych, czyli wymagana jest
			//rejestracja.

			cout << "Logowanie sie nie powiodlo. Mozliwe ze uzytkownik o podanych danych nie istnieje." << endl;
			cout << "Jezeli chcesz wrocic do menu glownego wybierz 0." << endl;
			cout << "Jezeli chcesz sprobowac zalogowac sie ponownie, wybierz liczbe inna niz 0: ";
			cin >> choice;
			cin.clear();
			cin.ignore(200, '\n');
			if (choice == 0) {
				return NULL;
			}
		}
	}
}

int Ui::readerMenu(Reader* reader, Library*library, sqlite3*dataBase) {

	//Proste menu wyswietlane po zalogowaniu.
	//Po wyborze umozliwia dalsze operacje np. wypozyczenie ksiazki, aktualizacja danych itd.

	while (true) {
		system("CLS");
		int choice = 0;
		cout << "Wprowadz odpowiednia liczbe aby kontynuowac." << endl;
		cout << "1: Wyswietl dane o bibliotece" << endl;
		cout << "2: Wyswietl dane o koncie" << endl;
		cout << "3: Wyswietl liste dostepnych ksiazek." << endl;
		cout << "4: Wyswietl liste wypozyczonych ksiazek." << endl;
		cout << "5: Wypozycz ksiazke." << endl;
		cout << "6: Oddaj ksiazke." << endl;
		cout << "0: Wyloguj i wroc do menu glownego." << endl;
		cout << "Wybor: ";
		cin >> choice;
		cin.clear();
		cin.ignore(200, '\n');

		if (choice == 0) {
			return 0;
		}
		readerMenuChoice(choice, reader, library, dataBase);
	}
}

void Ui::readerMenuChoice(int choice, Reader* reader, Library* library, sqlite3* dataBase) {

	//Wyswietla odpowiednie informacje w zaleznosci od wyboru w menu czytelnika po zalogowaniu.
	//Wybor pozwala na wykonywanie odpowiednich czynnosci np. zmiana danych konta, wypozyczenie/oddanie ksiazki.

	system("CLS");
	switch (choice) {
	case 1:
	{
		library->printLibraryInfo();
		cout << endl;
		cout << "Nie posiadasz uprawnien do zmiany tych danych." << endl;
		break;
	}
	case 2:
	{
		cout << "Dane o koncie." << endl;
		reader->printReaderInfo();
		cout << endl;
		int choice1;
		cin.clear();
		cout << "Aby zmienic dane wprowadz 1. Inaczej wprowadz dowolna liczbe poza 1." << endl;
		cout << "Wybor: ";
		cin >> choice1;
		cin.clear();
		cout << endl;
		if (choice1 == 1) {
			changeUserData(1, reader, dataBase);
		}
		break;
	}
	case 3:
	{
		//Lista ksiazek dostepnych w bibliotece
		getBooks(*reader,1);
		break;
	}
	case 4:
	{
		//Lista ksiazek wypozyczonych przez czytelnik (max 3).
		getUserBooks(*reader);
		break;
	}
	case 5:
	{
		//Wypozyczanie ksiazek przez czytelnika.
		getBooks(*reader, 1);
		string titleInput;
		cout << "Podaj tytul ksiazki do wypozyczenia: ";
		getline(cin, titleInput);
		cin.clear();
		lendBook(*reader, titleInput);
		break;
	}
	case 6:
	{
		//Zwracanie ksiazek przez czytelnika.
		getUserBooks(*reader);
		string isbnNumber;
		cout << "Podaj numer ISBN ksiazki, ktora chcesz zwrocic: ";
		getline(cin, isbnNumber);
		cin.clear();
		returnBook(*reader, isbnNumber);
		break;
	}
	default:
		cout << "Niewlasciwa opcja. Sprobuj ponownie" << endl;
		break;
	}
	system("pause");
}

int Ui::librarianMenu(Librarian* librarian, Library* library, sqlite3* dataBase) {

	//Proste menu wyswietlane po zalogowaniu bibliotekarza.
	//Po wyborze umozliwia dalsze operacje np. sprawdzenie rejestru spoznien.

	while (true) {

		system("CLS");
		int choice = 0;
		cout << "Wprowadz odpowiednia liczbe aby kontynuowac" << endl;
		cout << "1: Wyswietl dane o bibliotece" << endl;
		cout << "2: Wyswietl dane o koncie" << endl;
		cout << "3: Wyswietl liste dostepnych ksiazek" << endl;
		cout << "4: Dodaj ksiazke do biblioteki" << endl;
		cout << "0: Wyloguj i wroc do menu glownego" << endl;
		cout << "Wybor: ";
		cin >> choice;
		cin.clear();
		cin.ignore(200, '\n');

		if (choice == 0) {
			return 0;
		}
		librarianMenuChoice(choice, librarian, library, dataBase);
	}
}

void Ui::librarianMenuChoice(int choice, Librarian* librarian, Library* library, sqlite3* dataBase) {

	//Wyswietla odpowienie informacje w zaleznosci od wyboru w menu.
	//Wybor odpowiedniej opcji w menu pozwala rowniez dokonac roznych akcji np. wyslanie powiadomienia
	//o zaleganiu z oddanie ksiazek.

	system("CLS");
	switch (choice) {
	case 1:
	{
		library->printLibraryInfo();
		cout << endl;
		cout << "Nie posiadasz uprawnien do zmiany tych danych." << endl;
		break;
	}
	case 2:
	{
		cout << "Dane o koncie." << endl;
		librarian->printLibrarianInfo();
		cout << endl;
		int choice1;
		cin.clear();
		cout << "Aby zmienic dane wprowadz 1. Inaczej wprowadz dowolna liczbe poza 1." << endl;
		cout << "Wybor: ";
		cin >> choice1;
		cin.clear();
		cout << endl;
		if (choice1 == 1) {
			changeUserData(2,librarian, dataBase);
		}
		break;
	}
	case 3:
	{
		getBooks2(*librarian,2);
		break;
	}
	case 4:
	{
		addBook();
		break;
	}
	default:
	{
		cout << "Niewlasciwa opcja. Sprobuj ponownie" << endl;
		break;
	}
	}
	system("pause");
}

Librarian* Ui::loadLibrarian(sqlite3* dataBase, string query) {

	//Baza danych musi byc otwarta.
	//Do metody przekazuje siê obiekt typu stmt (ju¿ przygotowany, utworzony).
	//Z zalozenia jest to metoda do wykorzystania w metodzie logujacej Bibliotekarza.
	//dlatego tez, wiersze w tabeli Czytelnik sa juz gotowe do odczytu (przygotowanie jest robione w 
	//metodzie logujacej).

	if (dataBase == NULL) {
		sqlite3_open("..\\ProjektBiblioteka\\main_db.db", &dataBase);
		if (dataBase == NULL) {
			return NULL;
		}
	}

	sqlite3_stmt* stmt = NULL;
	sqlite3_prepare_v2(dataBase, query.c_str(), -1, &stmt, NULL);
	int retValue = sqlite3_step(stmt);

	if (retValue != SQLITE_ROW) {
		return NULL;
	}
	
	int id = sqlite3_column_int(stmt, 0);
	string firstName = Utilities::convertToString(sqlite3_column_text(stmt, 1));
	string lastName = Utilities::convertToString(sqlite3_column_text(stmt, 2));
	int age = sqlite3_column_int(stmt, 3);
	Date birthDate = Utilities::convertToData(Utilities::convertToString(sqlite3_column_text(stmt, 4)));
	string password = Utilities::convertToString(sqlite3_column_text(stmt, 5));
	string emailAdress = Utilities::convertToString(sqlite3_column_text(stmt, 6));
	string phoneNumber = Utilities::convertToString(sqlite3_column_text(stmt, 7));
	string city = Utilities::convertToString(sqlite3_column_text(stmt, 8));
	string zipCode = Utilities::convertToString(sqlite3_column_text(stmt, 9));
	string street = Utilities::convertToString(sqlite3_column_text(stmt, 10));
	int flatNumber = sqlite3_column_int(stmt, 11);
	Adress adress = Adress(city, zipCode, street, flatNumber);

	Librarian* librarian = new Librarian(firstName, lastName, emailAdress, phoneNumber, birthDate.getDay(), birthDate.getMonth(), birthDate.getYear(), adress, password, id);

	sqlite3_finalize(stmt);
	return librarian;
}


void Ui::changeUserData(int mode, Person* person, sqlite3* dataBase) {

	//Zmiana danych uzytkownika (czytelnika/bibliotekarza w zaleznosci od trybu).

	Reader* reader = NULL;
	Librarian* librarian = NULL;

	if (mode == 1) {
		reader = reinterpret_cast<Reader*>(person);
	}
	else if (mode == 2) {
		librarian = reinterpret_cast<Librarian*>(person);
	}
	else {
		cout << "Blad krytyczny. Wybrano niewlasciwy tryb." << endl;
		return;
	}

	while (true) {

		int choice;
		system("CLS");
		cout << "Wybierz co chcesz zmienic." << endl;
		cout << "Pamietaj, ze nie mozna zmienic niektorych danych za pomoca systemu. ";
		cout << "W sprawie ich zmiany skontaktuj sie z dyrekcja biblioteki." << endl;
		cout << "1: Zmiana hasla" << endl;
		cout << "2: Zmiana adresu e-mail" << endl;
		cout << "3: Zmiana numeru telefonu" << endl;
		cout << "0: Przerwanie dokonywania zmian" << endl;
		cin >> choice;
		cin.clear();
		cin.ignore(200, '\n');

		string query;
		sqlite3_stmt* stmt = NULL;

		switch (choice) {
		case 0:
			return;
		case 1:
		{
			string password1;
			string password2;
			cout << "Podaj nowe haslo: ";
			cin >> password1;
			cin.clear();
			cin.ignore(200, '\n');
			cout << "Powtorz haslo: ";
			cin >> password2;
			cin.clear();
			cin.ignore(200, '\n');

			if (password1 != password2) {
				int choice1 = -1;
				cout << "Hasla nie sa zgodne. Sprobuj ponownie." << endl;
			}
			else {
				if (mode == 1) {
					query = "UPDATE Czytelnik "
						"SET haslo = '" +
						password1 + "' WHERE ID == " + to_string(reader->getID()) + ";";
					reader->setPassword(password1);
				}
				else if (mode == 2) {
					query = "UPDATE Bibliotekarz "
						"SET haslo = '" +
						password1 + "' WHERE ID == " + to_string(librarian->getID()) + ";";
					librarian->setPassword(password1);
				}
				sqlite3_exec(dataBase, query.c_str(), NULL, NULL, NULL);
				cout << "Pomyslnie zmieniono haslo" << endl;
			}	
			system("pause");
			break;
		}
		case 2:
		{
			string email;
			cout << "Podaj nowy adres email: ";
			cin >> email;
			cin.clear();
			cin.ignore(200, '\n');

			if (validateEmail(email) && checkEmailAvailability(dataBase, email)){
				if (mode == 1) {
					query = "Czytelnik "
						"SET email = '" +
						email + "' WHERE ID == " + to_string(reader->getID()) + ";";
					reader->setEmailAdress(email);
				}
				else if (mode == 2) {
					query = "Bibliotekarz "
						"SET email = '" +
						email + "' WHERE ID == " + to_string(librarian->getID()) + ";";
					librarian->setEmailAdress(email);
				}
				sqlite3_exec(dataBase, query.c_str(), NULL, NULL, NULL);
				cout << "Pomyslnie zmieniono adres e-mail" << endl;
				system("pause");
			}
			else {
				cout << "Wystapil blad przy probie zmiany adresu e-mail. Sprobuj ponownie." << endl;
				system("pause");
			}
			break;
		}
		case 3:
		{
			string phoneNumber;
			cout << "Podaj nowy nr. telefonu: ";
			cin >> phoneNumber;
			getline(cin, phoneNumber);
			cin.clear();

			if (mode == 1) {
				query = "UPDATE Czytelnik "
					"SET telefon = '" +
					phoneNumber + "' WHERE ID = " + to_string(reader->getID()) + ";";\
				reader->setPhoneNumber(phoneNumber);
			}
			else if (mode == 2) {
				query = "UPDATE Bibliotekarz "
					"SET telefon = '" +
					phoneNumber + "' WHERE ID = " + to_string(librarian->getID()) + ";";
				librarian->setPhoneNumber(phoneNumber);
			}
			sqlite3_exec(dataBase, query.c_str(), NULL, NULL, NULL);
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

Library* Ui::loadLibrary(sqlite3* dataBase) {

	//Wczytuje biblioteke do bazy danych. 

	if (dataBase == NULL) {
		//Na wypadek gdyby przekazano NULL'a.
		sqlite3_open("..\\ProjektBiblioteka\\main_db.db", &dataBase);
		if (dataBase == NULL) {
			//Nie udalo sie otworzyc bazy danych.
			return NULL;
		}
	}

	string query = "SELECT * FROM BIBLIOTEKA;";
	sqlite3_stmt* stmt = NULL;
	sqlite3_prepare_v2(dataBase, query.c_str(), -1, &stmt, NULL);
	int ret = sqlite3_step(stmt);

	if (ret != SQLITE_ROW) {
		return NULL;
	}

	string emailAdress = Utilities::convertToString(sqlite3_column_text(stmt, 0));
	string phoneNumber = Utilities::convertToString(sqlite3_column_text(stmt, 1));
	string city = Utilities::convertToString(sqlite3_column_text(stmt, 2));
	string zipCode = Utilities::convertToString(sqlite3_column_text(stmt, 3));
	string street = Utilities::convertToString(sqlite3_column_text(stmt, 4));
	int flatNumber = sqlite3_column_int(stmt, 5);
	int amountOfCopies = sqlite3_column_int(stmt, 6);
	map<string, string> openingHours = Library::loadOpeningHours(dataBase);
	Adress adress = Adress(city, zipCode, street, flatNumber);

	sqlite3_finalize(stmt);

	Library* library = new Library(emailAdress, phoneNumber, adress, openingHours, amountOfCopies);
	return library;
}

Reader* Ui::loadReader(sqlite3* dataBase, string query) {
	//Na poczatku sprawdza czy baza danych jest otwarta.
	//Jezeli nie jest, probuje ja otworzyc.
	//Jezeli nie uda sie otworzyc (wskaznik na baze == NULL) to zwraca NULL'a (oznacza, ze nie udalo sie utworzyc obiektu.

	if (dataBase == NULL) {
		sqlite3_open("..\\ProjektBiblioteka\\main_db.db", &dataBase);
		if (dataBase == NULL) {
			return NULL;
		}
	}

	sqlite3_stmt* stmt = NULL;
	sqlite3_prepare_v2(dataBase, query.c_str(), -1, &stmt, NULL);
	int retValue = sqlite3_step(stmt);

	if (retValue != SQLITE_ROW) {
		return NULL;
	}

	int id = sqlite3_column_int(stmt, 0);
	string firstName = Utilities::convertToString(sqlite3_column_text(stmt, 9));
	string lastName = Utilities::convertToString(sqlite3_column_text(stmt, 10));
	int age = sqlite3_column_int(stmt, 11);
	Date birthDate = Utilities::convertToData(Utilities::convertToString(sqlite3_column_text(stmt, 12)));
	string password = Utilities::convertToString(sqlite3_column_text(stmt, 13));
	string emailAdress = Utilities::convertToString(sqlite3_column_text(stmt, 18));
	string phoneNumber = Utilities::convertToString(sqlite3_column_text(stmt, 19));
	string city = Utilities::convertToString(sqlite3_column_text(stmt, 6));
	string zipCode = Utilities::convertToString(sqlite3_column_text(stmt, 7));
	string street = Utilities::convertToString(sqlite3_column_text(stmt, 8));
	int flatNumber = sqlite3_column_int(stmt, 14);
	Adress adress = Adress(city, zipCode, street, flatNumber);

	Reader* reader = new Reader(firstName, lastName, emailAdress, phoneNumber, birthDate.getDay(), birthDate.getMonth(), birthDate.getYear(), adress, password, id);

	sqlite3_finalize(stmt);
	return reader;
}

bool Ui::registerUser(int mode, sqlite3* dataBase) {

	//Rejestracja bibliotekarza lub czytelnika w zaleznosci od wybranego trybu.

	if (mode != 1 && mode != 2) {
		return false;
	}
	if (dataBase == NULL) {
		sqlite3_open("..\\ProjektBiblioteka\\main_db.db", &dataBase);
		if (dataBase == NULL) {
			return false;
		}
	}
	if (mode == 1) {
		Person* person = createUser(1, dataBase);
		if (person == NULL) {
			return false;
		}
		Reader* reader = reinterpret_cast<Reader*>(person);
		reader->printReaderInfo();

		if (confirmVerification()) {
			if (addUserToDataBase(1, dataBase, reader)) {
				cout << "Pomyslnie dodano czytelnika do bazy danych." << endl;
				system("pause");
				//Po rejestracji kasuje czytelnika (musi sie nastepnie zalogowac).
				delete reader;
				return true;
			}
			else {
				cout << "Blad przy dodawaniu czytelnika do bazy danych." << endl;
				system("pause");
				delete reader;
				return false;
			}
		}
	}
	else if (mode == 2) {
		Person* person = createUser(2, dataBase);
		if (person == NULL) {
			return false;
		}
		Librarian* librarian = reinterpret_cast<Librarian*>(person);
		librarian->printLibrarianInfo();
		if (confirmVerification()) {
			if (addUserToDataBase(2, dataBase, librarian)) {
				cout << "Pomyslnie dodano bibliotekarza do bazy danych." << endl;
				system("pause");
				delete librarian;
				return true;
			}
			else {
				cout << "Blad przy dodawaniu bibliotekarz do bazy danych." << endl;
				system("pause");
				delete librarian;
				return false;
			}
		}
	}
}

void Ui::uiStartUp(Library* library, sqlite3*dataBase) {
	Ui ui = Ui();
	for (;;) {
		int accountType;
		int mode = ui.signInUpMenu();

		if (mode == 1) {
			//TRYB LOGOWANIA
			accountType = ui.chooseUserType();
			if (accountType == 3)
				continue;
			else if (accountType == 0)
				break;
			else if (accountType == 1) {
				Person* loggedUser = ui.logIn(1, dataBase);
				if (loggedUser == NULL) continue;
				else {
					Reader* loggedReader = reinterpret_cast<Reader*>(loggedUser);
					ui.readerMenu(loggedReader, library, dataBase);
				}
			}
			else if (accountType == 2) {
				Person* loggedUser = ui.logIn(2, dataBase);
				if (loggedUser == NULL) continue;
				else {
					Librarian* loggedLibrarian = reinterpret_cast<Librarian*>(loggedUser);
					ui.librarianMenu(loggedLibrarian, library, dataBase);
				}
			}
		}
		else if (mode == 2) {
			//TRYB REJESTRACJI
			int accountType = ui.chooseUserTypeRegistration();
			if (accountType == 0)
				break;
			else if (accountType == 3)
				continue;
			else if (accountType == 1) {
				ui.registerUser(1, dataBase);
			}
			else if (accountType == 2) {
				ui.registerUser(2, dataBase);
			}
		}
		else {
			break;
		}
	}
}
