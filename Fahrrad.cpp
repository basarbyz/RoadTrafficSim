#include "Fahrrad.h"
#include <cmath>

Fahrrad::Fahrrad(std::string sName, double dMaxGeschwindigkeit) : Fahrzeug(sName, dMaxGeschwindigkeit){}

double Fahrrad::dGeschwindigkeit() const
{
	double dAktGesch = std::pow(0.9, (int)p_dGesamtStrecke / 20) * p_dMaxGeschwindigkeit;

	return (dAktGesch >= 12) ? dAktGesch : 12 ;
}

void Fahrrad::vZeichnen(Weg& aWeg) const
{
	double dRelPosition = this->dgetAbschnittStrecke() / aWeg.dgetLaenge(); //Wert zwichen 0 & 1

	std::string Strasse = aWeg.getName();
	std::string FahradName = this->getName();
	double Km_H = this->dGeschwindigkeit();

	bZeichneFahrrad(FahradName, Strasse, dRelPosition, Km_H);
}

