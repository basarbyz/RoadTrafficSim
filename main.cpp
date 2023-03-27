#include "Fahrzeug.h"
#include "PKW.h"
#include "Fahrrad.h"
#include "Fahren.h"
#include "Verhalten.h"
#include "Simulationsobjekt.h"
#include "SimuClient.h"
#include "Kreuzung.h"

#include <iostream>
#include <memory>
#include <iomanip>
#include <string>
#include <vector>
#include <cmath>
#include <random>
#include <algorithm>
#include "Weg.h"

using namespace std;

double dGlobaleZeit = 0.0;//Globale Uhr, mit extern einer klasse bekannt machen
double dEpsilon = 0.001;
//Test zu Aufgabe 1

void vAufgabe_1()
{
	//---Statische Fahrzeug-Elemente Über Deklaration
	Fahrzeug Auto("Auto_1");
	Fahrzeug Bus("Bus_1");

	//---Dynamische Fahrzeug-Elemente mit new erstellt und delete gelöscht
	Fahrzeug * Auto_2 = new Fahrzeug("New Auto_2");
	Fahrzeug * Bus_2 = new Fahrzeug("New Bus_2");

	delete Bus_2;
	delete Auto_2;
	//---Löschung dynamesche elemente zähler nicht gelöscht

	//---Erzeugung von Fahrzeugen mit Smartpointer
	auto p_Mofa_1 = make_unique<Fahrzeug>("Unique p_Mofa_1");
	auto p_Mofa_2 = make_unique<Fahrzeug>("Unique p_Mofa_2");
	auto p_Mofa_3 = make_shared<Fahrzeug>("Shared p_Mofa_3");
	auto p_Mofa_4 = make_shared<Fahrzeug>("Shared p_Mofa_4");
	cout<< "Anzahl der Referenzen auf p_Mofa_4:\n"
			 << p_Mofa_4.use_count()<<endl;    //zählt referenzen aufp_Mofa_4

	shared_ptr<Fahrzeug> p_Mofa_5 = p_Mofa_4;  //shared_ptr von p_Mofa_4 wird nochmal hier gespeichert
	cout<< "Anzahl der Referenzen auf p_Mofa_4:\n"
		     << p_Mofa_4.use_count()<<endl<<endl;
	//---Aufruf Destruktor
	//---Erzeugung eines unique Vectors,der die erzeugten unique Fahrzeuge speichert
	cout << "Verkehrsmittel erzeugt\n";
	vector<unique_ptr<Fahrzeug>> Verkehrsmittel;
	Verkehrsmittel.push_back(move(p_Mofa_1));  //unique pointer nicht kopierbar, move() überträgt Wert in neue Fkt/pointer
	Verkehrsmittel.push_back(move(p_Mofa_2));

	//--Erzeugung eines shared Vecttos,der die erzeugten shared Fahrzeuge speichert
	cout << "shared_Verkehrsmittel erzeugt\n";
	vector<shared_ptr<Fahrzeug>> shared_Verkehrsmittel;
	shared_Verkehrsmittel.push_back(p_Mofa_3 );  //hier werden nur kopien des Pointers gespeichert
	shared_Verkehrsmittel.push_back(move(p_Mofa_4));

	cout << " Verkehrsmittel loesch\n";
	Verkehrsmittel.clear(); //Löschung des unique Vectors, alle Daten sind gelöscht

	cout << "shared_Verkehrsmittel loesch\n";
	shared_Verkehrsmittel.clear();//Löschung des shared Vectors, alle Kopien wurden gelöscht
}

