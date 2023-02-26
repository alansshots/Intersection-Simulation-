#ifndef WEG_H_
#define WEG_H_

#pragma once
#include <list>
#include <memory>
#include "Simulationsobjekt.h"
#include "Tempolimit.h"
#include "vertagt_liste.h"
#include "Kreuzung.h"

using namespace std;
class Verhalten;
class Fahrausnahme;
class Fahrzeug; //Anstatt die Headerdatei zu inkludieren, kann man einfach die Klasse hier deklaririen, um z.B Rekursion zu vermeiden

class Weg : public Simulationsobjekt {
public:
    Weg(); //Standardkonstruktor
    Weg(string sName, double dLaenge, Tempolimit eLimit = Tempolimit::Autobahn);
    Weg(string sName, double dLaenge,bool bUeberholverbot = true, Tempolimit eLimit = Tempolimit::Autobahn);
    vertagt::VListe<unique_ptr<Fahrzeug>> p_pFahrzeuge; //Liste aller Fahrzeuge auf dem Weg.

    static void vKopf();
    void vAusgabe(ostream& oStream) const override;
    void vSimulieren() override;

    string getName() const;
    double getLaenge() const;
    double getTempolimit();

    void vAnnahme(unique_ptr<Fahrzeug>);
    void vAnnahme(unique_ptr<Fahrzeug>, double); //parkend und fahrend unterschied
    void vZeichnen();
    unique_ptr<Fahrzeug> pAbgabe(const Fahrzeug& fahrzeug);
//    list<unique_ptr<Fahrzeug>> pGetList();

    void setZielKreuzung(weak_ptr<Kreuzung> pZielKreuzung);
    void setRueckWeg(weak_ptr<Weg> pRueckWeg);
    weak_ptr<Kreuzung> getZielKreuzung();
    weak_ptr<Weg> getRueckWeg();


    virtual ~Weg();
    Weg(const Weg&) = delete; //copy-konstruktor verbot

private:
    double p_dLaenge = 0;
    Tempolimit p_eTempolimit;
    string sName = "";
    bool p_bUeberholverbot;
    double p_dVirtuelleSchranke;
    weak_ptr<Kreuzung> p_pZielKreuzung ;
    weak_ptr<Weg> p_pRueckWeg;
};

#endif /* WEG_H_ */

