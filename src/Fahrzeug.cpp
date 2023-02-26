//============================================================================
// Name        : Fahrzeug.cpp
// Author      : Alen Gospodinov
//============================================================================

#include <iomanip>
#include <ios>
#include <memory>
#include <iostream>

#include "Fahrzeug.h"
#include "Verhalten.h"
#include "Fahren.h"
#include "Parken.h"

using namespace std;

int Fahrzeug::p_iMaxID = 0;

Fahrzeug::Fahrzeug():Simulationsobjekt(""){
	cout << "Fahrzeug mit Name:" << p_sName << "; ID = " << p_iID << " wurde erstellt" << endl;
	cout << "" << endl;
}

//Mit Nameangabe
Fahrzeug::Fahrzeug(string name):Simulationsobjekt(name) {
	cout << "Fahrzeug mit Name: " << p_sName << " und ID#: " << p_iID << " wurde mit nicht-Standardkonstruktors erstellt." << endl;
	cout << "" << std::endl;
}

//Mit Nameangabe und MaxGeschwindigkeit
Fahrzeug::Fahrzeug(string name, double maxGeschwindigkeit) :
	Simulationsobjekt(name), p_dMaxGeschwindigkeit((maxGeschwindigkeit > 0) ? maxGeschwindigkeit:0) {

		cout << "Konstruktor mit name & max Geschwindigkeit, Fahrzeug: " << p_sName << "; Max Geschwindigkeit: "<< p_dMaxGeschwindigkeit << "; ID = "<< p_iID << endl;
}

Fahrzeug::~Fahrzeug(){
		cout << "Fahrzeug geloescht: " << p_sName << " " << p_iID << endl;
};

void Fahrzeug::vKopf(){
	Simulationsobjekt::vKopf();
	cout << setiosflags(ios::left)
		<< setw(5) << "ID"
		<< right
		<< setw(10) << "Name"
		<< setw(30) << "MaxGeschwindigkeit(km/h)"
		<< setw(20) << "Gesamtstrecke(km)"
		<< setw(25) << "Geschwindigkeit(km/h)"
		<< setw(20) << "Tankinhalt(L)"
		<< endl;
	cout << setfill('-') << setw(110)<< "" << setfill(' ') << endl;

};

void Fahrzeug::vAusgabe(){
	cout << setiosflags(ios::right)
			<< setw(6) << p_iID
			<< setw(10) << p_sName
			<< setw(20) << p_dMaxGeschwindigkeit
			<< setw(20) << p_dGesamtStrecke
			<< setw(25) << dGeschwindigkeit();
	cout << endl;
};

//---------------Simulationsfunktion des einzelnen Fahrzeuges----------------
void Fahrzeug::vSimulieren()
{
	if (dGlobaleZeit > p_dZeit)
		{
			double dPeriode = dGlobaleZeit - p_dZeit; //dPeriode = takt
			double dNeueStrecke = p_pVerhalten->dStrecke(*this, dPeriode);
			p_dAbschnittStrecke += dNeueStrecke; //Aktuelle Strecke
			p_dGesamtStrecke += dNeueStrecke; //Gesamtstrecke .
			p_dZeit += dPeriode; //aktualisiern nach dem Takt.
			p_dGesamtZeit += dPeriode; //gesamtzeit
		}
}

//Getters

double Fahrzeug::dGeschwindigkeit() const
{
	return p_dMaxGeschwindigkeit;
};

int Fahrzeug::check_type()
{
	return 0;
};

string Fahrzeug::getName() const {
	return p_sName;
};

double Fahrzeug::getAbschnittStrecke() const {
	return p_dAbschnittStrecke;
}

double Fahrzeug::dTanken(double dMenge)
{
	if(dMenge != std::numeric_limits<double>::infinity())
	{
		dMenge = 0;
	}
	return dMenge;
};

void Fahrzeug::vAusgabe(ostream& oStream){
	Simulationsobjekt::vAusgabe(oStream);
	oStream << setiosflags(ios::right)
		<< setw(6) << this->p_iID
		<< setw(10) << this->p_sName
		<< setw(20) << this->p_dMaxGeschwindigkeit
		<< setw(20) << this->p_dGesamtStrecke
		<< setw(25) << this->dGeschwindigkeit();
};

//ostream& operator<<(ostream& oStream, Fahrzeug& fahrzeug){
//	fahrzeug.vAusgabe(oStream);
////	os << "overload" << endl;
//	return oStream;
//}

void Fahrzeug::vZeichnen(const Weg& street) const {

}

void Fahrzeug::operator=(const Fahrzeug& vehicle) {
	Simulationsobjekt::operator=(vehicle);
	this->p_dMaxGeschwindigkeit = vehicle.p_dMaxGeschwindigkeit;
}

bool Fahrzeug::operator<(const Fahrzeug& vehicle2) const {
	return (this->p_dGesamtStrecke < vehicle2.p_dGesamtStrecke);
}

//Erstellen eines neuen Verhaltens von einem fahrenden Fahrzeug in einem bestimmten Weg
void Fahrzeug::vNeueStrecke(Weg& street) {
	p_pVerhalten = make_unique<Fahren>(street); //Alte Instantz (Weg) wird geloescht.
	this->p_dAbschnittStrecke = 0;
}

//Erstellen eines neuen Verhalten von einem parkenden Fahrzeuges in einem bestimmten Weg
void Fahrzeug::vNeueStrecke(Weg& street, double Startzeit)
{
	if (Startzeit >= dGlobaleZeit)
	{
		p_pVerhalten = make_unique<Parken>(street, Startzeit); ////Alte Instantz (Weg) wird geloescht.
		this->p_dAbschnittStrecke = 0;
	}
}

