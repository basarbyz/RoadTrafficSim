#pragma once
#include <iostream>
#include <string>
#include <iomanip>
#include "SimuClient.h"

using namespace std;

extern double dGlobaleZeit;

class Simulationsobjekt
{
	private:
		static int p_iMaxID;

	protected:
		string p_sName = "";
		const int  p_iID;
		double p_dZeit = 0;

	public:
		Simulationsobjekt();
		Simulationsobjekt(string sName);
		virtual ~Simulationsobjekt();

		static void vKopf();
		virtual void vAusgeben(ostream& os) const;
		virtual void vSimulieren() = 0;
		string getName() const	{return p_sName;}

		virtual void operator=(const Simulationsobjekt&);
		virtual bool operator==(const Simulationsobjekt&);

		Simulationsobjekt(const Simulationsobjekt&) = delete;
};

ostream& operator<<(ostream& o, const Simulationsobjekt&);

