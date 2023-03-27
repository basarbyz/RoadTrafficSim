#pragma once
#include <memory>
#include "Simulationsobjekt.h"
#include "Tempolimit.h"
#include "vertagt_liste - Vorlage.h"

class Fahrzeug;
class Kreuzung;

using namespace std;

class Weg : public Simulationsobjekt
{
	private:
		double p_dLaenge = 0; // km
		TempolimitNS::Tempolimit p_eTempolimit;
		string sName = "";

		vertagt::VListe<unique_ptr<Fahrzeug>> p_pFahrzeuge;
		bool p_bUeberholverbot;
		double p_dVirtuelleSchranke = 1000000000;
		weak_ptr<Weg> p_pRueckWeg;
		const weak_ptr<Kreuzung> p_pKreuzung;
	public:
		Weg();
		Weg(string sName, double dLaenge, TempolimitNS::Tempolimit optTempoLimit = TempolimitNS::Tempolimit::Autobahn,
				bool Ueberholverbot = true);
		Weg(string name, double dLaenge, weak_ptr<Kreuzung> pKreuzung,
				TempolimitNS::Tempolimit Geschwindigkeitslimit = TempolimitNS::Tempolimit::Autobahn, bool Ueberholverbot = true);

		static void vKopf();

		void vSimulieren() override;
		void vAusgeben(ostream& os) const override;
		virtual void vAnnahme(unique_ptr<Fahrzeug> ptrFahrzeug);
		void vAnnahme(unique_ptr<Fahrzeug> ptrFahrzeug, double dStartzeitpkt);
		double getTempolimit();
		double dgetLaenge() const;

		unique_ptr<Fahrzeug> pAbgabe(const Fahrzeug& aFzg);

		// list<unique_ptr<Fahrzeug>> pgetList();
		vertagt::VListe<unique_ptr<Fahrzeug>>* getList(){return &p_pFahrzeuge;}
		double getVirtuelleSchranke();
		void setVirtuelleSchranke(double dVirtuelleSchranke);
		void setRueckweg(weak_ptr<Weg> pRueckweg);
		Weg& getRueckweg();
		Kreuzung& getKreuzung();

		Weg(const Weg&) = delete;
		virtual ~Weg();

};

