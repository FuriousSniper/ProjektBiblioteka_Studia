#include "..\headers\Biblioteka.h"
#include "..\headers\ElementyPomocnicze.h"

Biblioteka::Biblioteka(string emailKontaktowy, string telefonKontaktowy, Adres adres, map<string, string> godzinyOtwarcia, int iloscEgzemplarzy) : emailKontaktowy(emailKontaktowy), telefonKontaktowy(telefonKontaktowy), adres(adres), godzinyOtwarcia(godzinyOtwarcia), iloscEgzemplarzy(iloscEgzemplarzy) {}

void Biblioteka::printGodzinyOtwarcia() {
	map<string, string> ::iterator iterator = godzinyOtwarcia.begin();

	while (iterator != godzinyOtwarcia.end()) {
		cout<<"\t\t"<<iterator->first << ": " << iterator->second << endl;
		iterator++;
	}
}

void Biblioteka::printInfo() {
	cout << "Informacje o bibliotece:" << endl<<endl;
	cout << "\tTelefon kontaktowy: " << telefonKontaktowy << endl;
	cout << "\tE-mail kontaktowy: " << emailKontaktowy << endl;
	cout << "\tAdres: ";
	adres.printAdres();
	cout << "\tRozmiar ksiegozbiorow biblioteki: " << iloscEgzemplarzy << endl << endl;
	cout << "\tGodziny otwarcia:" << endl << endl;
	printGodzinyOtwarcia();	
}

map<string, string> Biblioteka :: wczytywanieGodzin(sqlite3* bazaDanych) {

	if (bazaDanych == NULL) {

		sqlite3_open("..\\ProjektBiblioteka\\main_db.db", &bazaDanych);

		if (bazaDanych == NULL) {

			//Nie udalo sie otworzyc bazy.

			return wczytywanieGodzinBlad();
		}
	}

	//Metoda pozwalajaca na wczytywanie godzin otwarcia biblioteki z bazy danych.
	//Zwraca mape, gdzie kluczem jest dzien tygodnia, a wartoscia godziny otwarcia dla danego dnia.

	sqlite3_stmt* stmt = NULL;
	string zapytanie = "SELECT godzinyOtwarcia FROM Biblioteka;";
	sqlite3_prepare_v2(bazaDanych, zapytanie.c_str(), -1, &stmt, NULL);

	map<string, string> godzinyOtwarcia;

	if (sqlite3_step(stmt) == SQLITE_ROW) {

		//Zakladam, ze w bazie znajduja sie godziny dla 7 dni. One beda wstawione do bazy jednorazowo.
		//Ten program nie bedzie przewidywal ich modyfikacji.
		//Jezeli bylaby mozliwa modyfikacja to tutaj trzeba byloby duzo wiecej dopisac...

		vector<string> podzielone = ElementyPomocnicze :: split_string(ElementyPomocnicze :: konwersjaNaString(sqlite3_column_text(stmt, 0)), "||");

		if (podzielone.size() != 7) {

			//Gdyby wystapila sytuacja (te dane nie beda modyfikowane przez czytelnika/bibliotekarza, ale
			//dodaje, na wszelki wypadek, obsluge tego przypadku) gdzie nie ma godzin otwarcia
			//dla wszystkich dni w bazie danych (rozmiar vectora != 7), uzupelnij (do 7) odpowiednia informacja.

			//Przypisuje reszcie dni "Brak danych do wyswietlenia".

			while (podzielone.size() != 7) {
				podzielone.push_back("Brak danych do wyswietlenia.");
			}
		}

		godzinyOtwarcia["Poniedzialek"] = podzielone[0];
		godzinyOtwarcia["Wtorek"] = podzielone[1];
		godzinyOtwarcia["Sroda"] = podzielone[2];
		godzinyOtwarcia["Czwartek"] = podzielone[3];
		godzinyOtwarcia["Piatek"] = podzielone[4];
		godzinyOtwarcia["Sobota"] = podzielone[5];
		godzinyOtwarcia["Niedziela"] = podzielone[6];

	}
	else {

		cout << "Blad krytyczny. Nie znaleziono biblioteki w bazie danych";

		//Wtedy tworzy mape, gdzie dla kazdego klucza przypisuje wartosc "Blad odczytu".

		godzinyOtwarcia = wczytywanieGodzinBlad();

	}

	sqlite3_finalize(stmt);
	return godzinyOtwarcia;
}

map<string, string> Biblioteka :: wczytywanieGodzinBlad() {

	map<string, string> godzinyOtwarcia;

	//Wykorzystywane do przypisywania godzin, gdy nie udalo sie otworzyc bazy lub otworzono baze
	//ale nie zawiera ona zadnych rekordow (patrz metoda wczytywanieGodzin).

	godzinyOtwarcia["Poniedzialek"] = "Blad odczytu";
	godzinyOtwarcia["Wtorek"] = "Blad odczytu";
	godzinyOtwarcia["Sroda"] = "Blad odczytu";
	godzinyOtwarcia["Czwartek"] = "Blad odczytu";
	godzinyOtwarcia["Piatek"] = "Blad odczytu";
	godzinyOtwarcia["Sobota"] = "Blad odczytu";
	godzinyOtwarcia["Niedziela"] = "Blad odczytu";

	return godzinyOtwarcia;
}


