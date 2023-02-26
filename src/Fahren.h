#pragma once
#include "Verhalten.h"
#include "Streckenende.h"
class Fahren : public Verhalten{
	public:
    	Fahren(Weg& strasse):Verhalten(strasse) {};
    	double dStrecke(Fahrzeug&, double dZeitIntervall) override;
    	virtual ~Fahren();
};
