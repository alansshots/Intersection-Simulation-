/*
 * Fahrrad.h
 *
 *      Author: Alen Gospodinov
 */

#ifndef FAHRRAD_H_
#define FAHRRAD_H_
#include <string>
#include "Fahrzeug.h"
#include "Weg.h"

using namespace std;

class Fahrrad : public Fahrzeug  {
	public:
		double dGeschwindigkeit() const override;
		Fahrrad(string sName, double dMaxGeschwindigkeit);
		void vZeichnen(const Weg& street) const override;
		~Fahrrad();
};

#endif /* FAHRRAD_H_ */
