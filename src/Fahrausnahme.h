#pragma once
#include <exception>
#include <stdexcept>
#include "Fahrzeug.h"
#include "Weg.h"
#include "Fahrzeug.h"

class Fahrausnahme : exception {
	protected:
		Fahrzeug& fahrzeugObj;

		Weg& strasseObj;

	public:
		Fahrausnahme(Fahrzeug& fahrzeug, Weg& strasse);

		virtual void vBearbeiten() = 0;

		virtual ~Fahrausnahme();
};


