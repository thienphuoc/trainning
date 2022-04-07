#include "AlphaCoronavirus.h"

AlphaCoronavirus::AlphaCoronavirus()
{
	this->doBorn();
	this->initResistance();
	//log("AlphaCoronavirus AlphaCoronavirus()\n");
}

AlphaCoronavirus::~AlphaCoronavirus()
{
	this->doDie();
	//log("AlphaCoronavirus ~AlphaCoronavirus()\n");
}



void AlphaCoronavirus::setColor(virusColor color) {
	m_color = color;
	//log("AlphaCoronavirus SetColor()\n");
}
virusColor AlphaCoronavirus:: getColor() {
	return m_color;
	//log("AlphaCoronavirus getColor()\n");
}

// override the pure virtual class of Coronavirus 
void AlphaCoronavirus::getDataOfVirus() {
	cout << "the Color of this virus is: " << this->getColor() << endl;
	cout << "the DNA of this virus is: " << this->getDna() << endl;
	cout << "the Resistance of this virus is: " << this->getResistance() << endl;
}
void AlphaCoronavirus::doBorn() {
	this->loadADNInformation();
	if (randomNumber(1, 2) == 1) {
		m_color = BLUE;
	}
	else {
		m_color = RED;
	}

	//log("AlphaCoronavirus doBorn()\n");
}

vector<CoronaVirus*> AlphaCoronavirus::doClone() {
	AlphaCoronavirus* newVirus = new AlphaCoronavirus();
	vector<CoronaVirus*> newList;
	newVirus->setColor(m_color);
	//cout << "color of this virus(clone): "<< m_color << endl;
	newVirus->setDna(this->getDna());
	//cout << "DNA of this virus(clone): " << this->getM_dna() << endl;
	newVirus->setResistance(this->getResistance());
	newList.push_back(newVirus);

	//log("AlphaCoronavirus doClone()\n");
	return newList;
}
void AlphaCoronavirus::doDie() {
	//log("AlphaCoronavirus doDie()\n");
	delete this;
}
void AlphaCoronavirus::initResistance() {
	if (this->getColor() == BLUE)
	{
		this->setResistance(randomNumber(10, 15));
	}
	else {
		this->setResistance(randomNumber(10, 20));
	}
	//cout << "the resistance of this virus is: " << this->getM_resistance() << endl;
	//log("AlphaCoronavirus initResistance()\n");
}



