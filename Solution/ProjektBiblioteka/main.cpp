#include <iostream>
#include "..\headers\Osoba.h";
#include "..\headers\Ui.h";
#include "..\headers\Autor.h";
#include "..\headers\Adres.h";
#include "..\headers\DaneKontaktowe.h";
#include "..\ProjektBiblioteka\Libraries\sqlite3\sqlite3.h";
#include "..\headers\Biblioteka.h";
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
	
	
	Library* biblioteka = ui.loadLibrary(db);

	if (biblioteka == NULL) {
		cout << "Nie udalo sie utworzyc obiektu biblioteka." << endl;
		return -1;
	}
	
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
				Reader* osZalogowana = reinterpret_cast<Reader*>(ui.logIn(1, db));
				if (osZalogowana == NULL) continue;
				else {
					ui.readerMenuChoice(osZalogowana);
				}
			}
			else {
				//Logowanie bibliotekarza.
				//metoda zaloguj zwraca wskaznik na Osob? wiec konwertujemy.
				Librarian* osZalogowana = reinterpret_cast<Librarian*>(ui.logIn(2, db));
				if (osZalogowana == NULL) continue;
				else {
					ui.librarianMenu(osZalogowana, biblioteka, db);		
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
				ui.registerUser(1, db);
			}
			else if (acc_type2 == 2) {
				ui.registerUser(2, db);
			}
		}
		else {
			//POTENCJALNY ERROR HANDLING
			break;
		}
	}
	
	//ui.addBook();
	sqlite3_close(db);

	system("pause");

	return 0;
}