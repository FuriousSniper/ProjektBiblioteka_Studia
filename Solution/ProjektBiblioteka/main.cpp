#include <iostream>
#include "..\headers\Person.h"
#include "..\headers\Ui.h"
#include "..\headers\Author.h"
#include "..\headers\Adress.h"
#include "..\ProjektBiblioteka\Libraries\sqlite3\sqlite3.h"
#include "..\headers\Library.h"
#include <sstream>
#include <vector>

using namespace std;

int main() {

	Ui ui = Ui();
	sqlite3* dataBase;

	sqlite3_open("main_db.db", &dataBase);

	if (dataBase == NULL)
	{
		printf("Failed to open DB\n");
		return 1;
	}
		
	Library* library = ui.loadLibrary(dataBase);

	if (library == NULL) {
		cout << "Nie udalo sie utworzyc obiektu biblioteka." << endl;
		return -1;
	}
	
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
					ui.readerMenuChoice(loggedReader);
				}
			}
			else if(accountType == 2){	
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
			//POTENCJALNY ERROR HANDLING
			break;
		}
	}
	
	//ui.addBook();
	sqlite3_close(dataBase);

	system("pause");

	return 0;
}