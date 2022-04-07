#include "AlphaCoronaVirus.h"

AlphaCoronaVirus::AlphaCoronaVirus()
{
	doBorn();
	initResistance();
	log("AlphaCoronaVirus constructor()\n");
}

AlphaCoronaVirus::AlphaCoronaVirus(const AlphaCoronaVirus &av)
{
	m_dna = av.m_dna;
	m_resistance = av.m_resistance;
	m_color = av.m_color;
	log("phaCoronaVirus copyConstructor()\n");
}

AlphaCoronaVirus::~AlphaCoronaVirus()
{
	doDie();
	log("AlphaCoronaVirus destructor()\n");
}

void AlphaCoronaVirus::doBorn()
{
	loadADNInformation();
	m_color = static_cast<MyColor>(rand() % BLUE);
	log("AlphaCoronaVirus doBorn()\n");
}

std::list<CoronaVirus*> AlphaCoronaVirus::doClone()
{
	std::list<CoronaVirus*> res;
	res.push_back(new AlphaCoronaVirus(*this));
	log("AlphaCoronaVirus doClone()\n");
	return res;
}

void AlphaCoronaVirus::doDie()
{
	m_dna = "";
	delete &m_dna;
	log("AlphaCoronaVirus doDie()\n");
}

void AlphaCoronaVirus::initResistance()
{
	int max=0;
	int min=0;
	if (m_color == RED)
	{
		min = 10;
		max = 20;
		m_resistance = randRange(min, min);
	}
	if (m_color == BLUE)
	{
		min = 10;
		max = 15;
	}
	m_resistance = randRange(min, max);
	log("AlphaCoronaVirus initResistance()\n");
}