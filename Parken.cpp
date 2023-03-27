#include "Parken.h"
#include "Fahrzeug.h"
#include "Losfahren.h"
#include <cmath>

extern double dGlobaleZeit;

Parken::Parken(Weg& aWeg, double dStartzeitpkt) : Verhalten(aWeg), p_dStartzeitpkt(dStartzeitpkt){}

Parken::~Parken(){}

//--dStrecke() fuer parkende Fahrzeuge gibt null aus, solange die Startzeit nicht erreicht wurde
double Parken::dStrecke(Fahrzeug& aFzg, double dZeitintervall)
{

	if (dGlobaleZeit + 0.0001 < p_dStartzeitpkt)
		return 0.0;
	else
	{
		throw Losfahren(aFzg, p_aWeg);
		cout << "Die Startzeit von " << aFzg.getName() << " wurde erreicht.\n\n";
	}

}
