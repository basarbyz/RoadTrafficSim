#pragma once
#include "Verhalten.h"

class Parken : public Verhalten
{
	private:
		double p_dStartzeitpkt;

	public:
		Parken(Weg& aWeg, double dStartzeitpkt);

		double dStrecke(Fahrzeug& aFzg, double dZeitIntervall) override;

		virtual ~Parken();
};
