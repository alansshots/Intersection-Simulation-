#ifndef VERHALTEN_H_
#define VERHALTEN_H_

#pragma once
#include <iostream>
#include <string>
#include <iomanip>

class Weg;
class Fahrzeug;

using namespace std;

class Verhalten {

	public:
		Verhalten(Weg& strasse);

		virtual double dStrecke(Fahrzeug& fahrzeug, double Startzeit) = 0; //virtuel weil Verhalten Oberklasse ist

		Weg& getWeg() const;

		virtual ~Verhalten();

	protected:
		Weg& strasse;
		Weg* p_pWeg;

};

#endif
