#include "CoronaVirus.h"
CoronaVirus ::CoronaVirus(CoronaVirus* corona) {
	m_dna = corona->getDna();
	m_resistance = corona->getResistance();
	//log("CoronaVirus CoronaVirus(CoronaVirus* corona)\n");
};


//get and set data
string CoronaVirus::getDna() {
	return m_dna;
}
void CoronaVirus::setDna(string dna) {
	m_dna = dna;

}
int CoronaVirus::getResistance() {
	return m_resistance;

}
void CoronaVirus::setResistance(int resistance) {
	m_resistance = resistance;
}


//get data from file ATGX.bin
void CoronaVirus::loadADNInformation() {
	fstream inputData;
	inputData.open("ATGX.bin");
	inputData >> m_dna;
	inputData.close();
	//log("CoronaVirus loadADNInformation()\n");
}


//
void CoronaVirus::reduceResistance(int i_medicineResistance) {
	m_resistance = m_resistance - i_medicineResistance;
	if (m_resistance <= 0) {
		//delete this;
	}
	//log("CoronaVirus reduceResistance()\n");
}


CoronaVirus::CoronaVirus()
{ 
	log("CoronaVirus CoronaVirus()\n");
}

CoronaVirus::~CoronaVirus()
{
	log("CoronaVirus ~CoronaVirus()\n");
}



int randomNumber(int start, int end) {
	srand(time(NULL));
	return (rand() % (end - start + 1) + start);
}
void log(string i_smg) {
	//cout << i_smg;
}