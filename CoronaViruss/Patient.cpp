#include "Patient.h"
#include <vector>
Patient::Patient()
{
	this->initResistance();
	this->doStart();
	m_state = ALIVE;
	log("Patient Patient()\n");
	
}

Patient::~Patient()
{
	this->doDie();
	log("Patient ~Patient()\n");
}

//get and set private data
void Patient::setResistance(int resistance) {
	m_resistance = resistance;
}
int Patient::getResistance() {
	return m_resistance;
}

void Patient::setState(State state) {
	m_state = state;
}
State Patient::getState() {
	return m_state;
	log("Patient getM_state()\n");
}
//end get and set data

//function
void Patient::getInfo() {
	cout << "state: " << m_state << endl;
	cout << "resistance: " << m_resistance << endl;
}


void Patient::addVirutList(CoronaVirus* virut) {
	m_virutList.push_back(virut);
}

void Patient::initResistance() {
	this->setResistance(randomNumber(1000, 9000));
	log("Patient initResistance()\n");
}

void Patient::doStart() {
	//tesst 3
	//m_state = ALIVE;
	//const int k_virusNum = 10 ;//randomNumber(10, 20);
	//for (size_t i = 0; i < k_virusNum; i++) 
	//{
	//	CoronaVirus* virus = new AlphaCoronavirus();
	//	virus->setResistance(100);
	//	m_virutList.push_back(virus);
	//}

	//test 4
	/*m_state = ALIVE;
	const int k_virusNum = 10;
	for (size_t i = 0; i < k_virusNum; i++)
	{
		CoronaVirus* virus = new BetaCoronavirus();
		virus->setResistance(100);
		m_virutList.push_back(virus);
	}*/

	//test 5
	//m_state = ALIVE;
	//const int k_virusNum = 10;//randomNumber(10, 20);
	//for (size_t i = 0; i < k_virusNum; i++)
	//{
	//	CoronaVirus* virus = new AlphaCoronavirus();
	//	virus->setResistance(100);
	//	m_virutList.push_back(virus);
	//}

	//test 6
	/*m_state = ALIVE;
	const int k_virusNum = 10;
	for (size_t i = 0; i < k_virusNum; i++)
	{
		CoronaVirus* virus = new BetaCoronavirus();
		virus->setResistance(100);
		m_virutList.push_back(virus);
	}*/

	//test 7
	m_state = ALIVE;
	const int k_virusNum = 5;
	for (size_t i = 0; i < k_virusNum; i++)
	{
		CoronaVirus* virus = new AlphaCoronavirus();
		virus->setResistance(150);
		m_virutList.push_back(virus);
	}
	for (size_t i = 0; i < k_virusNum; i++)
	{
		CoronaVirus* virus = new BetaCoronavirus();
		virus->setResistance(90);
		m_virutList.push_back(virus);
	}



	/*int numberOfVirus = randomNumber(10, 20);
	for (int i = 0; i < numberOfVirus; i++)
	{
		int random = randomNumber(1, 2);
		if (random == 1)
		{
			AlphaCoronavirus* alpha = new AlphaCoronavirus();
			this->addM_virutList(alpha);
		}
		else if (random == 2) {
			BetaCoronavirus* beta = new BetaCoronavirus();
			this->addM_virutList(beta);
		}
		else {
			cout << "Find a error in doStart function in Patient.cpp" << endl;
		}
	}*/
	log("Patient doStart()\n");
}

int Patient::totalResistanceOfVirus(vector<CoronaVirus*> virus) {
	int totalResistanceOfVirus = 0;
	for (auto i : m_virutList)
	{
		totalResistanceOfVirus += i->getResistance();
	}
	return totalResistanceOfVirus;
}

void Patient::doDie() {
	m_state = DIE;
	//m_virutList.clear();
	log("Patient doDie()\n");
}

void Patient::takeMedicine(int i_medicineResistance) {
	cout << "takeMedicine|begin\n";
	cout << "takeMedicine|i_medicineResistance = " << i_medicineResistance << endl;
	cout << "takeMedicine|m_resistance = " << m_resistance << endl;
	cout << "takeMedicine|m_virutList.size() = " << m_virutList.size() << endl;
	
	vector<CoronaVirus*> newList;
	for (auto i : m_virutList)
	{
		//i_medicineResistance = randomNumber(1, 60);
		i->reduceResistance(i_medicineResistance);
		if (i->getResistance() > 0)
		{
			vector<CoronaVirus*> newCorona = i->doClone();
			newList.insert(newList.end(),newCorona.begin(),newCorona.end());
		}
		else {
			i->setResistance(0);
		}
	}
	
	for (auto i : newList)
	{
		m_virutList.push_back(i);
	}
	newList.clear();
	if (m_resistance < totalResistanceOfVirus(m_virutList))
	{
		this->doDie();
	}
	
	log("Patient takeMedicine()\n");
	cout << "takeMedicine|end\n";
	cout << "takeMedicine|i_medicineResistance = " << i_medicineResistance << endl;
	cout << "takeMedicine|m_resistance = " << m_resistance << endl;
	cout << "takeMedicine|totalResistanceOfVirus = " << this->totalResistanceOfVirus(m_virutList) << endl;
	cout << "takeMedicine|m_virutList.size() = " << m_virutList.size() << endl;
}


//end function