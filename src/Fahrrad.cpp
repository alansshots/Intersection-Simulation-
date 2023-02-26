/*
 * Fahrrad.cpp
 *
 *      Author: Alen Gospodinov
 */

#include "Fahrrad.h"
#include <iomanip>
#include <cmath>
#include <memory>
#include <iostream>

using namespace std;

double Fahrrad::dGeschwindigkeit() const
{
	if (p_dGesamtStrecke >= 20)
	{
		double dspeed = std::pow(0.9, (int)p_dGesamtStrecke / 20) * p_dMaxGeschwindigkeit; //aktuelle Geschwindigkeit = geschwindigkeit * (0,9)^(Gesamtstrecke/20km)

		if (dspeed >= 12)
		{
			return dspeed;
		}

		else
		{
			return 12;
		}
	}

	else
	{
		return p_dMaxGeschwindigkeit;
	}

};

Fahrrad::Fahrrad(string sName, double dMaxGeschwindigkeit) : Fahrzeug(sName, dMaxGeschwindigkeit){
};


void Fahrrad::vZeichnen(const Weg& street) const {
	double RelPosition = this->getAbschnittStrecke() / street.getLaenge(); //realtive Position des Fahrrads zur Laenge des Weges:
																	  //Wert zwichen 0 & 1.
	string WegName = street.getName(); //Name des Weges.
	string PKWName = this->getName(); //Name des Fahrrads.
	double KmH = this->dGeschwindigkeit(); //Geschwindigkeit des Fahrrads in KmH.

	bZeichneFahrrad(PKWName, WegName, RelPosition, KmH); //Zeichnen des Fahrrads.
}

Fahrrad::~Fahrrad(){
}





