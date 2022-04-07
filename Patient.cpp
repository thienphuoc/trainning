#include "Patient.h"

int Patient::getState()
{
	return m_state;
}

void Patient::setResistance(int resistance)
{
	m_resistance = resistance;
}

Patient::Patient()
{
	doStart();

}
Patient::~Patient()
{

}
void Patient::initResistance()
{
	int min = 1000;
	int max = 9000;
	m_resistance = randRange(min, max);

}

void Patient::doStart()
{
	m_state = 1;
	const int k_virusNUm = 5;
	int numberOfVirus = randRange(10, 20);
	for (int i = 0; i < numberOfVirus; i++)
	{
		BetaCoronaVirus *v = new BetaCoronaVirus();
		v->setResistance(90);
		m_virusList.push_back(v);
	}
	for (int i = 0; i < numberOfVirus; i++)
	{
		AlphaCoronaVirus *v = new AlphaCoronaVirus();
		v->setResistance(150);
		m_virusList.push_back(v);
	}
	m_state = 1;
}

void Patient::takeMedicine(int i_medicineRessistance)
{
	int mr = randRange(1, 60);
	std::cout << "takeMedicine:begin:\n";
	std::cout << "takeMedicine:i_medicineResistance ="<<i_medicineRessistance << std::endl;

	std::cout << "takeMedicine:m_resistance ="<<m_resistance << std::endl;
	std::cout << "takeMedicine:m_virusList.size() ="<<m_virusList.size()<<std::endl;

	std::list<CoronaVirus*> stillAliveVirusList;

	for(CoronaVirus* c: m_virusList)
	{
		c->reduceResistance(i_medicineRessistance);
		if (c->getResistance() > 0)
		{
			stillAliveVirusList.push_back(c);

		}
		else
		{
			m_virusList.remove(c);
		}
	}

	

	for (CoronaVirus *c : stillAliveVirusList)
	{
		std::list<CoronaVirus*> temp = c->doClone();
		for (CoronaVirus *t : temp)
		{
			m_virusList.push_back(t);
		}
	}

	if (m_resistance < totalVirusList())
	{
		doDie();
	}


	std::cout<<"takeMedicine:end:\n";
	std::cout << "takeMedicine:i_medicineResistance ="<<i_medicineRessistance << std::endl;
	std::cout << "takeMedicine:m_resistance ="<<m_resistance << std::endl;
	std::cout<<"takeMedicine:totalResistanceOfVirus ="<<totalVirusList() << std::endl;
	std::cout << "takeMedicine:m_virusList.size() ="<<m_virusList.size()<<std::endl;


}

void Patient::doDie()
{
	m_state = 0;
	delete &m_virusList;
}

int Patient::totalVirusList()
{
	int total = 0;
	for (CoronaVirus *c : m_virusList)
	{
		total += c->getResistance();
	}
	return total;
}