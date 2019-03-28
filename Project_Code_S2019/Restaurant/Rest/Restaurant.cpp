#include <cstdlib>
#include <time.h>
#include <iostream>
#include <fstream>
using namespace std;

#include "Restaurant.h"
#include "..\Events\ArrivalEvent.h"
#include "..\Events\CancelationEvent.h"
#include "..\Events\PromotionEvent.h"


Restaurant::Restaurant() 
{
	pGUI = NULL;
}

void Restaurant::RunSimulation()
{
	pGUI = new GUI;
	PROG_MODE	mode = pGUI->getGUIMode();
			switch (mode)	//Add a function for each mode in next phases
	{
	case MODE_INTR:
		break;
	case MODE_STEP:
		break;
	case MODE_SLNT:
		break;
	case MODE_Phaseone:
		simulate();

	};

}





//////////////////////////////////  Event handling functions   /////////////////////////////
void Restaurant::AddEvent(Event* pE)	//adds a new event to the queue of events
{
	EventsQueue.enqueue(pE);
}

//Executes ALL events that should take place at current timestep
void Restaurant::ExecuteEvents(int CurrentTimeStep)
{
	Event *pE;
	while( EventsQueue.peekFront(pE) )	//as long as there are more events
	{
		if(pE->getEventTime() > CurrentTimeStep )	//no more events at current time
			return;

		pE->Execute(this);
		EventsQueue.dequeue(pE);	//remove event from the queue
		delete pE;		//deallocate event object from memory
	}

}

//get region
Region* Restaurant::GetRegion(int index)
{
	return &R[index];
}



//function to read inputs from a file
bool Restaurant::ReadFile()
{
	InOutFile loadfile(this, pGUI);
	if(loadfile.Read())
		return true;
	return false;
}




Restaurant::~Restaurant()
{
		delete pGUI;
}

void Restaurant::simulate()   // Phase one simulation function and it is named simulate cause it is the only simulation function in this phase
{
	if(!ReadFile())
	{
		pGUI->waitForClick();
		return;
	}
	int currstep = 1 ;
	pGUI->PrintMessage("");
	bool FlagOrd=true;
	while(!EventsQueue.isEmpty() || FlagOrd )
	{
		Order *ord;
		ExecuteEvents(currstep);
		FlagOrd=LoadGUI();
		char timestep[10];
		itoa(currstep,timestep,10);			
		pGUI->waitForClick();
		pGUI->UpdateInterface();
		pGUI->DrawTimeStepCenter(timestep);
		pGUI->ResetDrawingList();
		currstep++;
		DeleteMax();	
	}
	//free the space allocated for the motorcycles
	for (int i = 0; i < 4; i++)
	{
		GetRegion(i)->DeleteMotors();
	}
	pGUI->PrintMessage("generation done, click to END program");
	pGUI->waitForClick();

}

bool Restaurant::LoadGUI()
{

	Queue<Order*> tmpQ;
	Order* tmp;
	bool flag=false; //active orders 
	for (int i = 0; i < 4; i++)
	{
		while(R[i].getVcount() != 0)
		{
		 tmp=R[i].dequeueV();
		pGUI->AddOrderForDrawing(tmp);
		tmpQ.enqueue(tmp);
		flag=true;
		}
		while(!tmpQ.isEmpty())
		{
			tmpQ.dequeue(tmp);
			R[i].InsertVOrder(tmp);
		}



		while(!R[i].Fisempty())
		{
		 tmp=R[i].dequeueF();
		 pGUI->AddOrderForDrawing(tmp);
		 tmpQ.enqueue(tmp);
		flag=true;
		}
		while(!tmpQ.isEmpty())
		{
			tmpQ.dequeue(tmp);
			R[i].InsertFOrder(tmp);
		}

		
		while(R[i].getNcount())
		{
		 tmp=R[i].dequeueN();
		 pGUI->AddOrderForDrawing(tmp);
		 tmpQ.enqueue(tmp);
		flag=true;

		}
		while(!tmpQ.isEmpty())
		{
			tmpQ.dequeue(tmp);
			R[i].InsertNOrder(tmp);
		}

	}

	return flag;

}


void Restaurant::DeleteMax()
{
	Order*deletedOrd=nullptr;
	for (int i = 0; i < 4; i++)
	{
		if(R[i].getVcount())
		{
			deletedOrd=R[i].dequeueV();
			delete deletedOrd;
			deletedOrd=nullptr;
		}
		else if(!R[i].Fisempty())
		{
			deletedOrd=	R[i].dequeueF();
			delete deletedOrd;
			deletedOrd=nullptr;

		}
		else if(R[i].getNcount())
			{
				deletedOrd=R[i].dequeueN();
				delete deletedOrd;
				deletedOrd=nullptr;
			}
	}

}

