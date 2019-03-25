//#include "Drawing.h"
#include <iostream>
#include "Rest\Restaurant.h"
#include "GUI\GUI.h"

using namespace std;
int main()
{
	
	Restaurant* pRest = new Restaurant;
	pRest->RunSimulation();
	
	return 0;
}
