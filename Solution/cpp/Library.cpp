#include "..\headers\Library.h"
#include "..\headers\utilities.h"

Library::Library(string contactEmailAdress, string contactPhoneNumber, Adress adress, map<string, string> openingHours, int numberOfCopies) : contactEmailAdress(contactEmailAdress), contactPhoneNumber(contactPhoneNumber), adress(adress), openingHours(openingHours), numberOfCopies(numberOfCopies) {}

void Library::printOpeningHours() {
	map<string, string> ::iterator iterator = openingHours.begin();

	while (iterator != openingHours.end()) {
		cout<<"\t\t"<<iterator->first << ": " << iterator->second << endl;
		iterator++;
	}
}

void Library::printLibraryInfo() {
	cout << "Informacje o bibliotece:" << endl<<endl;
	cout << "\tTelefon kontaktowy: " << contactPhoneNumber << endl;
	cout << "\tE-mail kontaktowy: " << contactEmailAdress << endl;
	cout << "\tAdres: ";
	adress.printAdress();
	cout << "\tRozmiar ksiegozbiorow biblioteki: " << numberOfCopies << endl << endl;
	cout << "\tGodziny otwarcia:" << endl << endl;
	printOpeningHours();	
}

map<string, string> Library :: loadOpeningHours(sqlite3* dataBase) {

	if (dataBase == NULL) {
		sqlite3_open("..\\ProjektBiblioteka\\main_db.db", &dataBase);
		if (dataBase == NULL) {
			//Nie udalo sie otworzyc bazy.
			return loadOpeningHoursError();
		}
	}

	//Metoda pozwalajaca na wczytywanie godzin otwarcia biblioteki z bazy danych.
	//Zwraca mape, gdzie kluczem jest dzien tygodnia, a wartoscia godziny otwarcia dla danego dnia.

	sqlite3_stmt* stmt = NULL;
	string query = "SELECT godzinyOtwarcia FROM Biblioteka;";
	sqlite3_prepare_v2(dataBase, query.c_str(), -1, &stmt, NULL);

	map<string, string> openingHours;

	if (sqlite3_step(stmt) == SQLITE_ROW) {

		//Zakladam, ze w bazie znajduja sie godziny dla 7 dni. One beda wstawione do bazy jednorazowo.
		//Ten program nie bedzie przewidywal ich modyfikacji.
		//Jezeli bylaby mozliwa modyfikacja to tutaj trzeba byloby duzo wiecej dopisac...

		vector<string> splitString = Utilities :: splitString(Utilities :: convertToString(sqlite3_column_text(stmt, 0)), "||");

		if (splitString.size() != 7) {

			//Gdyby wystapila sytuacja (te dane nie beda modyfikowane przez czytelnika/bibliotekarza, ale
			//dodaje, na wszelki wypadek, obsluge tego przypadku) gdzie nie ma godzin otwarcia
			//dla wszystkich dni w bazie danych (rozmiar vectora != 7), uzupelnij (do 7) odpowiednia informacja.

			//Przypisuje reszcie dni "Brak danych do wyswietlenia".

			while (splitString.size() != 7) {
				splitString.push_back("Brak danych do wyswietlenia.");
			}
		}

		openingHours["Poniedzialek"] = splitString[0];
		openingHours["Wtorek"] = splitString[1];
		openingHours["Sroda"] = splitString[2];
		openingHours["Czwartek"] = splitString[3];
		openingHours["Piatek"] = splitString[4];
		openingHours["Sobota"] = splitString[5];
		openingHours["Niedziela"] = splitString[6];

	}
	else {

		cout << "Blad krytyczny. Nie znaleziono biblioteki w bazie danych";

		//Wtedy tworzy mape, gdzie dla kazdego klucza przypisuje wartosc "Blad odczytu".

		openingHours = loadOpeningHoursError();

	}
	sqlite3_finalize(stmt);
	return openingHours;
}

map<string, string> Library :: loadOpeningHoursError() {

	map<string, string> openingHours;

	//Wykorzystywane do przypisywania godzin, gdy nie udalo sie otworzyc bazy lub otworzono baze
	//ale nie zawiera ona zadnych rekordow (patrz metoda wczytywanieGodzin).

	openingHours["Poniedzialek"] = "Blad odczytu";
	openingHours["Wtorek"] = "Blad odczytu";
	openingHours["Sroda"] = "Blad odczytu";
	openingHours["Czwartek"] = "Blad odczytu";
	openingHours["Piatek"] = "Blad odczytu";
	openingHours["Sobota"] = "Blad odczytu";
	openingHours["Niedziela"] = "Blad odczytu";

	return openingHours;
}


