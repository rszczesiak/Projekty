#include "Baza.h"

using namespace std;
using namespace boost::posix_time;
using namespace boost::gregorian;

Baza::Baza() : pcz("czytelnicy.txt"), pks("ksiazki.txt") {}
Baza::Baza(const string& pcz, const string& pks) : pcz(pcz), pks(pks) {}
Baza::~Baza(){}
void Baza::Dodaj_cz(){
	string imie, nazwisko, tel;
	cout << "Podaj imie: " << endl;
	cin >> imie;
	cout << "Podaj nazwisko: " << endl;
	cin >> nazwisko;
	cout << "Podaj nr telefonu: " << endl;
	cin >> tel;
	cTab.push_back(Czytelnik(imie, nazwisko, tel));
	cTab.back().SetID(Nadaj_cID());
	cout << "Nadano cID: " << cTab.back().GetID() << endl;
}
void Baza::Dodaj_ks(){
	string tytul, autor, wydaw, opis;
	float kara;
	cout << "Podaj tytul: " << endl;
	cin >> tytul;
	cout << "Podaj autora: " << endl;
	cin >> autor;
	cout << "Podaj wydawnictwo: " << endl;
	cin >> wydaw;
	cout << "Podaj opis: " << endl;
	cin >> opis;
	cout << "Podaj dzienna kare za przetrzymanie: " << endl;
	cin >> kara;
	kTab.push_back(Ksiazka(tytul, kara, autor, wydaw, opis));
	kTab.back().SetID(Nadaj_wID());
	cout << "Nadano wID: " << kTab.back().GetID() << endl;
}
int Baza::Nadaj_cID(){
	if (cTab.size() == 1) // 1, poniewaz przed chwila powstal pierwszy element kolekcji
		return 1;
	else {
		sort(cTab.begin(), next(cTab.end(), -1));
		if (cTab.begin()->GetID() != 1)
			return 1;
		else {
			for (vector<Czytelnik>::iterator iter = cTab.begin(); iter != next(cTab.end(),-1); ++iter){
				if ((iter->GetID( )+ 1) != next(iter, 1)->GetID() )
					return iter->GetID() + 1;
			}
			if (cTab.begin()->GetID() == 0)
				return next(cTab.end(), -1)->GetID() + 1;
		}
	}
}
int Baza::Nadaj_wID(){
	if (kTab.size() == 1) // 1, poniewaz przed chwila powstal pierwszy element kolekcji
		return 1;
	else {
		sort(kTab.begin(), next(kTab.end(), -1));
		if (kTab.begin()->GetID() != 1)
			return 1;
		else {
			for (vector<Ksiazka>::iterator iter = kTab.begin(); iter != next(kTab.end(), -1); ++iter){
				if ((iter->GetID() + 1) != next(iter, 1)->GetID())
					return iter->GetID() + 1;
			}
			if (kTab.begin()->GetID() == 0)
				return next(kTab.end(), -1)->GetID() + 1;
		}
	}
}
void Baza::Eksportuj_baze(){
	ofstream fcz(pcz);
	ofstream fks(pks);
	if (fcz.good() && fks.good()){
		for_each(cTab.begin(), cTab.end(), Drukuj<Czytelnik>(fcz));
		for_each(kTab.begin(), kTab.end(), Drukuj<Ksiazka>(fks));
	}
	else
		cerr << "Brak dostępu do pliku!" << endl;
	fcz.close(); fks.close();
}
void Baza::Importuj_baze(){
	ifstream fcz(pcz);
	ifstream fks(pks);
	if (fcz.good() && fks.good()){
		this->Wczytaj_ks(fks);
		this->Wczytaj_cz(fcz);
	}
	else
		cerr << "Brak dostępu do pliku!" << endl;
	fcz.close(); fks.close();
}
void Baza::Stan_konta(){
	int val;
	cout << "Podaj numer legitymacji (cID): " << endl;
	cin >> val;
	vector<Czytelnik>::iterator iter = find(cTab.begin(), cTab.end(), val);
	if (iter != cTab.end())
		iter->Drukuj(cout);
	else
		cerr << "Podano niepoprawny numer legitymacji (cID)!" << endl;
}
void Baza::Stan_ksiazki(){
	int val;
	cout << "Podaj numer katalogowy ksiazki (wID): " << endl;
	cin >> val;
	vector<Ksiazka>::iterator iter = find(kTab.begin(), kTab.end(), val);
	if (iter != kTab.end())
		iter->Drukuj(cout);
	else
		cerr << "Podano niepoprawny katalogowy (wID)!" << endl;
}
void Baza::Wczytaj_cz(ifstream& cz){
	string tekst;
	int count = 1;
	string imie, nazwisko, tel, listWypo;
	size_t comma = 0;
	list<int> lista;
	float kara;
	int ID, licz;
		while (!cz.eof()){
			getline(cz,tekst);
			size_t found = tekst.find(":"); // szukanie pozycji pierwszego dwukropka w lancuchu
			if (found != -1) tekst.erase(tekst.begin(), tekst.begin() + found + 2); // usuwa wszystko co przed pierwszym drukropkiem oraz ": "

			switch (count % 8){
			case 1:
				imie = tekst;
				break;
			case 2:
				nazwisko = tekst;
				break;
			case 3:
				tel = tekst;
				break;
			case 4:
				ID = stoi(tekst);
				break;
			case 5:
				licz = stoi(tekst);
				break;
			case 6:
				listWypo = tekst;
				while (comma = tekst.find(",") != -1){
					lista.push_back(stoi(tekst.substr(0, comma)));
					tekst.erase(tekst.begin(), tekst.begin() + comma+2);
				}
				comma = 0;
				break;
			case 7:
				kara = stof(tekst);
				break;
			default:
				cTab.push_back(Czytelnik(imie, nazwisko, tel));
				cTab.back().SetID(ID);
				cTab.back().SetLicz(licz);
				cTab.back().SetListWypo(lista);
				this->Nalicz_kare(ID);
				break;
			}
			count++;
		}
}
void Baza::Wczytaj_ks(ifstream& ks){
	string tekst;
	int count = 1, ID, cIDwypo, dzien, miesiac, rok;
	string tytul, autor, wydaw, opis;
	float kara;
	size_t slash;
	date dataWypo;
	while (!ks.eof()){
		getline(ks, tekst);
		size_t found = tekst.find(":"); // szukanie pozycji pierwszego dwukropka w lancuchu
		if (found != -1) tekst.erase(tekst.begin(), tekst.begin() + found + 2); // usuwa wszystko co przed pierwszym drukropkiem oraz ": "

		switch (count % 9){
		case 1:
			tytul = tekst;
			break;
		case 2:
			ID = stoi(tekst);
			break;
		case 3:
			autor = tekst;
			break;
		case 4:
			wydaw = tekst;
			break;
		case 5:
			opis = tekst;
			break;
		case 6:
			kara = stof(tekst);
			break;
		case 7:
			cIDwypo = stoi(tekst);
			break;
		case 8:
			slash = tekst.find("/");
			rok = stoi(tekst.substr(0, slash));
			tekst.erase(tekst.begin(), tekst.begin() + slash + 1);
			slash = tekst.find("/");
			miesiac = stoi(tekst.substr(0, slash));
			tekst.erase(tekst.begin(), tekst.begin() + slash + 1);
			dzien = stoi(tekst);
			dataWypo = date(rok, miesiac, dzien);
			break;
		default:
			kTab.push_back(Ksiazka(tytul, kara, autor, wydaw, opis));
			kTab.back().SetID(ID);
			kTab.back().SetIDWypo(cIDwypo);
			kTab.back().SetDataWypo(dataWypo);
			break;
		}
		count++;
	}
}
void Baza::Wypozycz(){
	int cID;
	cout << "Podaj numer legitymacji czytelnika (cID): " << endl;
	cin >> cID;
	vector<Czytelnik>::iterator cIter = find(cTab.begin(), cTab.end(), cID);
	if (cIter != cTab.end()){ // sprawdzenie, czy udalo sie znalezc czytelnika
		if (cIter->Mozna_wypo()){
			int wID;
			cout << "Podaj numer katalogowy ksiazki do wypozyczenia (wID): " << endl;
			cin >> wID;
			vector<Ksiazka>::iterator wIter = find(kTab.begin(), kTab.end(), wID);
			if (wIter != kTab.end()){ // sprawdzenie, czy udalo sie znalezc ksiazke{
				if (wIter->Mozna_wypo()){
					cIter->SetLicz(cIter->GetLicz() + 1);
					cIter->Wypozycz(wID);
					wIter->SetIDWypo(cID);
					wIter->SetDataWypo(second_clock::local_time().date());
				}
				else
					cerr << "Tej ksiazki nie mozna wypozyczyc!" << endl;
			}
			else
				cerr << "Podano niepoprawny numer katalogowy (wID)!" << endl;
		}
		else
			cerr << "Czytelnik nie moze wypozyczyc ksiazki!" << endl;
	}
	else
		cerr << "Podano niepoprawny numer legitymacji (cID)!" << endl;

}
void Baza::Zwroc(){
	int wID;
	cout << "Podaj numer katalogowy (wID) ksiazki do zwrotu: " << endl;
	cin >> wID;
	vector<Ksiazka>::iterator wIter = find(kTab.begin(), kTab.end(), wID);
	if (wIter != kTab.end()){
		vector<Czytelnik>::iterator cIter = find(cTab.begin(), cTab.end(), wIter->GetIDWypo()); // tutaj nie dopisano juz IFa, gdyz nie spodziewana jest sytuacja,
		cIter->Zwroc(wID);																		// ze wypozyczona ksiazka nie bedzie miala czytelnika
		cIter->SetLicz(cIter->GetLicz() - 1);
		wIter->SetIDWypo(0);
	}
	else
		cerr << "Podano niepoprawny numer katalogowy (wID)!" << endl;
}
void Baza::Nalicz_kare(const int cID){
	vector<Czytelnik>::iterator cIter = find(cTab.begin(), cTab.end(), cID);
	list<int> lista = cIter->GetListWypo();
	int wID;
	float kara = 0;
	for (list<int>::iterator iter = lista.begin(); iter != lista.end(); ++iter){
		wID = *iter;
		vector<Ksiazka>::iterator kIter = find(kTab.begin(), kTab.end(), wID);
		int liczDni = (second_clock::local_time().date() - kIter->GetDataWypo()).days();
		if (liczDni > 30)
			kara += kIter->GetKara()*(liczDni - 30); // preztrzymanie POWYZEJ 30 dni
		else
			kara = 0;
	}
	cIter->SetKara(kara);
}
