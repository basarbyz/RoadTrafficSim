#pragma once
#include "Fahrzeug.h"
#include "SimuClient.h"
#include "Weg.h"

class Fahrrad : public Fahrzeug
{
	public:
		Fahrrad(std::string sName, double dMaxGeschwindigkeit);
		double dGeschwindigkeit() const override;
		virtual void vZeichnen(Weg& aWeg) const override;
};
