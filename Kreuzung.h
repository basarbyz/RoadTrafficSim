#pragma once

#include "Simulationsobjekt.h"
#include <list>
#include "Weg.h"

using namespace std;

class Kreuzung : public Simulationsobjekt{
public:
	Kreuzung();
	Kreuzung(string sName, double dTankstellenKapazitaet = 0);

	void vVerbinde(string sNameHinweg, string sNameRueckweg, double dWegLaenge,
			weak_ptr<Kreuzung> pStartKreuzung, const weak_ptr<Kreuzung> pZielKreuzung,
			TempolimitNS::Tempolimit geschBegrenz = TempolimitNS::Tempolimit::Autobahn, bool bUeberholVerbot = true);
	void vTanken(Fahrzeug&);
	void vAnnahme(unique_ptr<Fahrzeug>,double dZeit);
	void vSimulieren();
	Weg& pZufaelligerWeg(Weg&);
	double getTankstellen(){return p_dTankstelle;}
	list<shared_ptr<Weg>> getWege(){return p_pWege;}
	virtual ~Kreuzung();
private:
	double p_dTankstelle;
	list<shared_ptr<Weg>> p_pWege;
};