//----Hauptfkt vAufgabe_1a(), liest Namen & Maxgeschw. von 3 unique Fahrzeugen, speichert diese in ein vektor
//simulieren über verschiedene Zeitspannen
void vAufgabe_1a()
{
	//----Vektor container für Fahrzeuge, die vom Benutzer eingegeben werden durch schleife
	vector<unique_ptr<Fahrzeug>> BenutzerFahrzeug;
	for ( int  i = 1; i<=3; i++)
	{
		string sName;
		double dMaxGeschwindigkeit;
		cout <<"Gebe Namen und Max.Geschwindigkeit des "<< i <<"# Fahrzeugs ein: \n";
		cin >> sName >> dMaxGeschwindigkeit;
		BenutzerFahrzeug.push_back(make_unique<Fahrzeug> (sName, dMaxGeschwindigkeit));//fügt dem Vector hinzu
	}
	//Simulieren des Fahrzeugs in eine gewisse zeitspanne mit einer schleife,
	//schleife : erhöht globale Uhr je um einen Zeittakt & ruft Simulationsfkt und Ausgabefkt der fahrzeuge
	double dZeittakt = 0.25; //Takt in 15 min

	for (; dGlobaleZeit < 1; dGlobaleZeit += dZeittakt) //für 45 zeittakte 1 Std.
		{
			BenutzerFahrzeug[0]->vKopf();//als erstes Überschrift
			cout << endl;

			for (int i = 0; i < 3; i++)
			{
				BenutzerFahrzeug[i]->vSimulieren();//Simulation durchführen
				cout << *BenutzerFahrzeug[i]; //ausgabefkt aufrufen
				cout<<endl;
			}

			cout<<"\n\n";
		}

}


//4.4 Warum können/sollten keine fahrzeugobjekte gespeicher werden   ?    -----> Fahrzeug ist die Basisklasse von der man ein Objekt erzeugen kann/sollte, Erzeugung von Objekten nur von den Unterklassen.
//4.4 warum können PKWs und Fahrräder in ein gemeinsames Vector gespeichert werden?-----> Sie sind unterclassen von Klasse Fahrzeug (also abgeleitet vom selben Typ, Klasse), und können im selben Vector-Container gespeichert werden
/* Der Zeiger vom Typ „Basisklasse“ kann nur Methoden der
Basisklasse aufrufen, aber keine Methoden der Subklasse.
 Das Objekt der Subklasse wird automatisiert in ein Objekt der
Basisklasse konvertiert.*/
void vAufgabe_2()
{
	vector<unique_ptr<Fahrzeug>> TransportContainer;//vector-container für die Objekte

	int icountPKW=0;
	cout<<"Wie viele PKWs willst du erstellen?:\n ";
	cin>>icountPKW;

	//----Schleife erstellt PKWs und gibt diese in den TransportContainer
	for (int i = 1; i <= icountPKW; i++)
		{
			cout << "Eingabe der Daten des " << i << " PKWs:\n" << endl;
			string sName;
			double dMaxGeschw_=0, dVerbrauch=0,dTankvolumen =0;

			cout << "Name: ";
			cin >> sName;
			cout << "Max-Geschwindigkeit: ";
			cin >> dMaxGeschw_;
			cout << "Oel-Verbrauch in Liter/100km: ";
			cin >> dVerbrauch;
			cout<<"Willst du Tankvolumen eingeben? (y/n) \n";
			char eingabe;
			cin>>eingabe;
			switch(eingabe)
			{
				case'y':
					cout << "Tankvolumen in Liter: ";
					cin >> dTankvolumen;
					TransportContainer.push_back(move(make_unique<PKW>(sName, dMaxGeschw_, dVerbrauch, dTankvolumen)));
					break;
				case'n':
					cout << "Tankvolumen wird nicht mit eingegeben.\n ";
					TransportContainer.push_back(move(make_unique<PKW>(sName, dMaxGeschw_, dVerbrauch)));
					cout<<"\n";
					break;
				default:
					cout <<"ungültige eingabe.\n";
			}
		}

	int icountFahrrad;
	cout<<"Wie viele Fahrraeder willst du erstellen?\n ";
	cin>>icountFahrrad;
	//----Schleife erstellt Fahrräder und gibt diese in den TransportContainer
	for (int i = 1; i <= icountFahrrad; i++)
	{
		cout << "Eingabe der Daten des " << i << " Fahrrads:\n" << endl;
		string sName;
		double dMaxGeschw_;
		cout << "Name: ";
		cin >> sName;
		cout << "Max-Geschwindigkeit: ";
		cin >> dMaxGeschw_;
		TransportContainer.push_back(make_unique<Fahrrad>(sName, dMaxGeschw_));
	}

	//--------Simulations, nach 3 Std. PKWs nochmals volltanken, Zeitabfrage in TestProgramm nicht in dTanken()
	//in verschiedenen zeittakten testen, daten aller Fahrzeuge nach jedem schritt ausgeben
	double dZeittakt = 0.5; //Takt in 30 min
	bool bTankstatus = false; //ueberpruefen ob schonmal getankt wurde

	for (; dGlobaleZeit < 12; dGlobaleZeit += dZeittakt) //für 6 Std.
		{
					if (dGlobaleZeit >= 3.0 && bTankstatus == false)
					{
						cout << "------------------>>3 Stunden sind um. Es wird voll getankt.\n\n ";
						for ( int i = 0; i < icountPKW; i++)
							{
								double dOelmenge = 0;
								cout << "Mit wie viel wollen Sie das " << TransportContainer[i]->getName() << " tanken (in Liter)? "
										  <<" (Tipp: zum Volltanken wird " <<TransportContainer[i]->dGetfreierTank()<<" Liter benötigt.): ";
								cin >> dOelmenge;
								TransportContainer[i]->dTanken(dOelmenge);
							}
						bTankstatus = true;//nach dem auffüllen

					}
			cout<<"Aktuelle globake Zeit:"<<dGlobaleZeit<<endl<<endl;
			TransportContainer[0]->vKopf();//als erstes Überschrift
			cout << endl;

			for (unsigned int i = 0; i < TransportContainer.size(); i++)
				{
					TransportContainer[i]->vSimulieren();//Simulation durchführen

					//TransportContainer[i]->vAusgeben();
					cout << (*TransportContainer[i]);
					cout<<"\n\n";
				}
			}
}


