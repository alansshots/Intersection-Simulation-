/*
 * main.cpp
 *
 *  Created on: Nov 25, 2022
 *      Author: Alen Gospodinov
 */

//============================================================================
// Name        : Fahrzeug.cpp
// Author      : Alen Gospodinov
//============================================================================
#include <iostream>
#include <memory>
#include <vector>
#include <iomanip>
#include <cmath>
#include <random>

#include "SimuClient.h"
#include "Fahrzeug.h"
#include "PKW.h"
#include "Fahrrad.h"
#include "Simulationsobjekt.h"
#include "Weg.h"
#include "vertagt_liste.h"

using namespace std;

double dGlobaleZeit = 0.0;

void vAufgabe_1(){
	Fahrzeug mercedes("AMG-ONE");
	Fahrzeug porsche("GT3RS");

	Fahrzeug* audi = new Fahrzeug("A5");
	Fahrzeug* bmw = new Fahrzeug("M3");

	auto toyota = make_unique<Fahrzeug>("Supra");
	auto nisan = make_unique<Fahrzeug>("Z-350");

	auto ferrari = make_shared<Fahrzeug>("SF-90");
	auto corvette = make_shared<Fahrzeug>("C8");

	shared_ptr<Fahrzeug> ferrariShared = ferrari;

//	cout << "f7.use_count() = " << ferrari.use_count() << endl;

//	unique_ptr<Fahrzeug> toyotaNew = move(toyota);

	vector<unique_ptr<Fahrzeug>>vectorCars;

//	Fahrzeung* vectorCars = new Fahrzeug();
//	vectorCars.push_back(vectorCars);


//		vectorCars= { move(toyota), move(nisan) };
		vectorCars.push_back(move(toyota));
		vectorCars.push_back(move(nisan));
		vectorCars.clear();//delete toyota, nisan

		vector<shared_ptr<Fahrzeug>> vectorCars2;
		vectorCars2.push_back(ferrari);
		vectorCars2.push_back(move(corvette));
		vectorCars2.clear();//delete f8

		Fahrzeug::vKopf();
		mercedes.vAusgabe();

	delete audi;
	delete bmw;
};

void vAufgabe_1a() {
//	auto a = make_unique<Fahrzeug>("BMW M2", 20);
//	auto b = make_unique<Fahrzeug>("BNW M3", 35);
//	auto c = make_unique<Fahrzeug>("BMW M5", 55);
//
//	vector<unique_ptr<Fahrzeug>>vectorVehicles;

//	vectorVehicles.push_back(move(a));
//	vectorVehicles.push_back(move(b));
//	vectorVehicles.push_back(move(c));

	string fahrzeugName;
	double fahrzeugMaxgeschwindigkeit;
	vector<unique_ptr<Fahrzeug>>vectorVehicles;
	double dZeitschritt = 1.0;

	for(int i=0; i<3; i++){
		cout << "Enter Fahrzeug name: " << endl;
		cin >> fahrzeugName;
		cout << "Enter Fahrzeug Maxgeschwindigkeit: " << endl;
		cin >> fahrzeugMaxgeschwindigkeit;

		auto fahrzeug = make_unique<Fahrzeug>(fahrzeugName, fahrzeugMaxgeschwindigkeit);
		vectorVehicles.push_back(move(fahrzeug));
	};

	for (int i=0; i < 3; i++)
		{
			dGlobaleZeit += dZeitschritt;
			cout << "GlobaleZeit=" << dGlobaleZeit << endl;
			Fahrzeug::vKopf();
			for (int j = 0; j < 3; j++){
				vectorVehicles[j]->vSimulieren();
				vectorVehicles[j]->vAusgabe();
				cout << endl;
			}
			cout << endl;
		};

		vectorVehicles.clear();
};

