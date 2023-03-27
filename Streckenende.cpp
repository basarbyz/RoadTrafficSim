#include "Streckenende.h"
#include "Fahrzeug.h"
#include "Weg.h"
#include "Kreuzung.h"
#include <iostream>


Streckenende::Streckenende(Fahrzeug& aFzg, Weg& aWeg): Fahrausnahme(aFzg, aWeg){}

Streckenende::~Streckenende(){}

void Streckenende::vBearbeiten()
{
	cout << "\nAusnahmeart: Streckenende\n";
	cout << "Für das Fahrzeug: " << p_exceptFahrzeug.getName()
			<< " auf dem Weg: " << p_exceptWeg.getName() << endl;

	vertagt::VListe<unique_ptr<Fahrzeug>>* fahrzeuglist = p_exceptWeg.getList();
	Kreuzung& kreuzung = p_exceptWeg.getKreuzung();
	Weg& neuweg = kreuzung.pZufaelligerWeg(p_exceptWeg);

	for (auto it = fahrzeuglist->begin(); it != fahrzeuglist->end(); it++)
	{
		if ((*it).get() == &p_exceptFahrzeug)
		{
			fahrzeuglist->erase(it);
			kreuzung.vTanken(p_exceptFahrzeug);
			neuweg.vAnnahme(move(*it));
			break;
		}
	}

	fahrzeuglist->vAktualisieren();
	cout << "ZEIT     " << ":" << dGlobaleZeit << endl;
	cout << "KREUZUNG " << ":" << kreuzung.getName() << " " << kreuzung.getTankstellen() << endl;
	cout << "WECHSEL  " << ":" << p_exceptWeg.getName() << " -> " << neuweg.getName() << endl;
	cout << "FAHRZEUG " << ":" << p_exceptFahrzeug.getName() << endl;
}
