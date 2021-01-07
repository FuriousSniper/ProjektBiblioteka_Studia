#include "..\headers\Utilities.h"

string Utilities :: convertToString(const unsigned char* var) {

	//Konwersja const unsigned char* na const char* (string).
	//Jezeli wskaznik jest NULL'em, zwraca pustego stringa.

	if (var == NULL) {
		return "";
	}
	else {
		return reinterpret_cast<const char*>(var);
	}
}

Date Utilities :: convertToData(string stringToBeConverted) {

	//Jezeli w danym rekordzie kolumna o typie danych DATA jest pusta to sqlite3_column_text(...) zwraca NULLA.
	//W innej metodzie (konwersjaNaString) zwracana wartosc konwertowana jest na string (zwracana wartosc jest typu
	//const unsigned char*).
	//Jezeli zwracana wartosc == NULL to jest konwertowana na "".
	//W takim przypadku zwracany jest obiekt utworzony konstruktorem domyslnym.

	if (stringToBeConverted == "") {
		return Date();
	}

	//W przeciwnym razie stringa dzieli sie na 3 czesci (d,m,r) oddzielone delimiterem "-" (taki jest format zapisu
	//dat w bazie).

	//Zakladam, ze nie moze zajsc sytuacja, w ktorej rozmiar tego vectora jest rozny od 3. Tzn. data zapisywana
	//w bazie zawsze slada sie z 3 czesci: dnia, miesiaca oraz roku albo nie ma jej wcale (patrz wy¿ej).

	//Jezeli moze zajsc sytuacja w ktorej rozmiar vectora moze byc rozny od 3, nalezy dodac tu wiecej warunkow.

	vector<string> splitString = split_string(stringToBeConverted, "-");
	return Date(stoi(splitString[0]), stoi(splitString[1]), stoi(splitString[2]));
}

vector<string> Utilities :: split_string(string stringToBeSplitted, string delimeter) {
	vector<string> splittedString;
	int startIndex = 0;
	int  endIndex = 0;
	while ((endIndex = stringToBeSplitted.find(delimeter, startIndex)) < stringToBeSplitted.size()){
		string val = stringToBeSplitted.substr(startIndex, endIndex - startIndex);
		splittedString.push_back(val);
		startIndex = endIndex + delimeter.size();
	}
	if (startIndex < stringToBeSplitted.size()){
		string val = stringToBeSplitted.substr(startIndex);
		splittedString.push_back(val);
	}
	return splittedString;
}