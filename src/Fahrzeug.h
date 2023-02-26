/*
 * Fahrzeug.h
 *
 *      Author: Alen Gospodinov
 */

#ifndef FAHRZEUG_H_
#define FAHRZEUG_H_
#include <limits>
#include <string>
#include <iostream>
#include "Simulationsobjekt.h"
#include "Verhalten.h"

class Weg;

using namespace std;

extern double dGlobaleZeit;

class Fahrzeug: public Simulationsobjekt {
	private:
	static int p_iMaxID;

	protected:
		double p_dZeit = 0;
		double p_dStreckeGefahren = 0;
		double p_dMaxGeschwindigkeit = 0;
		double p_dGesamtStrecke = 0; //die bisher zuruckgelegte Gesamtstrecke
		double p_dAbschnittStrecke = 0; //die bisher zuruckgelegte Gesamtstrecke auf einem Weg. Nicht zu verwechseln mit der Gesamtstrecke!
		double p_dGesamtZeit = 0; //die gesamte Fahrzeit des Objektes
		unique_ptr<Verhalten> p_pVerhalten = nullptr; //jedes Fahrzeug besitzt ein eigenes "Verhalten-Objekt", das nicht geteilt wird.


	public:
		Fahrzeug();
		Fahrzeug(string name);
		Fahrzeug(string name, double maxGeschwindigkeit);

		static void vKopf();
		virtual void vAusgabe();
		virtual void vSimulieren() override;
		virtual double dTanken(double dMenge = std::numeric_limits<double>::infinity());
		virtual void vAusgabe(ostream& oStream);

		virtual double dGeschwindigkeit() const;
		virtual int check_type();
		virtual string getName() const;
		double getAbschnittStrecke() const;


		void vNeueStrecke(Weg&);
		void vNeueStrecke(Weg&, double);

		virtual void vZeichnen(const Weg&) const;
		void operator=(const Fahrzeug&);
		bool operator<(const Fahrzeug&) const;

		virtual ~Fahrzeug();
		Fahrzeug(const Fahrzeug&) = delete;

};

ostream& operator<<(ostream& oStream, const Fahrzeug& fahrzeug);


#endif /* FAHRZEUG_H_ */
