#include "BetaCoronavirus.h"
BetaCoronavirus::BetaCoronavirus()
{
	this->doBorn();
	this->initResistance();
	log("BetaCoronavirus BetaCoronavirus()\n");

}

BetaCoronavirus::BetaCoronavirus(BetaCoronavirus* betaVirus) {
	this->setProtein(betaVirus->getProtein());
	this->setDna(betaVirus->getDna());
	this->setResistance(betaVirus->getResistance());
	log("BetaCoronavirus BetaCoronavirus(BetaCoronavirus* betaVirus)\n");
}

BetaCoronavirus::~BetaCoronavirus()
{
	this->doDie();
	log("BetaCoronavirus ~BetaCoronavirus()\n");
}



void BetaCoronavirus::setProtein(Protein protein) {
	m_protein = protein;
}
Protein BetaCoronavirus::getProtein() {
	return m_protein;
}

// override the pure virtual class of Coronavirus 
void BetaCoronavirus::getDataOfVirus() {
	cout << "the Protein of this virus is: " << this->getProtein() << endl;
	cout << "the DNA of this virus is: " << this->getDna() << endl;
	cout << "the Resistance of this virus is: " << this->getResistance() << endl;
}
void BetaCoronavirus::doBorn() {
	this->loadADNInformation();
	if (randomNumber(1, 3) == 1) {
		m_protein = NS3;
	}
	else if (randomNumber(1, 3) == 2) {
		m_protein = NS5;
	}
	else {
		m_protein = E;
	}

	log("BetaCoronavirus doBorn()\n");
}
vector<CoronaVirus*> BetaCoronavirus::doClone() {
	vector<CoronaVirus*> newList;
	for (int i = 0; i < 2; i++)
	{
		BetaCoronavirus* beta = new BetaCoronavirus(this);
		newList.push_back(beta);
	}
	log("BetaCoronavirus doClone()\n");
	return newList;
}
void BetaCoronavirus::doDie() {	
	log("BetaCoronavirus doDie()\n");
	delete this;

}
void BetaCoronavirus::initResistance() {
	if (this->getProtein() == NS3)
	{
		this->setResistance(randomNumber(1, 10));
	}
	else if (this->getProtein() == NS5) {
		this->setResistance(randomNumber(11, 20));
	}
	else if (this->getProtein() == E) {
		this->setResistance(randomNumber(21, 30));
	}
	else {
		cout << "the Resistance of this virus hasn't been initialized yet! please check it again." << endl;
	}
	log("BetaCoronavirus initResistance()\n");
}


