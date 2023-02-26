#include "Weg.h"
#include "Fahrzeug.h"
#include "Verhalten.h"
#include "Fahrausnahme.h"
#include "vertagt_liste.h"
using namespace std; 

Weg::Weg():Simulationsobjekt() {
}

Weg::~Weg() {
}

Weg::Weg(string sName, double dLaenge, Tempolimit eLimit):
	sName(sName), Simulationsobjekt(sName), p_dLaenge(dLaenge), p_eTempolimit(eLimit) {
};

Weg::Weg(string sName, double dLaenge,bool bUeberholverbot, Tempolimit eLimit):
	sName(sName), Simulationsobjekt(sName), p_dLaenge(dLaenge),p_bUeberholverbot(bUeberholverbot), p_eTempolimit(eLimit) {
};

//Getters:
double Weg::getTempolimit() {
	return (double) p_eTempolimit;
}

double Weg::getLaenge() const {
	return p_dLaenge;
}

string Weg::getName() const {
	return sName;
}

weak_ptr<Kreuzung> Weg::getZielKreuzung() {
	return p_pZielKreuzung;
}

weak_ptr<Weg> Weg::getRueckWeg() {
	return p_pRueckWeg;
}

//list<unique_ptr<Fahrzeug>> Weg::pGetList() {
//	return p_pFahrzeuge;
//}

//Getters end

void Weg::vSimulieren() {

	if (!p_pFahrzeuge.empty()) {

		for (auto& it : p_pFahrzeuge) {
			try {
				it->vSimulieren();
			} catch (Fahrausnahme* fahrausnahme) {
				fahrausnahme->vBearbeiten();
				delete fahrausnahme;
			}
		}
	}

	p_pFahrzeuge.vAktualisieren();
}

//void Weg::vKopf() {
//	cout << setiosflags(ios::left)
//			<< setw(7) << "ID" << " | "
//			<< setw(15) << "Name" << " | "
//			<< setw(20) << "Laenge" << " | "
//			<< setw(30) << "Fahrzeuge"
//			<< endl;
//	cout << setfill('-') << setw(110)<< "" << setfill(' ') << endl;
//}

void Weg::vKopf() {
	Simulationsobjekt::vKopf();
	cout << resetiosflags(ios::left);
	cout << setw(28) << "|  Laenge" << setw(20) << "|  Fahrzeuge" << endl;
	cout << setfill('-') << setw(110)<< "" << setfill(' ') << endl;
}

void Weg::vAusgabe(ostream& oStream) const {
	string sAlleFahrzeuge = "";

	for (auto& Mitglied : p_pFahrzeuge){
		sAlleFahrzeuge = sAlleFahrzeuge + " " + Mitglied->getName(); //Uebergeben aller Fahrzeuge auf dem Weg in einem String,damit die demnaechst ausgegeben werden.
	}

	Simulationsobjekt::vAusgabe(oStream);
	oStream << resetiosflags(ios::right);
	oStream << setw(15) << ":" << setw(10) << p_dLaenge << setw(10) << setprecision(5) << "(" << sAlleFahrzeuge << ")" << endl;
}

unique_ptr<Fahrzeug> Weg::pAbgabe(const Fahrzeug& fahrzeug)
{
	for (auto it = p_pFahrzeuge.begin(); it != p_pFahrzeuge.end(); it++)
	{
		if ((*it != nullptr) && (**it == fahrzeug))
		{
			unique_ptr<Fahrzeug>pFahrzeugLokal = move(*it); //Zwischenspeicherung
			p_pFahrzeuge.erase((it));
			return pFahrzeugLokal;
		}
	}
	return nullptr;
}

void Weg::vZeichnen() {

	if (!p_pFahrzeuge.empty())
	{
		for (auto& it : p_pFahrzeuge)
		{
			it->vZeichnen(*this);
		}
	}
}

// Setters
void Weg::setZielKreuzung(weak_ptr<Kreuzung> pZielKreuzung) {
	p_pZielKreuzung = pZielKreuzung;
}

void Weg::setRueckWeg(weak_ptr<Weg> pRueckWeg) {
	p_pRueckWeg = pRueckWeg;
}


//Fahrzeug zum Weg hinzufügen
void Weg::vAnnahme(unique_ptr<Fahrzeug> fahrzeuge) {
	fahrzeuge->vNeueStrecke(*this); //signalisiert
	p_pFahrzeuge.push_back(move(fahrzeuge));
}

//dasselbe, aber für geparkte Fahrzeuge, deshalb brauchen wir eine variable Startzeit
void Weg::vAnnahme(unique_ptr<Fahrzeug> fahrzeuge, double Startzeit) {
	fahrzeuge->vNeueStrecke(*this, Startzeit); //signalisiert
	p_pFahrzeuge.push_front(move(fahrzeuge));
}