//-------------Funktion zum Testen der ueberladenen Operatoren------------------
void vAufgabe_3()
{
	vector<unique_ptr<Fahrzeug>> FahrContainer;
//----Autos
	FahrContainer.push_back(move(make_unique<PKW> ("Audi", 150.2, 10, 80)));
	FahrContainer.push_back(move(make_unique<PKW> ("VW",   100.6,  9, 70)));
//-----Fahrräder
	FahrContainer.push_back(move(make_unique<Fahrrad>("Citybike", 50)));
	FahrContainer.push_back(move(make_unique<Fahrrad>("Mountainbike", 40)));
//----------Simulation------------------------
	double dZeitTakt = 0.25; //Takt in 15 minuten
	for (; dGlobaleZeit < 1; dGlobaleZeit += dZeitTakt)
	{
		cout << "Aktuelle Globalle Zeit:"<< dGlobaleZeit<<"\n\n";
		FahrContainer[0]->vKopf();
		cout << "\n" ;
		for (int i = 0; i < 4; i++)
		{
			FahrContainer[i]->vSimulieren();
				cout << *FahrContainer[i];
				cout << "\n";
		}cout << "\n" ;
	}

//--------------Testen der selbstdefinierten Operatoren-------------------
//Daten vergleichen anhand Gesamtstrecke.
	cout<<"\n------Testen der Operationen\n\n";
	if(*FahrContainer[3] < *FahrContainer[1])
	{
		cout <<"Ueberladung des < Operators war erfolgreich.\n"
				  << FahrContainer[1]->getName() << " ist weiter gefahren als " << FahrContainer[3]->getName() << ".\n\n" ;
	}
	else if (*FahrContainer[1] < *FahrContainer[3])
		{
			cout << FahrContainer[3]->getName() << " ist weiter gefahren als " << FahrContainer[1]->getName() << "." << endl;
			cout << "" << endl;
		}
	else
		{
			cout << FahrContainer[3]->getName() << "&" << FahrContainer[4]->getName() << "sind genauso weit gefahren." << "." << endl;
			cout << "" << endl;
		}
	//Test des gleichgesetzt operaotors
		*FahrContainer[3] = *FahrContainer[2]; //Mountainbike nimmt Stammdaten von Citybike, Mountainbyke ist jetzt clone von citybike.
		//Ausgabe
		FahrContainer[0]->vKopf();
		for (unsigned i = 0;i<4;i++)
			cout << (*FahrContainer[i]);

//		cout << (*FahrContainer[1]);
//		cout << (*FahrContainer[2]);//cout<<"\n";
//		cout << (*FahrContainer[3]);

}

