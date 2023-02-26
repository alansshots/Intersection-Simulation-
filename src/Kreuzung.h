#ifndef KREUZUNG_H_
#define KREUZUNG_H_

#pragma once
#include "Simulationsobjekt.h"
#include <list>
#include <memory>
#include <string>
#include <random>

#include "Fahrzeug.h"
#include "Simulationsobjekt.h"
#include "Tempolimit.h"

class Weg;
class Kreuzung : public Simulationsobjekt {

	public:
    	Kreuzung();
    	Kreuzung(string sName, double dTank);
    	static void vVerbinde(shared_ptr<Kreuzung> kreuzung1 , shared_ptr<Kreuzung> kreuzung2,string sNameH, string sNameR, double dLaenge, bool bUeberholverbot = true, Tempolimit eLimit = Tempolimit::Autobahn);
    	void vTanken(Fahrzeug& fahrzeug);
    	void vAnnahme(unique_ptr<Fahrzeug> pFahrzeug, double dStartzeitpunkt);
    	void vSimulieren();
    	void Zeichnen();

    	Weg& pZufaelligerWeg(Weg& weg);

    	double getTankinhalt();

    	virtual ~Kreuzung();

	private:
    	double p_dTankstelle;
    	list<shared_ptr<Weg>>p_pWege;
};

#endif
