#ifndef __BAZA_H__
#define __BAZA_H__

#include <cstdlib>
#include <iostream>
#include <windows.h>
#include <string>
#include <vector>
#include <algorithm>
#include <fstream>
#include "Osoba.h"
#include "Wolumen.h"
#include "Funktor.h"
#include "boost/date_time/gregorian/gregorian_types.hpp"

using namespace std;
using namespace boost::gregorian;

class Baza{
	string pcz; //nazwa pliku z baza czytelnikow
	string pks; //nazwa pliku z baza ksiazek
	vector<Czytelnik> cTab;
	vector<Ksiazka> kTab;
public:
	Baza();
	Baza(const string& pcz, const string& pks);
	~Baza();
	void Dodaj_cz(); // tworzy czytelnika i dodaje go na koniec wektora czytelnikow
	void Dodaj_ks(); // tworzy ksiazke i dodaje ja na koniec wektora ksiazek
	void Wczytaj_cz(ifstream& cz); // wczytywanie informacji o czytelnikach z pliku
	void Wczytaj_ks(ifstream& ks); // wczytywanie informacji o ksiazce z pliku
	int Nadaj_cID(); // zwraca najnizszy wolny numer legitymacji. Tu moznaby sprobowac zrobic szablon dla cID i wID
	int Nadaj_wID(); // Zwraca najnizszy wolny numer wolumenu
	void Eksportuj_baze(); // eksport do pliku
	void Importuj_baze(); // import z pluki
	void Stan_konta(); // wyswietla Stan konta czytelnika
	void Stan_ksiazki(); // wyswietla Stan ksiazki
	void Wypozycz(); // wypozycza ksiazke czytelnikowi
	void Zwroc(); // zwraca ksiazke do biblioteki
	void Nalicz_kare(const int cID); // nalicza calkowita kare za przetrzymanie dla czytelnika
};

#endif __BAZA_H__
