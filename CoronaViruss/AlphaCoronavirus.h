#pragma once
#include "CoronaVirus.h"
enum virusColor {
		BLUE,
		RED
	};
class AlphaCoronavirus : public CoronaVirus
{
public:
	
	AlphaCoronavirus();
	~AlphaCoronavirus();

	void getDataOfVirus() override;
	void  doBorn() override;
	vector<CoronaVirus*> doClone() override;
	void doDie() override;
	void initResistance() override;

	

	void setColor(virusColor color);
	virusColor getColor();
private:
	virusColor m_color;
};

