/*
 * PKW.cpp
 *
 *      Author: Alen Gospodinov
 */

//============================================================================
// Name        : PKW.cpp
// Author      : Alen Gospodinov
//============================================================================
#include <iomanip>
#include <memory>
#include <iostream>
#include <limits>

#include "PKW.h"
#include "Fahrzeug.h"

using namespace std;

PKW::PKW(string sName):
Fahrzeug(sName)
{
	cout << "(Constructor with name) New PKW: " << p_sName << " " << p_iID << " " << p_dVerbrauch << "/" << p_dTankvolumen << endl;
};

PKW::PKW(string sName, double dMaxGeschwindigkeit) :
Fahrzeug(sName, dMaxGeschwindigkeit)
{
	cout << "(Constructor with name & max-speed) New PKW: " << p_sName << " " << p_iID << " " << p_dVerbrauch << "/" << p_dTankvolumen << endl;
};

PKW::PKW(string sName, double dMaxGeschwindigkeit, double dVerbrauch, double dTankvolumen) :
Fahrzeug(sName, dMaxGeschwindigkeit),
	p_dVerbrauch(dVerbrauch),
	p_dTankvolumen(dTankvolumen),
	p_dTankinhalt(dTankvolumen / 2)
{
	cout << "(Konstruktor mit name, maxgeschwindigkeit, verbrauch und Tankvolumen) Neuer PKW: " << p_sName << " " << p_iID << " " << p_dVerbrauch << " " << p_dTankvolumen << endl;
};

PKW::~PKW()
{
	cout << "geloeschter PKW: " << p_sName << " " << p_iID << " " << p_dVerbrauch << " " << p_dTankvolumen << endl;
};

void PKW::vAusgabe(){
    Fahrzeug::vAusgabe();
    double dGesamtVerbrauch = (p_dVerbrauch/100.0) * p_dGesamtStrecke;
    cout << setw(16) << fixed << p_dTankinhalt << setw(17) << fixed << dGesamtVerbrauch;
}

void PKW::vAusgabe(ostream& oStream){
	Fahrzeug::vAusgabe(oStream);
	char buf[20];
	sprintf_s(buf, "%.2f/%.2f", p_dTankinhalt, p_dTankvolumen);
	oStream << setw(20) << buf;
};

double PKW::dTanken(double dMenge)
{
	if(dMenge == std::numeric_limits<double>::infinity()){
		double dMenge = p_dTankvolumen - p_dTankinhalt;
		p_dTankinhalt += dMenge;
		return dMenge;
	}

	double dLeerTank = p_dTankvolumen - p_dTankinhalt;

	//passende Menge ueberpruefen
	while (dMenge > dLeerTank)
	{
		cout << "Oel laeuft ueber! bitte Tankmenge runtersetzen, Sie koennen bis " << dLeerTank << " Liter Tanken." << endl;
		cout << "Tankmenge: ";
		cin >> dMenge;
		cout << "" << endl;
	}

	//Tankinhalt aktualisieren
	p_dTankinhalt += dMenge;
	return dMenge;
};

//Funktion Simuliert Fahrzeuge mit Oel-Verbrauch, dazu wird der Tankinhalt nach jedem Simulationsschritt aktualisiert
void PKW::vSimulieren()
{
	//Ob Tank leer ist, wenn nicht, dann wird weiter gefahren und der Tank aktualisiert sich
	if (p_dTankinhalt > 0)
	{
		double dFahrzeit = dGlobaleZeit - p_dZeit;
		Fahrzeug::vSimulieren();
		double dTankVerbrauch = p_dVerbrauch/ 100*dFahrzeit*dGeschwindigkeit(); //Verbrauchrate*gefahrene strecke seit letztem Simulationsschritt
		p_dTankinhalt -= dTankVerbrauch;
		if (p_dTankinhalt < 0)
		{
			p_dTankinhalt = 0;
		}
	}
	//wenn Leer ist, dann nicht weiter gefahren, sonder kommt eine Frage fur tanken.
	else
	{
		p_dTankinhalt = 0; //Falls der Tank minus Werte hat (Ol) aus der letzten Simulation, wird er auf 0 gesetzt.
		cout << "Tank von "<< this->p_sName << " ist Leer, bitte Tanken!" << endl;
	}
};

void PKW::vZeichnen(const Weg& street) const
{
	double RelPosition = this->getAbschnittStrecke() / street.getLaenge(); //realtive Position des PKWs zur Laenge des Weges: Wert zwichen 0 & 1.

	string WegName = street.getName();
	string PKWName = this->getName();
	double KmH = this->dGeschwindigkeit();
	double Tank = this->p_dTankinhalt;

	bZeichnePKW(PKWName, WegName, RelPosition, KmH, Tank);


}
