#include "Wolumen.h"

using namespace std;
using namespace boost::posix_time;
using namespace boost::gregorian;

Wolumen::Wolumen(const string tytul, const float& kara) : wTytul(tytul), wKara(kara), wID(0), cIDwypo(0), dataWypo(2015, 10, 1) {}
Ksiazka::Ksiazka(const string tytul, const float& kara, const string autor, const string wyd, const string opis) 
: Wolumen(tytul, kara), kAutor(autor), kWyd(wyd), kOpis(opis) {}
const string Wolumen::GetTytul() const{
	return wTytul;
}
const int Wolumen::GetID() const{
	return wID;
}
void Wolumen::SetIDWypo(const int& set){
	cIDwypo = set;
}
void Wolumen::SetDataWypo(const date& set){
	dataWypo = set;
}
const float Wolumen::GetKara() const{
	return wKara;
}
const date Wolumen::GetDataWypo() const{
	return dataWypo;
}
const string Ksiazka::GetAutor() const{
	return kAutor;
}
const string Ksiazka::GetWyd() const{
	return kWyd;
}
const string Ksiazka::GetOpis() const{
	return kOpis;
}
void Wolumen::SetID(const int& set){
	wID = set;
}
const int Wolumen::GetIDWypo() const{
	return cIDwypo;
}
bool Wolumen::Mozna_wypo(){
	return !cIDwypo;
}
void Ksiazka::Drukuj(ostream& os) const{
	os << "Tytul: " << this->GetTytul() << endl;
	os << "Nr katalogowy (wID): " << this->GetID() << endl;
	os << "Autor: " << this->GetAutor() << endl;
	os << "Wydawnictwo: " << this->GetWyd() << endl;
	os << "Opis: " << this->GetOpis() << endl;
	os << "Dzienna kara za przetrzymanie: " << this->GetKara() << endl;
	os << "Wypozyczono czytelnikowi o numerze legitymacji (CID): " << this->GetIDWypo() << endl;
	os << "Data ostatniego wypozyczenia (RRRR/MM/DD): " << this->GetDataWypo() << endl;
	os << "###" << endl;
}
const bool operator < (const Ksiazka& first, const Ksiazka& second){
	if (first.GetID() < second.GetID())
		return true;
	else
		return false;
}
const bool operator == (const Ksiazka& first, const Ksiazka& second){
	if (first.GetID() == second.GetID())
		return true;
	else
		return false;
}
const bool operator == (const Ksiazka& first, const int& val){
	if (first.GetID() == val)
		return true;
	else
		return false;
}
ostream& operator << (ostream& os, const date& data){
	os << data.year() << "/" << (int)data.month() << "/" << data.day();
	return os;
}