#include "Verhalten.h"
#include "Fahrzeug.h"
#include "Streckenende.h"
#include "Weg.h"


Verhalten::Verhalten(Weg& aWeg): p_aWeg(aWeg){}

Verhalten::~Verhalten(){}

Weg& Verhalten::wgetWeg() const
{
	return p_aWeg;
}

double Verhalten::dGeschw_limit()
{
	return p_aWeg.getTempolimit();
}


