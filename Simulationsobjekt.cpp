#include "Simulationsobjekt.h"

int Simulationsobjekt::p_iMaxID = 0;

Simulationsobjekt::Simulationsobjekt(): p_sName(""), p_iID(p_iMaxID++)
{
	cout<<"\n(Aufruf Standardkonstruktor)\n"
			 << "Name des Simulationsobjekt: " << p_sName
			 << "\nID: " << p_iID ;
}

Simulationsobjekt::Simulationsobjekt(string sName) : p_sName(sName), p_iID(p_iMaxID++)
{
	cout<<"\n(Aufruf Parameterkonstruktor)\n"
			 << "Name des Simulationsobjekt: " << p_sName
			 << "\nID : " << p_iID<<"\n";
}

Simulationsobjekt::~Simulationsobjekt()
{
	cout<<"\n(Aufruf Standarddestruktor) \n"
			 << "Name des zerstörten Simulationsobjekt: " << p_sName
			 << "\nID: " << p_iID << "\n" ;
}

void Simulationsobjekt::vKopf()
{
	cout<< resetiosflags(ios::left);
	cout<< setw(10) << "\nID"
			 << setw(15) << "|  Name";

}

void Simulationsobjekt::vAusgeben(ostream& os) const
{
	os << resetiosflags(ios::left);
	os << setiosflags(ios::right)
	   << setw(9) << p_iID
	   <<setiosflags(ios::left)<< setw(20) << p_sName<< resetiosflags(ios::left)<<setw(20);
}

void Simulationsobjekt::operator=(const Simulationsobjekt& obj)
{
	// ID ist const variable und kann nicht bearbeitet werden
	this->p_sName = obj.p_sName + "-Kopie";
}

bool Simulationsobjekt::operator==(const Simulationsobjekt& obj)
{
	return (this->p_iID==obj.p_iID);
}

ostream& operator<<(ostream& os, const Simulationsobjekt& obj)
{
	obj.vAusgeben(os);
	cout << "\n" ;
	return os;
}
