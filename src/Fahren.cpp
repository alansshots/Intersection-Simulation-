#include "Fahren.h"
#include "Fahrzeug.h"
#include "Weg.h"
#include "Streckenende.h"

//Fuer fahrende Fahrzeuge
double Fahren::dStrecke(Fahrzeug& fahrzeug, double dZeitIntervall)
{
	Weg& strasse = this->getWeg(); //eine Kopie der Strasse, dient zum Vereinfachen der unteren Anweisungen.

	double dStreckeMax = dZeitIntervall * fahrzeug.dGeschwindigkeit(); //die fahrbare Strecke vom Fahrzeug in dem gegebenen Zeitintervall
																   //anhand seiner Gschwindigkeit.
	double dRestStrecke = strasse.getLaenge() - fahrzeug.getAbschnittStrecke(); //die restliche Strecke eines Weges.

	if (dStreckeMax > dRestStrecke)
	{
		cout << " " << fahrzeug.getName() << " ist am Ende des Weges angekommen" << endl;
		Streckenende* streckenende= new Streckenende(fahrzeug, strasse);
		throw streckenende;  //die zugehoerige Fahrausnahme wird hier geworfen.
}

	return dStreckeMax;

	//wenn die Summe der vom Fahrzeug fahrbare Strecke und der Reststrecke des Weges groesser ist als der Weg,
	//dann ist die dStreckeMax nicht realisierbar.
}

Fahren::~Fahren(){

}
