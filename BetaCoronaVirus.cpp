#include "BetaCoronaVirus.h"


BetaCoronaVirus::BetaCoronaVirus()
{
	doBorn();
	initResistance();
	log("BetaCoronaVirus constructor()\n");
}

BetaCoronaVirus::BetaCoronaVirus(const BetaCoronaVirus &av)
{
	m_dna = av.m_dna;
	m_resistance = av.m_resistance;
	m_protein = av.m_protein;
	log("BetaCoronaVirus copyConstructor()\n");
}

BetaCoronaVirus::~BetaCoronaVirus()
{
	doDie();
	log("BetaCoronaVirus destructor()\n");
}

void BetaCoronaVirus::doBorn()
{
	loadADNInformation();
	m_protein = static_cast<MyProtein>(rand() % E);
	log("BetaCoronaVirus doBorn()\n");
}

std::list<CoronaVirus*> BetaCoronaVirus::doClone()
{
	std::list<CoronaVirus*> res;
	res.push_back(new CoronaVirus(*this));
	res.push_back(new CoronaVirus(*this));
	log("BetaCoronaVirus doClone()\n");
	return res;
}

void BetaCoronaVirus::doDie()
{
	log("BetaCoronaVirus doDie()\n");
}


void BetaCoronaVirus::initResistance()
{
	int min;
	int max;
	if (m_protein == NS3)
	{
		min = 1;
		max = 10;
	}
	else if (m_protein == NS5)
	{
		min = 11;
		max = 20;
	}
	else
	{
		min = 21;
		max = 30;
	}
	m_resistance = randRange(min, max);
	log("BetaCoronaVirus initResistance()\n");

}
