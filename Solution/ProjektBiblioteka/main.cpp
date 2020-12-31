#include <iostream>
#include "..\headers\Osoba.h";
#include "..\headers\Ui.h";
#include "..\headers\Autor.h";
#include "..\headers\AdresZamieszkania.h";
#include "..\headers\DaneKontaktowe.h";
#include "../ProjektBiblioteka/Libraries/sqlite3/sqlite3.h";
#include <sstream>
#include <vector>

using namespace std;

int main() {

	
	
	Ui ui = Ui();
	sqlite3* db;
	sqlite3_stmt* stmt;
	char* error;
	sqlite3_open("main_db.db", &db);

	if (db == NULL)
	{
		printf("Failed to open DB\n");
		return 1;
	}
	
	
	/*
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
	*/

	const char* sql = "CREATE TABLE CZYTELNIK(ID INTEGER PRIMARY        KEY      ,listaZaleglosci       TEXT     ,dataPierwszegoWypozyczenia     DATE     ,iloscWypozyczonychOdDolaczenia  INT             ,preferowaneTematy     TEXT             ,dataDolaczenia        DATE             ,miasto				   TEXT             ,kodPocztowy           TEXT             ,ulica                 TEXT             ,imie                  TEXT             ,nazwisko              TEXT             ,wiek                  TEXT             ,dataUrodzenia         DATE             ,haslo				   TEXT				,numerMieszkania       TEXT             , ksiazka1 TEXT, ksiazka2 TEXT, ksiazka3 TEXT)";
	sqlite3_exec(db, sql, NULL, NULL, NULL);
	for (;;) {
		int tryb = ui.signInUpMenu();
		if (tryb == 1) {
			//TRYB LOGOWANIA
			int acc_type = ui.chooseUserType();
			if (acc_type == 3)
				continue;
			else if (acc_type == 0)
				break;
			else if (acc_type == 1) {
				//LOGOWANIE CZYTELNIKA
			}
			else {
				//LOGOWANIE BIBLIOTEKARZA
			}
		}
		else if (tryb == 2) {
			//TRYB REJESTRACJI
			int acc_type2 = ui.chooseUserTypeRegistration();
			if (acc_type2 == 0)
				break;
			else if (acc_type2 == 3)
				continue;
			else if (acc_type2 == 1) {
				//REJESTRACJA CZYTELNIKA
				Czytelnik new_user = ui.createCzytelnik(db);
				new_user.printInfo();
				//WERYFIKACJA POPRAWNOSCI WPROWADZONYCH DANYCH
				if (ui.confirmVerification() == true) {
					//DODANIE CZYTELNIKA DO BAZY DANYCH
					if (ui.addCzytelnik(new_user, db) == true) {
						system("cls");
						cout << "Pomyslnie dodano uzytkownika!\nHaslo: " << new_user.getHaslo()
						<< "\nLogin: " << new_user.getImie() << " " << new_user.getNazwisko() << endl;
						system("pause");
					}
					else {
						cout << "Blad przy dodawaniu uzytkownika do bazy danych.\n";
						system("pause");
					}
				}
				else {
					continue;
				}
			}
			else if (acc_type2 == 2) {

				//REJESTRACJA BIBLIOTEKARZA

				Bibliotekarz new_user = ui.createBibliotekarz(db);
				new_user.printInfOBibliotekarzu();

				if (ui.confirmVerification() == true) {

					if (ui.addBibliotekarz(new_user, db) == true) {
						system("cls");
						cout << "Pomyslnie dodano bibliotekarza!\nHaslo: " << new_user.getHaslo() << "\nLogin: " << new_user.getImie() << " " << new_user.getNazwisko() << endl;
						system("pause");
					}
						else {
						cout << "Blad przy dodawaniu uzytkownika do bazy danych.\n";
						system("pause");
					}
				}
				else {
					continue;
				}
			
			}
		}
		else {
			//POTENCJALNY ERROR HANDLING
			break;
		}
	}
		

	
	sqlite3_close(db);

	
	system("pause");

	return 0;
}