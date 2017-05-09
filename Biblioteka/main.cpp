/*
BIBIOTEKA v0.9
Jest to program napisany na zaliczenie projektu z przedmiotu "Programowanie obiektowe w C++". Realizuje on temat nr 30. Biblioteka.
Niniejszy kod ilustruje zastosowanie nastepujacych pojec podejscia obiektowego C++:
-- klasy, dziedziczenie, klasy wirtualne;
-- biblioteka STL: wektory, listy, algorytmy (sortowanie, szukanie);
-- obiekty funkcyjne, przeciazanie operatorow;
Celem implementacji narzedzia naliczajacego kare za przetrzymanie wolumenu powyzej 30 dni, skorzystano w biblioteki zewnetrznej boost v.1.60.0.
Jest ona niezbedna do poprawnego obliczania liczby dni, ktore uplynely od daty wypozyczenia. Jest to mozliwe do wlasnorecznego okodowania,
lecz autor programu uznal to za zbyt zmudne i nie wnoszace dodatkowego waloru edukacyjnego z zakresu podejscia obiektowego.
*/

#include <cstdlib>
#include <iostream>
#include <windows.h>
#include "Osoba.h"
#include "Wolumen.h"
#include "Funktor.h"
#include "Baza.h"

using namespace std;

int main(){

	Baza b1;

	cout << "Witam w programie Bibioteka v.0.9!" << endl << endl;
	int wybor = -1;

	while (wybor != 0){
		cout << "Wybierz polecenie:" << endl;
		cout << "1. Importuj baze" << endl;
		cout << "2. Eksportuj baze" << endl;
		cout << "3. Dodaj czytelnika" << endl;
		cout << "4. Dodaj ksiazke" << endl;
		cout << "5. Sprawdz stan konta czytelnika" << endl;
		cout << "6. Sprawdz stan ksiazki" << endl;
		cout << "7. Wypozycz ksiazke" << endl;
		cout << "8. Zwroc ksiazke" << endl;
		cout << "0. Wyjscie" << endl;
		cout << "Wybor: ";
		wybor = -1;
		cin >> wybor;
		system("CLS");

		switch (wybor)
		{
		case 0:
			exit(0);
		case 1:
			b1.Importuj_baze();
			break;
		case 2:
			b1.Eksportuj_baze();
			break;
		case 3:
			b1.Dodaj_cz();
			break;
		case 4:
			b1.Dodaj_ks();
			break;
		case 5:
			b1.Stan_konta();
			break;
		case 6:
			b1.Stan_ksiazki();
			break;
		case 7:
			b1.Wypozycz();
			break;
		case 8:
			b1.Zwroc();
			break;	
		default:
			cout << "Niepoprawny wybor!" << endl;
			break;
		}
		cin.clear();
		cin.ignore();
		cout << endl;
	}

	system("pause");
	return 0;
}