#include "Osoba.h"

using namespace std;

static float max_kara = 5.;

Osoba::Osoba(const string imie, const string nazwisko, const string tel) : oImie(imie), oNazwisko(nazwisko), oTel(tel) {}
const string Osoba::GetImie() const{
	return oImie;
}
const string Osoba::GetNazwisko() const{
	return oNazwisko;
}
const string Osoba::GetTelefon() const{
	return oTel;
}

Czytelnik::Czytelnik(const string imie, const string nazwisko, const string tel) : Osoba(imie, nazwisko, tel), cID(0), cLicz(0), cKara(0) {}
void Czytelnik::SetID(const int& set){
	cID = set;
}
void Czytelnik::SetLicz(const int& set){
	cLicz = set;
}
void Czytelnik::SetListWypo(const list<int>& set){
	listWypo = set;
}
void Czytelnik::SetKara(const float& set){
	cKara = set;
}
const int Czytelnik::GetID() const{
	return cID;
}
const int Czytelnik::GetLicz() const{
	return cLicz;
}
const list<int> Czytelnik::GetListWypo() const{
	return listWypo;
}
const float Czytelnik::GetKara() const{
	return cKara;
}
const bool operator < (const Czytelnik& first, const Czytelnik& second){
	if (first.GetID() < second.GetID())
		return true;
	else 
		return false;
}
const bool operator == (const Czytelnik& first, const Czytelnik& second){
	if (first.GetID() == second.GetID())
		return true;
	else
		return false;
}
const bool operator == (const Czytelnik& first, const int& val){
	if (first.GetID() == val)
		return true;
	else
		return false;
}
void Czytelnik::Drukuj(ostream& os) const{
	os << "Imie: " << this->GetImie() << endl;
	os << "Nazwisko: " << this->GetNazwisko() << endl;
	os << "Nr telefonu: " << this->GetTelefon() << endl;
	os << "Nr legitymacji (cID): " << this->GetID() << endl;
	os << "Liczba wypozyczen: " << this->GetLicz() << endl;
	os << "Numery katalogowe wypozyczonych wolumenow (wID): ";
	ostream_iterator<int> out_it(os, ", ");
	copy(listWypo.begin(), listWypo.end(), out_it);
	os << endl;
	os << "Nalezna kara: " << this->GetKara() << endl;
	os << "###" << endl;
}
bool Czytelnik::Mozna_wypo(){
	if (cLicz < 10 && cKara < max_kara)
		return true;
	else
		return false;
}
void Czytelnik::Wypozycz(const int& wID){
	listWypo.push_back(wID);
}
void Czytelnik::Zwroc(const int& wID){
	list<int>::iterator wIter = find(listWypo.begin(), listWypo.end(), wID);
	listWypo.erase(wIter);
}