#include "Verhalten.h"
#include "Weg.h"
#include "Fahrzeug.h"

//Der Konstruktor der Klasse übergibt den Inhalt des eingegebenen Weges
//über einen Referenzaufruf an street1, um die Erstellung einer lokalen Kopie zu vermeiden.
Verhalten::Verhalten(Weg& strasse1):strasse(strasse1){

}

Weg& Verhalten::getWeg() const{
	return strasse;
}

Verhalten::~Verhalten(){

}