void vAufgabe_Probe()
{
   Fahrzeug* pF1 = new PKW("Audi", 150, 8);
    dGlobaleZeit = 0.0;
    Fahrzeug::vKopf();
    dGlobaleZeit = 3.0;
    cout << endl << "Globalezeit = " << dGlobaleZeit << endl;
    pF1->vSimulieren();
    cout << *pF1 << endl;
    delete pF1;
    pF1 = 0;

}

void vAufgabe_AB1()
{
    int l = 0; // Laufindex für gezielte AUsgabe
    vector<int> ausgabe{13};
    double dTakt = 0.4;

    vector<unique_ptr<Fahrzeug>> vecFahrzeuge;
    vecFahrzeuge.push_back(make_unique <PKW>("Audi", 217, 10.7));
    vecFahrzeuge.push_back(make_unique <Fahrrad>("BMX", 21.4));
    for (dGlobaleZeit= 0.0; dGlobaleZeit < 6; dGlobaleZeit += dTakt) // @suppress("Float counter in for loop")
    {
        auto itL = find(ausgabe.begin(), ausgabe.end(), l);
        if (itL != ausgabe.end()) {
            cout << endl << l <<  " Globalezeit = " << dGlobaleZeit << endl;
            Fahrzeug::vKopf();
        }

        for (unsigned int i = 0; i < vecFahrzeuge.size(); i++)
        {
            vecFahrzeuge[i]->vSimulieren();
            if (fabs(dGlobaleZeit - 3.0) < dTakt/2)
            {
                vecFahrzeuge[i]->dTanken();
            }
            if (itL != ausgabe.end()) {
                cout << *vecFahrzeuge[i] << endl;
            }
        }
        l++;
    }
    char c;
    cin >> c;
}
void vAufgabe_4()
{
	Weg Weg_1("Mustafa Kemal Atatürk Sokak", 1881); // @suppress("Ambiguous problem")
	Weg_1.vKopf();
	cout << Weg_1;
}

void vAufgabe_5()
{
	Weg Weg_1("Mustafa Kemal Atatürk Sokak", 60, TempolimitNS::Tempolimit::Innerorts);

	Weg_1.vAnnahme(make_unique<PKW>("Volkswagen", 100, 10, 900), 3.0); // @suppress("Avoid magic numbers")

	Weg_1.vSimulieren();
	Weg_1.vKopf();
	cout << Weg_1;

	double dTakt = 0.2;
	for (; dGlobaleZeit < 5; dGlobaleZeit += dTakt)
	{
		cout<<" Globale Zeit: "<< dGlobaleZeit << endl;
		Weg_1.vSimulieren();
		Weg_1.vKopf();
		cout << Weg_1 << endl;
		vSleep(500);
	}
}


void vAufgabe_6()
{
	bInitialisiereGrafik(800, 500);


	Weg Weg_1("Weg_1", 500,  TempolimitNS::Tempolimit::Innerorts);
	Weg Weg_2("weg_2", 500,  TempolimitNS::Tempolimit::Innerorts);
	int iWegKoordinaten[] = { 700, 250, 100, 250 };
	bZeichneStrasse(Weg_1.getName(), Weg_2.getName(), Weg_1.dgetLaenge(), 2, iWegKoordinaten);
	{
		Weg_1.vAnnahme(make_unique<PKW>("Porsche", 190,10,200)); // fahrend
		Weg_1.vAnnahme(make_unique<Fahrrad>("MountainBike", 16)); // parkend
		Weg_2.vAnnahme(make_unique<PKW>("BMW", 110, 13, 180), 1.8); // parkend
		Weg_2.vAnnahme(make_unique<Fahrrad>("CityBike", 25)); // fahrend

		double dTakt = 0.4;
		for (; dGlobaleZeit < 8; dGlobaleZeit += dTakt)
		{
			Weg_1.vSimulieren();
			Weg_2.vSimulieren();
			cout << "Globalezeit :" << dGlobaleZeit << endl;
			vSetzeZeit(dGlobaleZeit);
			cout << "" << endl;
			Weg_1.vKopf();
			cout << Weg_1 << Weg_2 << endl;
			vSleep(100);
		}
	}
	vBeendeGrafik();
}

