#include "PKW.h"
#include "Verhalten.h"
#include "Weg.h"

PKW::PKW(std::string sName, double dMaxGeschwindigkeit, double dVerbrauch, double dTankvolumen):
		Fahrzeug(sName, dMaxGeschwindigkeit), p_dVerbrauch(dVerbrauch), p_dTankvolumen(dTankvolumen),p_dTankinhalt(dTankvolumen/2){}
double PKW::dGetfreierTank() const
{
	return p_dTankvolumen - p_dTankinhalt;
}

double PKW::dTanken(double dMenge)
 {
	 double dFreierTank = p_dTankvolumen - p_dTankinhalt;

	 if (dMenge <= 0)
	 {
		 std::cout<<"Es wurde Nicht getankt.\n\n";
		 return 0;
	 }
	 else if (0 < dMenge && dMenge <= dFreierTank )
	 {
		 p_dTankinhalt += dMenge;
		 std::cout<<"Es wurde erfolgreich getankt.\n\n";
		 return dMenge;
	 }
	 else if (dMenge > dFreierTank )
	 	{
	 		std::cout << "Zu viel betankt!Sie koennen nur bis: " << dFreierTank << " Liter Tanken." << std::endl;
	 		std::cout << "" << std::endl;
	 	}
	 return dMenge;
 }

double PKW::dGeschwindigkeit() const
 {
	if(p_pVerhalten != nullptr)
		return std::min(p_pVerhalten->dGeschw_limit(), p_dMaxGeschwindigkeit);
	else
		return p_dMaxGeschwindigkeit;
 }

 void PKW::vSimulieren()
 {
	 extern double dGlobaleZeit;
	 if (p_dTankinhalt > 0)
	 	{
	 		Fahrzeug::vSimulieren();
	 		double dTankVerbrauch =(dGlobaleZeit - p_dZeit) * dGeschwindigkeit()* p_dVerbrauch / 100;
	 		p_dTankinhalt -= dTankVerbrauch;
	 		if (p_dTankinhalt < 0)
	 		{
	 			p_dTankinhalt = 0;
	 		}
	 	}
	 	else
	 	{
	 		p_dTankinhalt = 0;
	 		std::cout << "Tank von "<< this->p_sName << " ist Leer, bitte Tanken!" << std::endl;
	 	}
 }

 void PKW::vZeichnen(Weg& aWeg) const
 {
	 double dRelPosition = this->dgetAbschnittStrecke() / aWeg.dgetLaenge();
	 std::string WegName = aWeg.getName();
	 std::string PKWName = this->getName();
	 double KmH = this->dGeschwindigkeit();
	 double Tank = this->p_dTankinhalt;

	 bZeichnePKW(PKWName, WegName, dRelPosition, KmH, Tank);
 }

 void PKW::vAusgeben(std::ostream& os) const
 {
	 Fahrzeug::vAusgeben(os);
	 os << std::resetiosflags(std::ios::left);
	 os << std::setw(20) << p_dGesamtStrecke * p_dVerbrauch/100
		 << std::setw(25) << p_dTankinhalt<< std::endl;
 }
