#pragma once
#include "Fahrausnahme.h"

class Losfahren : public Fahrausnahme
{
	public:
		Losfahren(Fahrzeug& aFzg, Weg& aWeg);

		virtual void vBearbeiten();

		virtual ~Losfahren();
};
