#ifndef __WOLUMEN_H__
#define __WOLUMEN_H__

#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
#include "boost/date_time/gregorian/gregorian_types.hpp"
#include "boost/date_time/posix_time/posix_time.hpp"

using namespace std;
using namespace boost::posix_time;
using namespace boost::gregorian;

class Wolumen{
	string wTytul; // tytul wolumenu
	int wID; // numer wolumenu
	float wKara; // kara za przetrzymanie
	int cIDwypo; // numer legitymacji czytelnika, ktoremu wypozyczono
	date dataWypo; // data wypozyczenia
public:
	Wolumen(const string tytul, const float& kara);
	void SetID(const int& set);
	void SetIDWypo(const int& set);
	void SetDataWypo(const date& set);
	bool Mozna_wypo();
	const string GetTytul() const;
	const int GetID() const;
	const int GetIDWypo() const;
	const date GetDataWypo() const;
	const float GetKara() const;
	friend ostream& operator << (ostream& os, const date& data);
};

class Ksiazka : public Wolumen{
	string kAutor; // autor ksiazki
	string kWyd; // wydawca ksiazki
	string kOpis; // opis ksiazki
public:
	Ksiazka(const string tytul, const float& kara, const string autor, const string wyd, const string opis);
	void Drukuj(ostream& os) const;
	const string GetAutor() const;
	const string GetWyd() const;
	const string GetOpis() const;
	friend const bool operator < (const Ksiazka& first, const Ksiazka& second); // na potrzeby for_each() w Eksporcie
	friend const bool operator == (const Ksiazka& first, const Ksiazka& second); // na potrzeby find() w Stanie_konta
	friend const bool operator == (const Ksiazka& first, const int& val); // na potrzeby find() w Stanie_konta
};

#endif __WOLUMEN_H__
