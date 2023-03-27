#pragma once
#include "Fahrausnahme.h"

class Streckenende : public Fahrausnahme
{
	public:
		Streckenende(Fahrzeug& aFzg, Weg& aWeg);

		virtual void vBearbeiten();

		virtual ~Streckenende();

};
