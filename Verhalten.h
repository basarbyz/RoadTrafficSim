#pragma once

class Weg;
class Fahrzeug;

class Verhalten
{
	protected:
		Weg& p_aWeg;

	public:
		Verhalten(Weg& aWeg);

		virtual double dStrecke(Fahrzeug& aFzg, double dZeitintervall) = 0;
		Weg& wgetWeg() const;
		double dGeschw_limit();

		virtual ~Verhalten();

};


