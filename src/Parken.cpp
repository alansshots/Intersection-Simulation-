#include "Parken.h"
#include "Fahrzeug.h"
#include "Losfahren.h"

Parken::Parken(Weg& strasse, double zeit):Verhalten(strasse), p_dStartzeit(zeit) {
}

double Parken::dStrecke(Fahrzeug& fahrzeug, double Startzeit)
{
	if (dGlobaleZeit >= p_dStartzeit)
	{
		cout << fahrzeug.getName() << " hat Startzeit erreicht" << endl;
		Losfahren* losfahren= new Losfahren(fahrzeug, strasse);
		throw losfahren;
	}
	else
	{
		return 0;
	}
}

Parken::~Parken(){

}
