#include <iostream>
#include "..\headers\Osoba.h";
#include "..\headers\Ui.h";
#include "..\headers\Autor.h";
#include "..\headers\AdresZamieszkania.h";
#include "../ProjektBiblioteka/Libraries/sqlite3/sqlite3.h";

using namespace std;

int main() {
	//EGZEMPLARZ, KSIAZKA, CZYTELNIK GOTOWE
	/*
	string id;
	Egzemplarz** listaZaleglosci;
	Data dataPierwszegoWypozyczenia;
	int iloscWypozyczonychObecnie;
	int iloscWypozyczonychOdDolaczenia;
	string* preferowaneTematy;
	Data dataDolaczenia;
	string miasto;
	string kodPocztowy;
	string ulica;
	int numerMieszkania;
	const string imie;
	const string nazwisko;
	int wiek;
	const Data dataUrodzenia;
	*/
	
	sqlite3* db;
	sqlite3_stmt* stmt;
	char* error;
	sqlite3_open("main_db.db", &db);

	if (db == NULL)
	{
		printf("Failed to open DB\n");
		return 1;
	}
	const char* sql;
	sql = "INSERT INTO "
		"CZYTELNIK("
		"	ID,"
		"	listaZaleglosci,"
		"	dataPierwszegoWypozyczenia,"
		"	iloscWypozyczonychOdDolaczenia,"
		"	preferowaneTematy,"
		"	dataDolaczenia,"
		"	miasto,"
		"	kodPocztowy,"
		"	ulica,"
		"	imie,"
		"	nazwisko,"
		"	wiek,"
		"	dataUrodzenia,"
		"	haslo,"
		"	numerMieszkania"
		") "
		"VALUES ("
		"	0002,"
		"	'',"
		"	'',"
		"	0,"
		"	'',"
		"	DATE(),"
		"		'Krakow',"
		"		'31-356',"
		"		'Dluga',"
		"		'Niko',"
		"		'Kovac',"
		"		26,"
		"		'1994 - 5 - 11',"
		"		'Kovac',"
		"		17"
		"	);";
	sqlite3_exec(db, sql, NULL, NULL, &error);
	if (error != SQLITE_OK)
		cout << "blad: "<<error << endl;

	printf("Performing query...\n");
	sqlite3_prepare_v2(db, "select * from CZYTELNIK", -1, &stmt, NULL);

	printf("Got results:\n");
	bool done = false;
	int row = 0;
	int bytes;
	const unsigned char* text;
	while (!done) {
		//printf("In select while\n");
		switch (sqlite3_step(stmt)) {
		case SQLITE_ROW:
			//bytes = sqlite3_column_bytes(stmt, 0);
			for (int i= 0; i < sqlite3_column_count(stmt); i++) {
				cout<<sqlite3_column_name(stmt, i) << ": ";
				cout<<sqlite3_column_text(stmt, i)<<endl;
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
	sqlite3_close(db);
	system("pause");
	
	return 0;
}