//funktion zufälige tahl
int izufahls_generator()
{
	static mt19937 device(0); //seed = 0;
	uniform_int_distribution<int> dist(1, 10);
	int zuf = dist(device);
	return (zuf);
}


void vAufgabe_6a()
{
	vertagt::VListe<int> ZufallsListe; //Liste erstellen

	for (int i = 0; i < 10; ++i) //Schleife zum Einfuegen 10 Zufallszahlen in die Liste
	{
		int zufalszahl = izufahls_generator();
		ZufallsListe.push_back(zufalszahl); //generierte Zahlen werden in die Liste eingefuegt, erstmal aber in p_aktionen.
		ZufallsListe.vAktualisieren();
	} //Zahlen werden so von p_aktionen in p_objekt umgewandelt, un kann ausgegeben werden

	//---Liste Ausgaben--------------

	cout << "\n Elemente in der Zufallsliste : \n";
	for (auto it = ZufallsListe.begin(); it != ZufallsListe.end(); ++it)
		{
			cout << *it << endl;
		}

	//--Loeschen aller elemente grösser als 5 ---------------
		//Ahand dieser Schleife werde die Erase-Aktionen in die p_Aktionen liste eingefuegt,
		//das heisst aber nicht, dass sie nun geloescht werden, das erfolgt erst nach der
		//Ausfuehrung von vAktualisieren().
	cout << "\n\nFolgende Element werden von der Zufallsliste geloescht: ";
	for (auto it = ZufallsListe.begin(); it != ZufallsListe.end(); ++it)
	{
			if (*it > 5 )
			{
				cout  << *it <<" ";
				ZufallsListe.erase(it); //die erase-"Auftraege" werden in die Liste p_aktionen eingefuegt
			}
	}

	//Ausgabe zum Ueberpruefen, dass die Aktionen noch nicht ausgefuehrt wurden,
	//obwohl sie schon in der p_aktionen Liste enthalten sind
	cout << "\n\n[Auftraege auf Standby]\n Folgende Elemente noch in der Zufallsliste enthalten: \n" ;
	for (auto it = ZufallsListe.begin(); it != ZufallsListe.end(); ++it)
	{
		cout << *it << endl;
	}
	ZufallsListe.vAktualisieren();//hier werden dann alle Auftraege auf einmal durchgefuehrt.


	cout << "\n\n Elemente in der Zufallsliste nach vAktualisieren :\n " ;
	for (auto it = ZufallsListe.begin(); it != ZufallsListe.end(); ++it)
	{
		cout << *it << endl;
	}
	// Einfuegen 2 veschiedener Zahlen----------
	//einfuegen erfolgt in der selben Liste, in der die Elemente geloescht wurden,
	ZufallsListe.push_back(12);
	ZufallsListe.push_front(100);
	ZufallsListe.vAktualisieren();
	cout << "\n\n Zufallsliste nach einfügen von 12 hinten und 100 vorne: \n";
	for (auto it = ZufallsListe.begin(); it != ZufallsListe.end(); ++it)
	{
		cout << *it << endl;
	}

}

