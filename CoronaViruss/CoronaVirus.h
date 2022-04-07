#pragma once
#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <vector>
#include<list>
using namespace std;

class CoronaVirus
{
public:
	CoronaVirus();
	~CoronaVirus();
	CoronaVirus(CoronaVirus* corona);

	string getDna();
	void setDna(string dna);
	int getResistance();
	void setResistance(int resistance);
	

	void loadADNInformation();
	void reduceResistance(int i_medicineResistance);
	virtual void doBorn() = 0;
	virtual vector<CoronaVirus*> doClone() = 0;
	virtual void doDie() = 0;
	virtual void initResistance() = 0;
	virtual void getDataOfVirus() = 0;
private:
	string m_dna;
	int m_resistance;
};
int randomNumber(int start, int end);
void log(string i_smg);


