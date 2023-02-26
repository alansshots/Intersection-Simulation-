#pragma once
#include "Verhalten.h"

class Parken : public Verhalten {
private:
    double p_dStartzeit; //startzeit eines Fahrzeuges: von "Parken" zu "Fahren".

public:
    Parken(Weg& strasse, double zeit); //zweiter Parameter fuer Startzeit.
    double dStrecke(Fahrzeug& fahrzeug, double Startzeit) override;
    virtual ~Parken();
};

