#ifndef __RESTAURANT_H_
#define __RESTAURANT_H_

#include "..\Defs.h"
#include "..\CMUgraphicsLib\CMUgraphics.h"
#include "..\GUI\GUI.h"
#include "..\Generic_DS\Queue.h"
#include "..\Events\Event.h"
#include "..\InOutFile.h"
#include"..\Region.h"
#include "Order.h"

// it is the maestro of the project
class Restaurant  
{	
private:
	GUI *pGUI;
	Queue<Event*> EventsQueue;	//Queue of all events that will be loaded from file
	Region R[4];
	int AutoProm;

public:
	Restaurant();
	~Restaurant();
	void AddEvent(Event* pE);	//adds a new event to the queue of events
	void ExecuteEvents(int TimeStep);	//executes all events at current timestep
	Region* GetRegion(int);
	void RunSimulation();
	bool ReadFile();
	void AddtoQueue(Order* po);
	Order* getOrder();
	void PrintStatuesBar();
	void SetAutoProm(int);
	int GetAutoProm() const;
	
	

	void simulate(); // The end of this phase isa
	bool LoadGUI();
	void DeleteMax();
};

#endif