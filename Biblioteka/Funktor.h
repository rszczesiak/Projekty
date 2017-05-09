#ifndef __FUNKTOR_H__
#define __FUNKTOR_H__

#include <cstdlib>
#include <iostream>
#include "Osoba.h"
#include "Wolumen.h"

using namespace std;

template <class T>
class Strumien{
public:
	virtual void operator ()(const T& obj) = 0;
};

template <class T>
class Drukuj : public Strumien<T> {
	ostream& os;
public:
	Drukuj(ostream& s) : os(s) {}
	void operator () (const T& obj){
		obj.Drukuj(os);
	}
};

#endif __FUNKTOR_H__