void vAufgabe_2(){
	int zFahrrad;
	int zPKW;

	vector<unique_ptr<Fahrzeug>> vectorVehicles2; //container der Objekte

		cout << "Anzahl des Fahrraeders?";
		cin >> zFahrrad;
		cout << "\n" << endl;

		for(int i=0; i<zFahrrad;i++) {
			string sName;
			double dGeschwindigkeit;

			cout << "Hier Daten des Fahrrads geben: \n" << i << endl;
			cout << "Name: ";
			cin >> sName;
			cout << "Geschwindigkeit: ";
			cin >> dGeschwindigkeit;
			vectorVehicles2.push_back(move(make_unique<Fahrrad>(sName, dGeschwindigkeit)));


		//Frage im Skript: Warum koennen/sollten Siew keine Fahrzeugobjekte speichern?
//		--> Fahrzeuge ist die Basisklasse, von der man mein Objekt erzeugen kann/sollte, sondern nur von den Unterklassen.
		//Frage im Skript: Warum koennen Sie PKWs und Fahrraeder in einem gemeinsamen Vektor speichern?
//		--> Denn sie sind beide vom selben "Typ", sie sind also beide von derselben Klasse abgeleitet und koennen somit in einem vector-container gespeichert werden.

		cout << "Anzahl des PKWs?";
		cin >> zPKW;
		cout << "\n" << endl;

		for(int i=1; i<zFahrrad;i++) {
			string sName;
			double dGeschwindigkeit;

			cout << "Hier Daten des PKWs geben: \n" << i << endl;
			cout << "Name: ";
			cin >> sName;
			cout << "Geschwindigkeit: ";
			cin >> dGeschwindigkeit;
			vectorVehicles2.push_back(move(make_unique<Fahrrad>(sName, dGeschwindigkeit)));
		}

		for (int i=1; i<=zPKW;i++){

				string sName;
				double dGeschwindigkeit;
				double dVerbrauch;
				double dTankvolumen;

				cout << "Hier Daten des PKW geben: \n" << endl;
				cout << "Name: ";
				cin >> sName;
				cout << "Geschwindigkeit: ";
				cin >> dGeschwindigkeit;
				cout << "Oelverbrauch (in L/100km): ";
				cin >> dVerbrauch;
				cout << "Ist das Tankvolumen bekannt? (j/n) \n";
				string sAntwort;
				cin >> sAntwort;
				if (sAntwort == "j")
				{
					cout << "Tankvolumen (in Liter): ";
					cin >> dTankvolumen;
					vectorVehicles2.push_back(move(make_unique<PKW>(sName, dGeschwindigkeit, dVerbrauch,
						dTankvolumen)));
				}

				else
				{
					vectorVehicles2.push_back(move(make_unique<PKW>(sName, dGeschwindigkeit, dVerbrauch)));
				}
			}


			double dGesamtzeit= 6.0;
			double dTankzeit = 3.0;
			bool bTankstatus;

			for (dGlobaleZeit=0; dGlobaleZeit <= dGesamtzeit; dGlobaleZeit += 1){
				cout << "dGlobaleZeit=" << dGlobaleZeit << endl;
				Fahrzeug::vKopf();

				for (int i=0; i<vectorVehicles2.size(); i++){

					vectorVehicles2[i]->vSimulieren();
					vectorVehicles2[i]->vAusgabe();

					if (dGlobaleZeit == dTankzeit){
						double olMenge;
						cout << "Bitten tanken Sie "<< vectorVehicles2[i]->getName() << ". Geben Sie OL in Liter: " << endl;
						cin >> olMenge;

						vectorVehicles2[i]->dTanken(olMenge);
					}
					cout << endl;
				}
				cout << endl;
			}
		}
}

ostream& operator<<(ostream& oStream, Fahrzeug& fahrzeug){
	fahrzeug.vAusgabe(oStream);
//	oStream << "overload" << endl;
	return oStream;
}

//ostream& operator<<(ostream& oStream, Simulationsobjekt& Simulationsobjekt){
//	Simulationsobjekt.vAusgabe(oStream);
////	oStream << "overload" << endl;
//	return oStream;
//}

