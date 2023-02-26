#pragma once
#include "Fahrzeug.h"
#include "Simulationsobjekt.h"
#include "SimuClient.h"
#include "Fahrausnahme.h"
#include "Kreuzung.h"
#include <iomanip>

class Streckenende : public Fahrausnahme {

	public:
		Streckenende(Fahrzeug& fahrzeug, Weg& strasse);

		void vBearbeiten() override;

		virtual ~Streckenende();
};

