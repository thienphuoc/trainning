#include "AlphaCoronavirus.h"
#include "BetaCoronavirus.h"
#include "Patient.h"

int main() {
	//test 1 fail don't load AlphaCoronavirus Destructor
	/*CoronaVirus* f1 = new AlphaCoronavirus();
	delete f1;*/

	//test 1 fail don't load BetaCoronavirus Destructor
	/*CoronaVirus* f1 = new BetaCoronavirus();
	delete f1;*/
	Patient p;
	//tesst 3 + 4 + 5 + 6
	//p.setResistance(1000);

	//test 7
	p.setResistance(2000);

	//test 3 + 4
	//const int k_medicineResistance = 10;

	//tesst 5 + 6 = 7
	const int k_medicineResistance = 160;
	while (p.getState() == 1)
	{
		p.takeMedicine(k_medicineResistance);
	}
	return 0;
}
