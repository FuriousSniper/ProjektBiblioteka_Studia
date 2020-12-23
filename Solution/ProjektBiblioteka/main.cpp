#include <iostream>
#include "..\headers\Osoba.h";
#include "..\headers\Ui.h";
#include "..\headers\Autor.h";
#include "..\headers\AdresZamieszkania.h";
#include "../ProjektBiblioteka/Libraries/sqlite3/sqlite3.h";

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
	}/*
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
	}*/
	
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
				Czytelnik new_user = ui.createCzytelnik();
				new_user.setAdresZamieszkania(ui.createAdres());
				new_user.printInfo();
				//WERYFIKACJA POPRAWNOSCI WPROWADZONYCH DANYCH
				if (ui.confirmVerification() == true) {
					//DODANIE CZYTELNIKA DO BAZY DANYCH
					string sql2;
					sql2 = "INSERT INTO "
						"CZYTELNIK "
						"VALUES ("
						"	'',"			
						"	'',"			//RESZTA ZOSTAJE PUSTA
						"	'',"			//BO UZYTKOWNIK NIC JESZCZE NIE WYPOZYCZYL
						"	0,"
						"	'',"
						"	DATE(),'"+
						new_user.getAdres().getMiasto()+"','"+
						new_user.getAdres().getKodPocztowy()+"','"+
						new_user.getAdres().getUlica()+"','"+
						new_user.getImie()+"','"+
						new_user.getNazwisko()+"','"+
						to_string(new_user.getWiek())+"','"+
						to_string(new_user.getDataUrodzenia().getDzien())+"-"+
						to_string(new_user.getDataUrodzenia().getMiesiac())+"-"+ //DO UJEDNOLICENIA
						to_string(new_user.getDataUrodzenia().getRok())+"','"+	 //FORMAT WYSWIETLANIA DATY
						to_string(new_user.getAdres().getNumerMieszkania())+"','"+
						new_user.getHaslo()+"'"
						"	);";
					sqlite3_exec(db, sql2.c_str(), NULL, NULL, &error);
					if (error != SQLITE_OK) {
						cout << "blad: " << error << endl;
						system("pause");
					}
				}
				else {
					continue;
				}
			}
			else {
				//REJESTRACJA BIBLIOTEKARZA
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