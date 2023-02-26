#include "Kreuzung.h"
#include "Weg.h"
#include "Simulationsobjekt.h"
#include "Tempolimit.h"

Kreuzung::Kreuzung() : Simulationsobjekt() {
	cout << "Default Konstruktor" << endl;
	cout << "# erzeugte Kreuzung: " << p_sName << endl;
	cout << "ID#: " << p_iID << endl;
}

Kreuzung::Kreuzung(string sName, double dTank) :Simulationsobjekt(sName), p_dTankstelle(dTank) {
	cout << "Konstruktor" << endl;
	cout << "# erzeugte Kreuzung: " << p_sName << endl;
	cout << "ID#: " << p_iID << endl;
}

void Kreuzung::vVerbinde(shared_ptr<Kreuzung> kreuzung1, shared_ptr<Kreuzung> kreuzung2, string sNameH, string sNameR, double dLaenge, bool bUeberholverbot, Tempolimit eLimit) {
	shared_ptr<Weg> pWegHin = make_shared<Weg>(sNameH, dLaenge, bUeberholverbot, Tempolimit::Innerorts); //Hinweg
	shared_ptr<Weg> pWegRueck = make_shared<Weg>(sNameR, dLaenge, bUeberholverbot, Tempolimit::Innerorts); //Rueckweg

	weak_ptr<Weg> pWegHW = pWegHin;
	weak_ptr<Weg> pWegRW = pWegRueck;
	weak_ptr<Kreuzung> pKreuzung1W = kreuzung1;
	weak_ptr<Kreuzung> pKreuzung2W = kreuzung2;

	pWegHin->setRueckWeg(pWegRW); //Rueckweg wird gesetzt
	pWegRueck->setRueckWeg(pWegHW);
	pWegHin->setZielKreuzung(pKreuzung2W); // setzen der Zielkreuzung
	pWegRueck->setZielKreuzung(pKreuzung1W);

//	Die beiden Straßen werden in die Liste der Straßen der jeweiligen Kreuzung eingetragen

	kreuzung1->p_pWege.push_back(pWegHin); // kreuzung1 bekommt WegH
	kreuzung2->p_pWege.push_back(pWegRueck); // kreuzung2 bekommt WegR


}

void Kreuzung::vTanken(Fahrzeug& fahrzeug) {
	if (p_dTankstelle > 0)
	{
		double dMenge = fahrzeug.dTanken(); //Tanken

		p_dTankstelle -= dMenge;

		if (p_dTankstelle < 0)
		{
			p_dTankstelle = 0;
		}
	}
}

double Kreuzung::getTankinhalt()
{
	return p_dTankstelle;
}


void Kreuzung::vAnnahme(unique_ptr<Fahrzeug> pFahrzeug, double dStartzeitpunkt) {
	pFahrzeug->dTanken();
	p_pWege.front()->vAnnahme(move(pFahrzeug), dStartzeitpunkt); //Fahrzeug wird auf ersten Weg gesetzt
}

void Kreuzung::vSimulieren()
{
	for (auto it = p_pWege.begin(); it != p_pWege.end(); it++)
	{
		(*it)->vSimulieren();
	}
}

Weg& Kreuzung::pZufaelligerWeg(Weg& weg) {
	static mt19937 device(0); //Zufallszahlen
	uniform_int_distribution<int> dist(1,p_pWege.size()); //Anzahl der mit der Kreuzung verbundenen Straßen.

	if (p_pWege.size() == 1)
	{
		return *p_pWege.front();
	}
	else
	{
		while (true)
		{
			int random = dist(device);
			int i = 1;
			shared_ptr<Weg> pWegNeu;

			for (auto it = p_pWege.begin(); it != p_pWege.end(); it++, i++)
			{
				if (i == random) //random-mal iteriert
				{
					pWegNeu = *it; //gefundener Weg wird in pWegNeu zwischengespeichert
					break;
				}
			}
			if (pWegNeu != weg.getRueckWeg().lock())
			{
				return *pWegNeu;
			}
			// Wenn Rueckweg ist, dann widerholen
		}
	}
}

void Kreuzung::Zeichnen()
{
	for (auto it = p_pWege.begin(); it != p_pWege.end(); it++)
	{
		(*it)->vZeichnen();
	}
}

Kreuzung::~Kreuzung() {

}