void vAufgabe_7()
{
	cout << "Aufgabe 7: " << endl << endl;
	shared_ptr<Kreuzung> kr1 = make_shared<Kreuzung>("kr1");
	shared_ptr<Kreuzung> kr2 = make_shared<Kreuzung>("kr2", 1000);
	shared_ptr<Kreuzung> kr3 = make_shared<Kreuzung>("kr3");
	shared_ptr<Kreuzung> kr4 = make_shared<Kreuzung>("kr4");

	unique_ptr<Fahrzeug> f1 = make_unique<PKW>("F1", 45, 7, 500);
	unique_ptr<Fahrzeug> f2 = make_unique<PKW>("F2", 100, 5, 300);
	unique_ptr<Fahrzeug> f3 = make_unique<PKW>("F3", 200, 7, 300);
	unique_ptr<Fahrzeug> f4 = make_unique<Fahrrad>("Fahrrad1", 30);
	unique_ptr<Fahrzeug> f5 = make_unique<Fahrrad>("Fahrrad2", 20);

	bInitialisiereGrafik(1000, 1000);

	bZeichneKreuzung(680, 40);
	bZeichneKreuzung(680, 300);
	bZeichneKreuzung(680, 570);
	bZeichneKreuzung(320, 300);

	int strasse1[] = { 680, 40, 680, 300 };
	int strasse2[] = { 680, 300, 850, 300, 970, 390, 970, 500, 850, 570, 680, 570 };
	int strasse3[] = { 680, 300, 680, 570 };
	int strasse4[] = { 680, 300, 320, 300 };
	int strasse5[] = { 680, 570, 500, 570, 350, 510, 320, 420, 320, 300 };
	int strasse6[] = { 320, 300, 170, 300, 70, 250, 80, 90, 200, 60, 320, 150, 320, 300 };

	bZeichneStrasse("W12", "W21", 40, 2, strasse1);
	bZeichneStrasse("W23a", "W32a", 115, 6, strasse2);
	bZeichneStrasse("W23b", "W32b", 40, 2, strasse3);
	bZeichneStrasse("W24", "W42", 55, 2, strasse4);
	bZeichneStrasse("W34", "W43", 85, 5, strasse5);
	bZeichneStrasse("W44a", "W44b", 130, 7, strasse6);

	kr1->vVerbinde("W12", "W21", 40, kr1, kr2, TempolimitNS::Tempolimit::Innerorts, true);
	kr2->vVerbinde("W23a", "W32a", 115, kr2, kr3, TempolimitNS::Tempolimit::Autobahn, false);
	kr2->vVerbinde("W23b", "W32b", 40, kr2, kr3,  TempolimitNS::Tempolimit::Innerorts, true);
	kr2->vVerbinde("W24", "W42", 55, kr2, kr4,  TempolimitNS::Tempolimit::Innerorts, true);
	kr3->vVerbinde("W34", "W43", 85, kr3, kr4,  TempolimitNS::Tempolimit::Autobahn, false);
	kr4->vVerbinde("W44a", "W44b", 130, kr4, kr4, TempolimitNS::Tempolimit::Landstrasse, false);


	//int koordinaten[4] = { 700, 300, 100, 300 };
	//string s2 = weg2->getName();
	//const char* sWegname2 = s2.c_str();
	//bZeichneStrasse(weg1->getName(), sWegname2, weg1->getLaenge(), 2, koordinaten);
	Fahrzeug& sf1 = *f1;
	Fahrzeug& sf2 = *f2;
	Fahrzeug& sf3 = *f3;
	Fahrzeug& sf4 = *f4;


	kr2->vAnnahme(move(f2),1);
	kr1->vAnnahme(move(f3),0);
	kr1->vAnnahme(move(f4),0);
	kr1->vAnnahme(move(f1),0);

	for (dGlobaleZeit = 0; dGlobaleZeit <= 200; dGlobaleZeit += 0.25)
	{

		if (fabs(dGlobaleZeit- 1)<0.01)
		{
			cout << "wait..." << endl;
		}
		cout << "dZeit=" << dGlobaleZeit<< endl;
		vSetzeZeit(dGlobaleZeit);
		kr1->vSimulieren();
		//kr1->getWege().front()->vFahrzeuglistAusgeben();

		kr2->vSimulieren();
		//list<shared_ptr<Weg>> tmp=kr2->getWege();
		//list<shared_ptr<Weg>>::iterator it = tmp.begin();
		//it++;
		//(*it)->vFahrzeuglistAusgeben();

		kr3->vSimulieren();
		kr4->vSimulieren();

		Fahrzeug::vKopf();
		cout << sf1 << endl;
		cout << sf2 << endl;
		cout << sf3 << endl;
		cout << sf4 << endl;
		vSleep(10000000);
}

vBeendeGrafik();
}
int main()
{

//	vAufgabe_1();
//	vAufgabe_1a();
//	vAufgabe_2();
//	vAufgabe_3();
//	vAufgabe_Probe();
//	vAufgabe_AB1();
//	vAufgabe_4();
//	vAufgabe_5();
//	vAufgabe_6();
//	vAufgabe_6a();
//	izufahls_generator();
	vAufgabe_7();
	return (0);
}


