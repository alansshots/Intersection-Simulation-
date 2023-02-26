#pragma once
#include "Fahrausnahme.h"
class Losfahren : public Fahrausnahme {

	public:
		Losfahren(Fahrzeug& fahrzeug, Weg& strasse);

    	void vBearbeiten() override;

    	virtual ~Losfahren();
};

