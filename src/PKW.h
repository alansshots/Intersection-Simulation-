/*
 * PKW.h
 *
 *      Author: Alen Gospodinov
 */
#ifndef PKW_H_
#define PKW_H_
#include <string>
#include <limits>
#include "Fahrzeug.h"
#include "Weg.h"
using namespace std;

class PKW : public Fahrzeug {
	private:
	    double p_dVerbrauch = 0; //Oel-Verbaruch in Liter/100km
	    double p_dTankvolumen = 0; //Tankvolumen in Liter p_dTankvolumen
	    double p_dTankinhalt = 0; //in Liter

	public:
	    PKW(string sName);
	    PKW(string sName, double dMaxGeschwindigkeit);
	    PKW(string sName, double dMaxSpeed, double dVerbrauch, double dTankvolumen = 55); //default parameter f�r Volumen, muss auch immer als letztes stehen
	    double dTanken(double dMenge = std::numeric_limits<double>::infinity()) override;
	    void vSimulieren() override;
	    virtual void vAusgabe() override;
	    virtual void vAusgabe(ostream& oStream) override;
	    void vZeichnen(const Weg& street) const override;

	    virtual ~PKW();
};


#endif /* PKW_H_ */