void vAufgabe_3() {
//	PKW* car = new PKW("Name", 200);
//
//	car->vSimulieren();
//
//	cout << *car;

	vector<unique_ptr<Fahrzeug>> vectorVehicles3; //ein container zum Testen

		//-----Fahrraeder fur Tests----------------------
	vectorVehicles3.push_back(move(std::make_unique<Fahrrad>("Treck", 35)));
	vectorVehicles3.push_back(move(std::make_unique<Fahrrad>("Speed", 20)));
	vectorVehicles3.push_back(move(std::make_unique<Fahrrad>("Cube", 0)));


		//-------Autos fur Tests-----------------------
	vectorVehicles3.push_back(move(std::make_unique<PKW>("Ford", 60, 13, 60)));
	vectorVehicles3.push_back(move(std::make_unique<PKW>("Polestar", 80, 15, 70)));

		//----------Simulation------------------------
		double dTakt = 0.25; //Takt in 15 minuten
		for (; dGlobaleZeit < 1.25; dGlobaleZeit += dTakt)
		{
			vectorVehicles3[0]->vKopf();
			cout << "\n" << endl;

			for (int i = 0; i < 5; i++)
			{
				vectorVehicles3[i]->vSimulieren();
				cout << *vectorVehicles3[i];
				cout << "\n" << endl;
			}

			cout << "\n" << endl;

		}

		//--------------Operatoren-Test-------------------

		//Nach Simulation wird  zwischen den Autos verglichen (nach Gesamtstrecke).
		if (*vectorVehicles3[3] < *vectorVehicles3[4])
		{
			cout << vectorVehicles3[4]->getName() << " ist weiter gefahren als " << vectorVehicles3[3]->getName() << "." << endl;
			cout << "\n" << endl;
		}
		else if (*vectorVehicles3[4] < *vectorVehicles3[3])
		{
			cout << vectorVehicles3[3]->getName() << " ist weiter gefahren als " << vectorVehicles3[4]->getName() << "." << endl;
			cout << "\n" << endl;
		}
		else
		{
			cout << vectorVehicles3[3]->getName() << "&" << vectorVehicles3[4]->getName() << "sind genauso weit gefahren." << "." << endl;
			cout << "\n" << endl;
		}

		//Fahrraeder werden gleichgesetzt und ausgegeben.
		*vectorVehicles3[2] = *vectorVehicles3[1]; //Die Stammdaten vom Cube-bike werden vom Speed-bike uebernommen

		//Ausgabe
		vectorVehicles3[0]->vKopf();
		cout << (*vectorVehicles3[0]) << endl;
		cout << (*vectorVehicles3[1]) << endl;
		cout << (*vectorVehicles3[2]) << endl;

};

void vAufgabe_4() {

	Weg Templergraben("Weg", 100, Tempolimit::Innerorts);
	Templergraben.vKopf();
	cout << Templergraben;
}

void vAufgabe_5() {
//	vector<unique_ptr<Fahrzeug>> vehicles; //container.
	Weg Weg("Weg", 100, Tempolimit::Innerorts); //Strasse.

	//Addirung von Fahrzeuge zum weg.
	Weg.vAnnahme(make_unique<Fahrzeug>("Audi"));
	Weg.vAnnahme(make_unique<Fahrzeug>("BMW"));
	Weg.vAnnahme(make_unique<Fahrzeug>("Porsche"));

	//-------------die Simulation--------------
	Weg.vKopf();
	Weg.vSimulieren();
	cout << Weg << endl;

}

void vAufgabe_6_test() {
		Weg weg1("Landstrasse", 200, Tempolimit::Landstrasse);
		Weg weg2("Innerorts", 300, Tempolimit::Innerorts);
		weg1.vAnnahme(make_unique<PKW>("Mercedes",200,6,60));
		weg2.vAnnahme(make_unique<Fahrrad>("BMX", 25));
		weg1.vAnnahme(make_unique<PKW>("Audi", 200, 6, 60),2);
		weg2.vAnnahme(make_unique<Fahrrad>("MTB Specialized", 25),4);
		cout << endl;

	for (int i = 0; i <= 3; i++)
	{
		dGlobaleZeit += 1;
		cout << "Aktuelle Zeit: " << dGlobaleZeit << endl;
		weg1.vSimulieren();
		weg2.vSimulieren();
		cout << weg1 << endl;
		cout << weg2 << endl;

	}
}

void vAufgabe_6() {
	bInitialisiereGrafik(800, 500);

		Weg Beverstrasse1("Weghin", 500, Tempolimit::Innerorts);
		Weg Beverstrasse2("WegRueck", 500, Tempolimit::Innerorts);
		int iBeverstrasseKoordinaten[4] = { 700, 250, 100, 250 };
		bZeichneStrasse(Beverstrasse1.getName(), Beverstrasse2.getName(), Beverstrasse1.getLaenge(), 2, iBeverstrasseKoordinaten);

		{
			Beverstrasse1.vAnnahme(make_unique<PKW>("Audi", 120, 30, 60));
			Beverstrasse1.vAnnahme(make_unique<PKW>("Volvo", 60, 30, 60), 3); //parkendes Fahrzeug
			Beverstrasse1.vAnnahme(make_unique<PKW>("BMW", 30, 30, 60));
			Beverstrasse1.vAnnahme(make_unique<Fahrrad>("CityBike", 25));

			cout << "Beverstrasse-Simulation" << endl;
			cout << "" << endl;
			Beverstrasse1.vKopf();
			double dTakt = 0.25;

			for (; dGlobaleZeit < 20; dGlobaleZeit += dTakt)
			{
				cout << "Globalezeit :" << dGlobaleZeit << endl;
				cout << "" << endl;
				Beverstrasse1.vSimulieren();
				Beverstrasse1.vZeichnen();
				Beverstrasse2.vZeichnen();
				cout << Beverstrasse1 << endl;
				vSleep(100);
			}
		}
//	-----------------------------------------------------------
//
//		Weg Luisen1("WegHin", 500, Tempolimit::Innerorts);
//		Weg Luisen2("Wegrueck", 500, Tempolimit::Innerorts);
//		int iLuisenKoordinaten[4] = { 700, 100, 100, 100 };
//		bZeichneStrasse(Luisen1.getName(), Luisen2.getName(), Luisen1.getLaenge(), 2, iLuisenKoordinaten);
//
//		{
//			Luisen1.vAnnahme(make_unique<PKW>("A", 120, 30, 60));
//			Luisen1.vAnnahme(make_unique<PKW>("V", 60, 30, 60), 3); //parkendes Fahrzeug
//			Luisen2.vAnnahme(make_unique<PKW>("B", 30, 30, 60));
//			Luisen2.vAnnahme(make_unique<Fahrrad>("C", 25));
//
//			cout << "Beverstrasse-Simulation" << endl;
//					cout << "" << endl;
//					Luisen1.vKopf();
//					double dTakt = 0.25;
//
//					for (; dGlobaleZeit < 15; dGlobaleZeit += dTakt)
//					{
//						cout << "Globalezeit :" << dGlobaleZeit << endl;
//						cout << "" << endl;
//						Luisen1.vSimulieren();
//						Luisen1.vZeichnen();
//						Luisen2.vZeichnen();
//						cout << Luisen1 << endl;
//						vSleep(100);
//					}
//		}

		vBeendeGrafik();
}

