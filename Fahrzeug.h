#pragma once
#include "Verhalten.h"
#include "Simulationsobjekt.h"
#include <iostream>
#include <iomanip>
#include <string>
#include <limits>
#include <memory>
#include <algorithm>
class Weg;
class Verhalten;
class Parken;
class Fahren;

class Fahrzeug : public Simulationsobjekt
{
	protected:
		unique_ptr<Verhalten> p_pVerhalten = nullptr;
		double p_dMaxGeschwindigkeit = 0;
		double p_dGesamtStrecke = 0;
		double p_dAbschnittStrecke = 0;
		double p_dGesamtZeit = 0;
		double p_dZeit = 0;

	public:
		Fahrzeug();
		Fahrzeug(string sName);
		Fahrzeug(string sName, double dMaxGeschwindigkeit);

		static void vKopf();
		virtual void vAusgeben(ostream& os) const;

		virtual double dTanken(double dMenge = numeric_limits<double>::infinity());
		virtual void vSimulieren() override;
		virtual void vZeichnen(Weg& aWeg) const;

		virtual double dGetfreierTank() const;
		virtual double dGeschwindigkeit() const;
		double dgetAbschnittStrecke() const;

		void vNeueStrecke(Weg&);
		void vNeueStrecke(Weg&, double dStartzeitkpt);

		bool operator<(const Fahrzeug&) const;
		bool operator>(const Fahrzeug&) const;
		void operator=(const Fahrzeug&);

		Fahrzeug(const Fahrzeug&) = delete;

		virtual ~Fahrzeug();
};
