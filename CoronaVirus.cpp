#include "CoronaVirus.h"
#include "Definition.h"



int CoronaVirus::getResistance()
{
	log("CoronaVirus getterResitance()\n");
	return m_resistance;
}

void CoronaVirus::setResistance(int r)
{
	m_resistance = r;
	log("CoronaVirus setterResitance()\n");
}

CoronaVirus::CoronaVirus()
{
	doBorn();
	initResistance();
	log("CoronaVirus defaultConstructor()\n");
}

CoronaVirus::~CoronaVirus()
{
	log("CoronaVirus destructor()\n");
}

CoronaVirus::CoronaVirus(const CoronaVirus &c)
{
	m_dna = c.m_dna;
	m_resistance = c.m_resistance;
	log("CoronaVirus copyConstructor()\n");
}

void CoronaVirus::loadADNInformation()
{
	std::string temp;
	std::ifstream fileRead("ATGX.bin", std::ifstream::binary);
	int size = 0;
	fileRead.read(reinterpret_cast<char *>(&size), sizeof(size));
	temp.resize(size);
	fileRead.read(&temp[0], temp.size());
	m_dna = temp;
	fileRead.close();
	log("CoronaVirus loadADNInformation()\n");
}

void CoronaVirus::reduceResistance(int i_medicineResistance)
{
	m_resistance -= i_medicineResistance;
	log("CoronaVirus reduceResistance()\n");
}

void CoronaVirus::doBorn()
{
	loadADNInformation();
	log("CoronaVirus doBorn()\n");
}

std::list<CoronaVirus*> CoronaVirus::doClone()
{
	std::list<CoronaVirus*> virusList;
	std::cout<<"CoronaVirus doClone()\n";
	return virusList;
}

void CoronaVirus::doDie()
{
	m_dna = "";
	m_resistance = 0;
	log("CoronaVirus doDie()\n");
}

void CoronaVirus::initResistance()
{
	log("CoronaVirus initResistance()\n");
}