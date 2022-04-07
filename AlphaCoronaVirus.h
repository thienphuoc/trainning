#pragma once
#include "CoronaVirus.h"
#include "Color.h"
#include "Definition.h"
class AlphaCoronaVirus :
	public CoronaVirus
{
	MyColor m_color;

public:

	AlphaCoronaVirus();

	AlphaCoronaVirus(const AlphaCoronaVirus &av);

	~AlphaCoronaVirus() ;

	void doBorn() override;

	std::list<CoronaVirus*> doClone() override;

	void doDie() override;

	void initResistance() override;
	
};