int vAufgabe_6a_nummber_generator(){

	static std::mt19937 device(0);
	uniform_int_distribution<int> dist(0, 10);
	int random = dist(device);
	return random;

	return 0;

}

void vAufgabe_6a(){

	vertagt::VListe<int> RandomNumList;

	for(int i = 0; i < 10; i++ ){
		int random_number = vAufgabe_6a_nummber_generator();
		RandomNumList.push_front(random_number); //Zahlen werden in die Liste eingefuegt (in p_aktionen).
		RandomNumList.vAktualisieren();
	}

//	Ausgabe RandomNumList
	list<int>::iterator it;
	cout << "Die folgenden Elemente sind in der Zufallsliste enthalten: " << endl;
	for (it = RandomNumList.begin(); it != RandomNumList.end(); it++) {
	cout << *it << endl;
	}

//	Loeschen + neue scope
	{
			list<int>::iterator it;
			for (it = RandomNumList.begin(); it != RandomNumList.end(); it++)
			{
				cout << "Folgendes Element wird von der Zufallsliste geloescht: " << endl;
				cout << *it << endl;
				RandomNumList.erase(it); //in die Liste p_aktionen eingefuegt
			}
			cout << "" << endl;

			//Ausgabe zum Ueberpruefen, dass die Aktionen noch nicht ausgefuehrt wurden,
			//obwohl sie schon in der p_aktionen Liste enthalten sind
			cout << "Elemente in RandomNumList: " << endl;
			for (it = RandomNumList.begin(); it != RandomNumList.end(); it++)
			{
				cout << *it << endl;
			}
			cout << "" << endl;

			RandomNumList.vAktualisieren();

			//Liste soll leer sein
			cout << "Elemente in RandomNumList: " << endl;
			for (it = RandomNumList.begin(); it != RandomNumList.end(); it++)
			{
				cout << *it << endl;
			}
			cout << "" << endl;
	}

			//2 veschiedener Zahlen

			RandomNumList.push_back(0);
			RandomNumList.push_front(11);
			RandomNumList.vAktualisieren();

			cout << "Elemente in RandomNumList: " << endl;
			for (it = RandomNumList.begin(); it != RandomNumList.end(); it++)	{
				cout << *it << endl;
			}


}

