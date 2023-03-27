#pragma once
#include "Verhalten.h"

class Fahren : public Verhalten
{
	public:
		explicit Fahren(Weg&);

		double dStrecke(Fahrzeug& aFzg, double dZeitIntervall) override;

		virtual ~Fahren();
};
