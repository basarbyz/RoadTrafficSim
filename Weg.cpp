#include "Weg.h"
#include "Fahrzeug.h"
#include "Verhalten.h"
#include "Fahrausnahme.h"

Weg::Weg() : Simulationsobjekt(){}

Weg::Weg(string sName, double dLaenge, TempolimitNS::Tempolimit  eTempoLimit, bool bUeberholverbot):
	 Simulationsobjekt(sName), p_dLaenge(dLaenge), p_eTempolimit(eTempoLimit), p_bUeberholverbot(bUeberholverbot){}

Weg::Weg(string sName, double dLaenge, weak_ptr<Kreuzung> pKreuzung,TempolimitNS::Tempolimit eTempoLimit, bool bUeberholverbot):
				Simulationsobjekt(sName), p_dLaenge(dLaenge), p_pKreuzung(pKreuzung),
				p_eTempolimit(eTempoLimit),p_bUeberholverbot(bUeberholverbot){}

Weg::~Weg(){}

double Weg::getTempolimit()
{
	return (double) p_eTempolimit;//gibt entsprechende geschw. zurück
}

double Weg::dgetLaenge() const
{
	return p_dLaenge;
}

void Weg::vKopf()
{
	Simulationsobjekt::vKopf();
	cout << resetiosflags(ios::left);
	cout << setw(28) << "|  Laenge"
			  << setw(20) << "|  Fahrzeuge\n";
	cout << "-----------------------------------------------------------------------------------------------------" << endl;
}

void Weg::vSimulieren()
{
	setVirtuelleSchranke(100000000000);
	p_pFahrzeuge.vAktualisieren(); //aktualieseren der Liste vor jeder Simulation,

	for (auto &fzg :  p_pFahrzeuge)
	{
		try
		{
 			fzg->vSimulieren();
			fzg->vZeichnen(*this);
		}
		catch (Fahrausnahme& Ausnahme1)
		{
			Ausnahme1.vBearbeiten(); //wenn eine bestimmte Ausnahme geworfen wurde, entsprechende vBearbeiten() wird dann aufgereufen
		}
	}

	p_pFahrzeuge.vAktualisieren(); //aktualieseren der Liste nach jeder Simulation,
	p_dZeit = dGlobaleZeit;
}

void Weg::vAusgeben(ostream& os) const
{
	Simulationsobjekt::vAusgeben(os);
	os << resetiosflags(ios::right);
	os << setw(8) << ":" << setw(10) << p_dLaenge << setw(10) << setprecision(5)
	   << "( " ;
	for (auto & fzg : p_pFahrzeuge)
	{
		os << (fzg)->getName()<<" ";
	}
	os << " )" << endl;

}

void Weg::vAnnahme(unique_ptr<Fahrzeug> ptrFahrzeug)
{
	ptrFahrzeug->vNeueStrecke(*this);
	p_pFahrzeuge.push_back(move(ptrFahrzeug));
}

void Weg::vAnnahme(unique_ptr<Fahrzeug> ptrFahrzeug, double dStartzeitpkt)
{
	ptrFahrzeug->vNeueStrecke(*this, dStartzeitpkt);
	p_pFahrzeuge.push_front(move(ptrFahrzeug));
}

unique_ptr<Fahrzeug> Weg::pAbgabe(const Fahrzeug& aFzg) // @suppress("No return")
{
	for (auto it = p_pFahrzeuge.begin(); it != p_pFahrzeuge.end(); it++)
	{
		if (**it == aFzg && (*it != nullptr))
		{
			auto pFzgLokal = move(*it);
			p_pFahrzeuge.erase(it);
			return pFzgLokal;
		}
	}
}

double Weg::getVirtuelleSchranke()
{
	if (p_bUeberholverbot)
	{
		return p_dVirtuelleSchranke;
	}
	return 10000000000;
}

void Weg::setVirtuelleSchranke(double dVirtuelleSchranke)
{
	p_dVirtuelleSchranke = dVirtuelleSchranke;
}

void Weg::setRueckweg(weak_ptr<Weg> pRueckweg)
{
	p_pRueckWeg = pRueckweg;
}

Weg& Weg::getRueckweg()
{
	return *p_pRueckWeg.lock();
}

Kreuzung& Weg::getKreuzung()
{
	return *p_pKreuzung.lock();
}







