#ifndef __RESTAURANT_H_
#define __RESTAURANT_H_

#include "..\CMUgraphicsLib\CMUgraphics.h"
#include "..\Generic_DS\Queue.h"
#include "..\Events\Event.h"
#include "..\InputFile.h"
#include "..\OutputFile.h"
#include "..\GUI\GUI.h"
#include "..\Region.h"
#include "..\Defs.h"
#include "Order.h"


class OutputFile;
// it is the maestro of the project
class Restaurant  
{	
private:
	OutputFile *Out;                        //to write on the file and closes at the end of the program
	GUI *pGUI;
	Queue <Event*> EventsQueue;				//Queue of all events that will be loaded from file
	priorityQueue <Order*> ServedOrder;     //to store the orders being seved with the finish time as priority to print them
	Region R[4];
	int AutoProm;

public:
	Restaurant();
	~Restaurant();
	void AddEvent(Event* pE);	        //adds a new event to the queue of events
	void ExecuteEvents(int TimeStep);	//executes all events at current timestep
	void SetAutoProm(int);
	int GetAutoProm() const;
	Region* GetRegion(int);
	void RunSimulation();				//prompt the user to choose the mode to start the simulation
	bool ReadFile();					//function to read input from a file
	void PrintStatusBar();				//prints information about different regions
	void MODEINTR();					//the simple simulation function
	bool LoadGUI();						//to load the gui array of pointers with orders to draw
	void AssignOrders(int);					//delete the order which should be deleted in the current time step
	void PrintOutfile();
};

#endif