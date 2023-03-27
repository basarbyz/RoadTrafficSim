#pragma once
#include "Fahrzeug.h"
#include <limits>
class Weg;
class PKW : public Fahrzeug
{
	private:
		double p_dVerbrauch = 0; // Liter/100km
		double p_dTankvolumen = 0; // Liter
		double p_dTankinhalt = 0; // liter
	public:
		PKW();
		PKW(std::string sName, double dMaxGeschwindigkeit, double dVerbrauch, double dTankvolumen = 55);
		virtual ~PKW()=default;
		double dGetfreierTank() const override;

		double dGeschwindigkeit() const;
		double dTanken(double dMenge) override;
		void vSimulieren() override;
		void vAusgeben(std::ostream& o) const override;
		virtual void vZeichnen(Weg& aWeg) const override;
};

