#include "Streckenende.h"
#include <iomanip>

Streckenende::Streckenende(Fahrzeug& fahrzeug, Weg& strasse):
	Fahrausnahme(fahrzeug, strasse) {
}

void Streckenende::vBearbeiten()
{
	cout << "Art der Ausnahme: Streckenende " << endl;
	cout << "Name des Fahrzeuges: " << fahrzeugObj.getName() << endl;
	cout << "Weg: " << strasseObj.getName() << endl;
	shared_ptr<Kreuzung> pKreuzung = strasseObj.getZielKreuzung().lock(); // weak to sheared pointer
	bLoescheFahrzeug(fahrzeugObj.getName());
	unique_ptr<Fahrzeug> pFahrzeug1Kopie = strasseObj.pAbgabe(fahrzeugObj);
	Weg& weg = pKreuzung->pZufaelligerWeg(strasseObj);
	pKreuzung->vTanken(fahrzeugObj);//Fahrzeug wird aufgetankt
	weg.vAnnahme(move(pFahrzeug1Kopie));//auf Weg setzen
	cout << setiosflags(ios::left) << setw(14) << "ZEIT" << setw(40) << ": [ "+ to_string(dGlobaleZeit) << " ]" << endl
		<< setw(14) << "KREUZUNG" << setw(40) << ": [ " + pKreuzung->getName() + " Der Inhalt ist " + to_string(pKreuzung->getTankinhalt()) + "l" << " ]" << endl
		<< setw(14) << "WECHSEL" << setw(40) << ": [ " + strasseObj.getName() + " -> " + weg.getName() << " ]" << endl
		<< setw(14) << "FAHRZEUG" << setw(40) << ": [ " + fahrzeugObj.getName() << " ]" << endl;
}

Streckenende::~Streckenende() {

}
