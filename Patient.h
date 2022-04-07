#pragma once
#include <list>
#include "CoronaVirus.h"
#include "AlphaCoronaVirus.h"
#include "BetaCoronaVirus.h"
#include "Definition.h"

class Patient
{
	int m_resistance;
	std::list<CoronaVirus*> m_virusList;
	int m_state;

public:

	int getState();

	void setResistance(int resistance);

	Patient();
	~Patient();
	void initResistance();
	
	void doStart();

	void takeMedicine(int i_medicineRessistance);

	void doDie();

	int totalVirusList();

};

