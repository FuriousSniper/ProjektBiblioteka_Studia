#ifndef ELEMENTY_POMOCNICZE_H
#define ELEMENTY_POMOCNICZE_H

#include<iostream>
#include <vector>
#include "Data.h"

using namespace std;

class ElementyPomocnicze {

public:

	//Konwertuje wskaznik (const unsigned char*) zwracany przez funkcje sqlite3_column_text
	//na string (const char*).
	static string konwersjaNaString(const unsigned char*);

	//Konwertuje string'a (WAZNE: musi byc to data pobrana z bazy danych) na obiekt typu Data.
	static Data konwersjaNaData(string napis);

	//funkcja do splitowania stringa za pomoca delimitera. arg 1 - string do podzielenia. arg 2 - delimiter. zwraca vector (uzywany jako tablica do prostego przejscia i wykonania czegos)
	static vector<string> split_string(string stringToBeSplitted, string delimeter);

};

#endif
