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

	sqlite3* dataBase;
	sqlite3_open("main_db.db", &dataBase);

	if (dataBase == NULL){
		cout << "Nie udalo sie otworzyc bazy danych. Nastopi wyjscie z programu." << endl;
		return 1;
	}

	//Ladowanie danych o bibliotece do obiektu w pamieci.

	Library* library = Ui :: loadLibrary(dataBase);

	//Jezeli nie udalo sie zaladowac (metoda zwrocila NULL), konczy program.

	if (library == NULL) {
		cout << "Nie udalo sie utworzyc obiektu biblioteka. Nastapi wyjscie z programu." << endl;
		return -1;
	}

	//Jezeli nie wystapily zadne kompilacja (blad otwarcia bazy, blad przy tworzeniu obiektu typu Library).
	//Zacznij interakcje z uzytkownikiem.

	Ui :: uiStartUp(library, dataBase);
	sqlite3_close(dataBase);
	system("pause");
	return 0;
}