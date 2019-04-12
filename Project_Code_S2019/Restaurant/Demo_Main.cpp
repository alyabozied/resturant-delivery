#include "Rest\Restaurant.h"
using namespace std;
#include <vld.h>
int main()
{

	Restaurant* pRest = new Restaurant;
	pRest->RunSimulation();
	delete pRest;
	return 0;
}
