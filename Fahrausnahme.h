#pragma once
#include <exception>
#include <stdexcept>
#include "Fahrzeug.h"
#include "Weg.h"

class Fahrausnahme : std::exception
{
	protected:
			Fahrzeug& p_exceptFahrzeug;
			Weg& p_exceptWeg;
	public:
		Fahrausnahme(Fahrzeug& aFzg, Weg& aWeg);

		virtual void vBearbeiten() = 0;

		virtual ~Fahrausnahme();

};
