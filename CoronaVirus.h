#pragma once
#include<iostream>
#include<fstream>
#include<list>
#include "Definition.h"



class CoronaVirus
{
protected:
	std::string m_dna;
	int m_resistance;

public:
	int getResistance();

	void setResistance(int r);

	CoronaVirus();

	virtual ~CoronaVirus();

	CoronaVirus(const CoronaVirus &c);

	void loadADNInformation();

	void reduceResistance(int i_medicineResistance);
	
	virtual void doBorn();

	virtual std::list<CoronaVirus*> doClone();

	virtual void doDie();

	virtual void initResistance();
};

