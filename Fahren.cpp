#include <algorithm>
#include "Fahren.h"
#include "Fahrzeug.h"
#include "Streckenende.h"
#include "Verhalten.h"
#include "Weg.h"

Fahren::Fahren(Weg& aWeg): Verhalten(aWeg){}

Fahren::~Fahren(){}

double Fahren::dStrecke(Fahrzeug& aFzg, double dZeitIntervall)
{
	Weg& strasse = this->wgetWeg();
	double dGefahrenStrecke = dZeitIntervall * aFzg.dGeschwindigkeit();
	double dRestStrecke = strasse.dgetLaenge() - aFzg.dgetAbschnittStrecke();

	if (dGefahrenStrecke >= dRestStrecke)
		{
			cout<< " Das Fahrzeug [ " << aFzg.getName() << " ] ist am Ende des Weges.\n";
			throw Streckenende(aFzg, strasse);
		}
	return min<double>(dGefahrenStrecke,dRestStrecke) ;
}
