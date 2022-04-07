#pragma once
#include "CoronaVirus.h"


enum Protein {
	NS3, 
	NS5, 
	E
};
class BetaCoronavirus : public CoronaVirus
{
public:
	BetaCoronavirus();
	~BetaCoronavirus();
	BetaCoronavirus(BetaCoronavirus* betaVirus);
	
	void getDataOfVirus() override;
	void  doBorn() override;
	vector<CoronaVirus*> doClone() override;
	void doDie() override;
	void initResistance() override;



	void setProtein(Protein color);
	Protein getProtein();

	
private:
	Protein m_protein;
};

