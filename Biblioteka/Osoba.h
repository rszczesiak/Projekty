#ifndef __OSOBA_H__
#define __OSOBA_H__

#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
#include <list>
#include "Wolumen.h"

using namespace std;

class Osoba{
	string oImie; // imie
	string oNazwisko; // nazwisko
	string oTel; // telefon
public:
	Osoba(const string imie, const string nazwisko, const string tel);
	const string GetImie() const;
	const string GetNazwisko() const;
	const string GetTelefon() const;
};

class Czytelnik : public Osoba{
	int cID; // nr legitymacji czytelnika
	int cLicz; // liczba wypozyczen czytelnika
	list<int> listWypo; // lista wID wypozyczonych wolumenow
	float cKara;
public:
	Czytelnik(const string imie, const string nazwisko, const string tel);
	float Oblicz_kare(); // oblicza nalezna kare na podstawie liczby wypozyczen po terminie i kary jednostkowej
	const int GetID() const;
	const int GetLicz() const;
	const list<int> GetListWypo() const;
	void SetID(const int& set);
	void SetLicz(const int& set);
	void SetListWypo(const list<int>& set);
	void SetKara(const float& set);
	const float GetKara() const;
	void Drukuj(ostream& os) const;
	bool Mozna_wypo();
	void Wypozycz(const int& wID);
	void Zwroc(const int& wID);
	friend const bool operator < (const Czytelnik& first, const Czytelnik& second); // na potrzeby for_each() w Eksporcie
	friend const bool operator == (const Czytelnik& first, const Czytelnik& second); // na potrzeby find() w Stanie_konta
	friend const bool operator == (const Czytelnik& first, const int& val); // na potrzeby find() w Stanie_konta
};

#endif __OSOBA_H__