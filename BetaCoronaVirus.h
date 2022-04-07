#pragma once
#include "CoronaVirus.h"
#include "Protein.h"
#include "Definition.h"
class BetaCoronaVirus :
	public CoronaVirus
{

	MyProtein m_protein;

public:

	BetaCoronaVirus();

	BetaCoronaVirus(const BetaCoronaVirus &av);

	~BetaCoronaVirus();

	void doBorn() override;

	std::list<CoronaVirus*> doClone() override;
	

	void doDie() override;
	

	void initResistance() override;
	

};