void vAufgabe_7(){
	bInitialisiereGrafik(1000, 600);

		auto kreuzung1 = make_shared<Kreuzung>("Kreuzung1", 0);
		auto kreuzung2 = make_shared<Kreuzung>("Kreuzung2", 1000);
		auto kreuzung3 = make_shared<Kreuzung>("Kreuzung3", 0);
		auto kreuzung4 = make_shared<Kreuzung>("Kreuzung4", 0);

		Kreuzung::vVerbinde(kreuzung1, kreuzung2, "Str1Hin", "Str1Rueck", 40, true, Tempolimit::Innerorts );
		Kreuzung::vVerbinde(kreuzung2, kreuzung3, "Str2Hin", "Str2Rueck", 115, false, Tempolimit::Autobahn);
		Kreuzung::vVerbinde(kreuzung2, kreuzung3, "Str3Hin", "Str3Rueck", 40, true, Tempolimit::Innerorts);
		Kreuzung::vVerbinde(kreuzung4, kreuzung2, "Str4Hin", "Str4Rueck", 55, true, Tempolimit::Innerorts);
		Kreuzung::vVerbinde(kreuzung4, kreuzung3, "Str5Hin", "Str5Rueck", 85, false, Tempolimit::Autobahn);
		Kreuzung::vVerbinde(kreuzung4, kreuzung4, "Str6Hin", "Str6Rueck", 130, false, Tempolimit::Landstrasse);

		int iKoordinatenStr1[] = { 680,40,680,300 };
		int iKoordinatenStr2[] = { 680,300,850,300,970,390,970,500,850,570,680,570 };
		int iKoordinatenStr3[] = { 680,300,680,570 };
		int iKoordinatenStr4[] = { 320,300,680,300 };
		int iKoordinatenStr5[] = { 320,300,320,420,350,510,500,570,680,570 };
		int iKoordinatenStr6[] = { 320,300,320,150,200,60,80,90,70,250,170,300,320,300 };

		bZeichneStrasse("Str1Hin", "Str1Rueck", 40, 2, iKoordinatenStr1);
		bZeichneStrasse("Str2Hin", "Str2Rueck", 115, 6, iKoordinatenStr2);
		bZeichneStrasse("Str3Hin", "Str3Rueck", 40, 2, iKoordinatenStr3);
		bZeichneStrasse("Str4Hin", "Str4Rueck", 55, 2, iKoordinatenStr4);
		bZeichneStrasse("Str5Hin", "Str5Rueck", 85, 5, iKoordinatenStr5);
		bZeichneStrasse("Str6Hin", "Str6Rueck", 130, 7, iKoordinatenStr6);

		bZeichneKreuzung(680, 40);
		bZeichneKreuzung(680, 300);
		bZeichneKreuzung(680, 570);
		bZeichneKreuzung(320, 300);


		kreuzung1->vAnnahme(move(make_unique<PKW>("BMW", 140, 7, 50)), 1.5);
		kreuzung1->vAnnahme(move(make_unique<PKW>("Mercedes", 60, 7.4, 30)), 1.25);
		kreuzung1->vAnnahme(move(make_unique<PKW>("Tesla", 80, 7.6, 34)), 1);
		kreuzung1->vAnnahme(move(make_unique<PKW>("Toyota", 140, 7, 50)), 1.75);
		kreuzung1->vAnnahme(move(make_unique<PKW>("Alfa-Romeo", 60, 7.4, 30)), 0.5);
		kreuzung1->vAnnahme(move(make_unique<PKW>("Porsche", 80, 7.6, 34)), 0.75);

		kreuzung1->vAnnahme(move(make_unique<PKW>("Audi", 50, 7, 50)), 2);
		kreuzung1->vAnnahme(move(make_unique<PKW>("Ford", 60, 7.4, 30)), 2.5);
		kreuzung1->vAnnahme(move(make_unique<PKW>("Lexus", 80, 7.6, 34)), 2.25);
		kreuzung1->vAnnahme(move(make_unique<PKW>("Ferrari", 50, 7, 50)), 2.75);
		kreuzung1->vAnnahme(move(make_unique<PKW>("Lotus", 60, 7.4, 30)), 3);
		kreuzung1->vAnnahme(move(make_unique<PKW>("Peugeot", 80, 7.6, 34)), 3.5);
		kreuzung1->vAnnahme(move(make_unique<Fahrrad>("Specialized", 60)), 0.25);

		cout << "Kreuzung-Simulation" << endl;
		cout << "" << endl;
		for (int i = 0; i < 50; i++) {
			cout << "Aktuelle Zeit" << dGlobaleZeit << endl;
			dGlobaleZeit += 0.125;
			kreuzung1->vSimulieren();
			kreuzung2->vSimulieren();
			kreuzung3->vSimulieren();
			kreuzung4->vSimulieren();
			kreuzung1->Zeichnen();
			kreuzung2->Zeichnen();
			kreuzung3->Zeichnen();
			kreuzung4->Zeichnen();
			vSleep(20);
			vSetzeZeit(dGlobaleZeit);
		}

		vBeendeGrafik();
}


int main(void){

//	vAufgabe_1();
//	vAufgabe_1a();
//	vAufgabe_2();
//	vAufgabe_3();
//	vAufgabe_4();
//	vAufgabe_5();
//	vAufgabe_6_test();
//	vAufgabe_6();
//	vAufgabe_6a();
	vAufgabe_7();
	return 0;
}
