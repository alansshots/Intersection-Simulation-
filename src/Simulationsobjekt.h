#ifndef SIMULATIONSOBJEKT_H_
#define SIMULATIONSOBJEKT_H_

#pragma once
#include <iostream>
#include <string>
#include <iomanip>
#include "SimuClient.h"
using namespace std;

class Simulationsobjekt {

	public:
		Simulationsobjekt();
		Simulationsobjekt(string Name);

		static void vKopf();
		virtual void vAusgabe(ostream& oStream = cout) const;
		virtual void vSimulieren() = 0;

		string getName() const;

		virtual void operator=(const Simulationsobjekt&);
		virtual bool operator==(const Simulationsobjekt&);

		Simulationsobjekt(const Simulationsobjekt&) = delete;
		virtual ~Simulationsobjekt();


	protected:
		string p_sName  = ""; //Simulationsobjekt Name
		const int p_iID; // Simulationsobjekt ID
		double p_dZeit = 0; //die Zeit, zu der das Simulationsobjekt zuletzt simuliert wurde

	private:
		static int p_iMaxID; //Mit der Klasse verknupft und nicht mit Objekten(deswegen static)

};

ostream& operator <<(ostream& oStream, const Simulationsobjekt& simulationsobjekt);

#endif /* SIMULATIONSOBJEKT_H_ */
