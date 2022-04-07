#pragma once

#include "AlphaCoronavirus.h"
#include "BetaCoronavirus.h"
enum State {
	DIE,
	ALIVE
};
class Patient
{
public:
	Patient();
	~Patient();

	//get and set private data
	void setResistance(int resistance);
	int getResistance();

	void addVirutList(CoronaVirus* virut);
	void getVirutList();

	void setState(State state);
	State getState();
	//end get and set data

	//function
	void initResistance();
	void doStart();
	int totalResistanceOfVirus(vector<CoronaVirus*> virus);
	void takeMedicine(int medicine);
	void doDie();
	void getInfo();
	//end function

private:
	int m_resistance;
	vector<CoronaVirus*> m_virutList;
	State m_state;
};

