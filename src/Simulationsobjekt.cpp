#include "Simulationsobjekt.h" 

int Simulationsobjekt::p_iMaxID = 0; 

Simulationsobjekt::Simulationsobjekt() : p_iID(++p_iMaxID) {
	cout << "Default Konstruktor, Simulationsobjekt: " << p_sName << "; ID = " << p_iID << endl;
};

Simulationsobjekt::Simulationsobjekt(string name) :
		p_sName(name),
		p_iID(++p_iMaxID)
	{
		cout << "Konstruktor mit name, Simulationsobject: " << p_sName << "; ID = " << p_iID << endl;
};

//Getters
string Simulationsobjekt::getName() const  {
	return p_sName;
};

//<iomanip>
void Simulationsobjekt::vKopf() {
	cout << resetiosflags(ios::left);
	cout << setw(10) << "ID" << setw(15) << "|   Name";
}

Simulationsobjekt::~Simulationsobjekt(){
		cout << "Fahrzeug geloescht: " << p_sName << " " << p_iID << endl;
};

void Simulationsobjekt::vAusgabe(ostream& oStream) const
{
	oStream << setiosflags(ios::right)
			<< setw(10) << p_iID
			<< setw(20) << p_sName << setw(25);
}

//Ueberladung der =operator (kopieren maxGeschwindigkeit und Name)
void Simulationsobjekt::operator=(const Simulationsobjekt& SimObjekt)
{
	//ID ist eine konstante variable und kann nicht bearbeitet werden sobald sie initialisiert wurde.
	this->p_sName = SimObjekt.p_sName + "-Kopie";
}

//Ueberladung der ==operator (ob die IDs stimmen)
bool Simulationsobjekt::operator==(const Simulationsobjekt& SimObjekt)
{
	if (this->p_iID == SimObjekt.p_iID) {
		return true;
	} else {
		return false;
	}
}

ostream& operator<<(ostream& oStream, const Simulationsobjekt& simulationsobjekt) {
	simulationsobjekt.vAusgabe(oStream);
	return oStream;
};

