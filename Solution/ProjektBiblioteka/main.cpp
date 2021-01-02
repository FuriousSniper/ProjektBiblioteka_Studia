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
	
	//const char* sql = "CREATE TABLE CZYTELNIK(ID INTEGER PRIMARY        KEY      ,listaZaleglosci       TEXT     ,dataPierwszegoWypozyczenia     DATE     ,iloscWypozyczonychOdDolaczenia  INT             ,preferowaneTematy     TEXT             ,dataDolaczenia        DATE             ,miasto				   TEXT             ,kodPocztowy           TEXT             ,ulica                 TEXT             ,imie                  TEXT             ,nazwisko              TEXT             ,wiek                  TEXT             ,dataUrodzenia         DATE             ,haslo				   TEXT				,numerMieszkania       TEXT             , ksiazka1 TEXT, ksiazka2 TEXT, ksiazka3 TEXT)";
	//sqlite3_exec(db, sql, NULL, NULL, NULL);
	/*
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
				//Logowanie czytelnika.
				//do zmodyfikowania po zaimplementowaniu ladowania czytelnika do pamieci 
				//(podobnie jak w bibliotekarzu).
				Czytelnik* osZalogowana = reinterpret_cast<Czytelnik*>(ui.zaloguj(1, db));
				if (osZalogowana == NULL) continue;
				else {
					ui.menuPoZalogowaniuCzytelnika(osZalogowana);
				}
			}
			else {
				//Logowanie bibliotekarza.
				//metoda zaloguj zwraca wskaznik na Osob? wiec konwertujemy.
				Bibliotekarz* osZalogowana = reinterpret_cast<Bibliotekarz*>(ui.zaloguj(2, db));
				if (osZalogowana == NULL) continue;
				else {
					ui.menuPoZalogowaniuBibliotekarza(osZalogowana);		
				}
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