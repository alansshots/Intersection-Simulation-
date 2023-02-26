#include "Losfahren.h"
#include "Fahrzeug.h"
#include "Weg.h"

Losfahren::Losfahren(Fahrzeug& fahrzeug, Weg& strasse):Fahrausnahme(fahrzeug, strasse) {

}

void Losfahren::vBearbeiten()
{
	cout << "Das Fahrzeug: " << fahrzeugObj.getName() << endl;
	cout << "Der Weg: " << strasseObj.getName() << endl;
	cout << "Ausnahmeart: Losfahren";
	cout << " " << endl;
	cout << " " << endl;

	fahrzeugObj.vNeueStrecke(strasseObj); //parkende Fahrzeuge fahren los.
}


Losfahren::~Losfahren() {
}
