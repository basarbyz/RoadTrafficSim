#include "Fahrzeug.h"
#include "Fahren.h"
#include "Parken.h"
#include "PKW.h"
#include "Weg.h"

Fahrzeug::Fahrzeug():Simulationsobjekt(""){}

Fahrzeug::Fahrzeug(string sName) : Simulationsobjekt(sName){}

Fahrzeug::Fahrzeug(string sName, double dMaxGeschwindigkeit):
		Simulationsobjekt(sName),p_dMaxGeschwindigkeit((dMaxGeschwindigkeit > 0) ? dMaxGeschwindigkeit:0){}

Fahrzeug::~Fahrzeug(){}

double Fahrzeug::dGetfreierTank() const
{
	return 0.0;
}

double Fahrzeug::dgetAbschnittStrecke() const
{
	return p_dAbschnittStrecke;
}

double Fahrzeug::dGeschwindigkeit() const
{
	return p_dMaxGeschwindigkeit;
}

double Fahrzeug::dTanken(double dMenge)
{
	return dMenge;
}

void Fahrzeug::vKopf()
{
	cout<<"\n\n";
	cout << resetiosflags(ios::left)
			  << setw(6)  << "ID"
			  << setw(20) << "Name"
			  << setw(20) << "MaxGeschwindigkeit [km/h]"
			  << setw(16) << "Gesamtstrecke [km] "
			  << setw(25) << "akt. Geschwindigkeit[km/h]"
			  << setw(20) << "Gesamtverbrauch [L]"
			  << setw(25) << "akt. Tankinhalt [L]" << endl;
	cout << "----------------------------------------------------------------------------------------------------------------------------------------------------" << endl;
}

void Fahrzeug::vNeueStrecke(Weg& aWeg)
{
	p_pVerhalten = make_unique<Fahren>(aWeg);
	this->p_dAbschnittStrecke = 0;
}

void Fahrzeug::vNeueStrecke(Weg& aWeg, double Startzeitpkt)
{
	if (Startzeitpkt >= dGlobaleZeit)
	{
		p_pVerhalten = make_unique<Parken>(aWeg, Startzeitpkt);
		this->p_dAbschnittStrecke = 0;
	}
}

void Fahrzeug::vAusgeben(ostream& os) const
{
	Simulationsobjekt::vAusgeben(os);
	os << setiosflags(ios::right)
	  << setw(20)<< setprecision(5)<< p_dMaxGeschwindigkeit
	  << setw(16)<< p_dGesamtStrecke
	  << setw(20)<< setprecision(5)<< dGeschwindigkeit();
}

void Fahrzeug::vSimulieren()
{
	extern double dGlobaleZeit;
	double dFahrzeit = dGlobaleZeit - p_dZeit;

	if (dFahrzeit > 0)
	{
		if (p_pVerhalten != nullptr)
		{
			double dGefahreneStrecke =p_pVerhalten->dStrecke(*this, dFahrzeit);
			p_dGesamtStrecke += dGefahreneStrecke;
			p_dAbschnittStrecke += dGefahreneStrecke;
		}
		else
		{
			p_dGesamtStrecke += dFahrzeit * dGeschwindigkeit() ;
		}
		p_dGesamtZeit += dFahrzeit;
		p_dZeit += dFahrzeit;
	}
}

void Fahrzeug::vZeichnen(Weg& aWeg) const{}

ostream& operator<<(ostream& os, const Fahrzeug& fahrzeug)
{
	fahrzeug.vAusgeben(os);
	return os;
}

bool Fahrzeug::operator<(const Fahrzeug& fahrzeug2) const
{
	return (this->p_dGesamtStrecke < fahrzeug2.p_dGesamtStrecke)? true : false;
}

void Fahrzeug::operator=(const Fahrzeug& fahrzeug3)
{
	this->p_sName = fahrzeug3.p_sName + "-Kopie";
	this->p_dMaxGeschwindigkeit = fahrzeug3.p_dMaxGeschwindigkeit;
	this->p_dGesamtStrecke = fahrzeug3.p_dGesamtStrecke;
}

bool Fahrzeug::operator>(const Fahrzeug& fahrzeug2) const
{
	return (this->p_dGesamtStrecke > fahrzeug2.p_dGesamtStrecke)? true : false;
}
