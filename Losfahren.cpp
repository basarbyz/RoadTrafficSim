#include "Losfahren.h"
#include "Fahrzeug.h"


Losfahren::Losfahren(Fahrzeug& aFzg, Weg& aWeg) : Fahrausnahme(aFzg, aWeg){}

Losfahren::~Losfahren(){}

void Losfahren::vBearbeiten()
{
	cout << "Ausnahmeart: Losfahren\n"
			  << ">>Name des Fahrzeugs: " << p_exceptFahrzeug.getName()
			  << "Der Weg auf dem sich das Fahrzeug befindet: " << p_exceptWeg.getName() ;
	cout << " \n\n" ;
	p_exceptFahrzeug.vNeueStrecke(p_exceptWeg); //parkende Fahrzeuge fahren los.
}

