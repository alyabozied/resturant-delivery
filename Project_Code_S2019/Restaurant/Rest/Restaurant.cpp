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
void Restaurant::ReadFile()
{
	pGUI->PrintMessage("Enter the file name: ");
	string filename = pGUI->GetString();
	ifstream InputFile(filename+".txt");
	if(!InputFile.is_open())
	{
		pGUI->PrintMessage("an error occured loading the file there may not exist a file with this name");
		return;
	}
	//speed of differnet types of motors
	int SpeedN, SpeedF, SpeedV;
	// number of different types of motors
	int	Norm, Frzn, VIP;
	//time of auto promotion and number of events
	int	AutoS, NumEvnts;
	// the timestep,ID, Distance of different orders
	int	TimeStp, ID, DST;
	double MON = 0, EXMON = 0;
	char  EVNT, TYP, REG;
	Order* pOrd = nullptr;
	Event* pEv = nullptr;
	
	InputFile >> SpeedN >> SpeedF >> SpeedV;
	//array of motors to store them
	Motorcycle**NMotors, **FMotors, **VMotors; 
	for (int i = 0; i < REG_CNT; i++)
	{
		InputFile >> Norm >> Frzn >> VIP;
			NMotors=new Motorcycle*[Norm];
			FMotors=new Motorcycle*[Frzn];
			VMotors=new Motorcycle*[VIP];

		for (int j = 0; j < Norm; j++)
		{
			NMotors[j]=new Motorcycle;
			NMotors[j]->SetID(j);
			NMotors[j]->SetSpeed(SpeedN);
			NMotors[j]->SetStatus(0);
			NMotors[j]->SetType(TYPE_NRM);
			
		}
		for (int k = 0; k < Frzn; k++)
		{
			FMotors[k]=new Motorcycle;
			FMotors[k]->SetID(k+Norm);
			FMotors[k]->SetSpeed(SpeedF);
			FMotors[k]->SetStatus(0);
			FMotors[k]->SetType(TYPE_FROZ);

		}
		for (int l = 0; l < VIP; l++)
		{
			VMotors[l]=new Motorcycle;
			VMotors[l]->SetID(Norm+Frzn+l);
			VMotors[l]->SetSpeed(SpeedV);
			VMotors[l]->SetStatus(0);
			VMotors[l]->SetType(TYPE_VIP);
		}

		GetRegion(i)->FillMotors(Norm,VIP,Frzn,NMotors,VMotors,FMotors);

	}

	
	InputFile >> AutoS;
	InputFile >> NumEvnts;

	//reads the different types of events
	while (!InputFile.eof())
	{
		// reads the first character in the line to know the type of the event to take the convinient action
		InputFile >> EVNT;
		if(toupper(EVNT) == 'R')
		{
			InputFile >> TimeStp >> TYP >> ID >> DST >> MON >> REG;
			
			// modifies the entered data for ordertype to be of desired datatype
			if(toupper(TYP) == 'N')
				TYP = TYPE_NRM;
			if(toupper(TYP) == 'V')
				TYP = TYPE_VIP;;
			if(toupper(TYP) == 'F')
				TYP = TYPE_FROZ;
			
			// modifies the entered data for region to be of desired datatype
			REG = toupper(REG) - 'A';

			if(REG >= 0 && REG <= 3)
			{
				pEv = new ArrivalEvent(TimeStp, ID,(ORD_TYPE) TYP, (REGION)REG, DST, MON);
				AddEvent(pEv);
			}

		}
		else if(toupper(EVNT) == 'X')
		{
			InputFile >> TimeStp >> ID;
			pEv = new CancelationEvent(TimeStp, ID);
			AddEvent(pEv);

		}
		else if(toupper(EVNT) == 'P')
		{
			InputFile >> TimeStp >> ID >> EXMON;
			pEv = new PromotionEvent(TimeStp, ID, EXMON);
			AddEvent(pEv);
		}
		else 
		{
			pGUI->PrintMessage("wrong file format");
		}

	}
	delete NMotors;
	delete VMotors;
	delete FMotors;
	
}




Restaurant::~Restaurant()
{
		delete pGUI;
}

void Restaurant::simulate()   // Phase one simulation function and it is named simulate cause it is the only simulation function in this phase
{
	ReadFile(); int currstep = 1 ;
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
		pGUI->DrawTimeStepCenter(currstep);
		pGUI->ResetDrawingList();
		currstep++;
		DeleteMax();	
	}
	


	

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




////////////////////////////////////////////////////////////////////////////////
/// ==> 
///  DEMO-related functions. Should be removed in phases 1&2

//This is just a demo function for project introductory phase
//It should be removed starting phase 1
/*void Restaurant::Just_A_Demo()
{
	
	//
	// THIS IS JUST A DEMO FUNCTION
	// IT SHOULD BE REMOVED IN PHASE 1 AND PHASE 2
	
	int EventCnt;	
	Order* pOrd;
	Event* pEv;
	srand(time(NULL));

	pGUI->PrintMessage("Just a Demo. Enter EVENTS Count(next phases should read I/P filename):");
	EventCnt = atoi(pGUI->GetString().c_str());	//get user input as a string then convert to integer

	pGUI->UpdateInterface();

	pGUI->PrintMessage("Generating orders randomly... In next phases, orders should be loaded from a file");
		
	int EvTime = 0;
	
	//Create Random events
	//All generated event will be "ArrivalEvents" for the demo
	for(int i=0; i<EventCnt; i++)
	{
		int O_id = i+1;
		
		//Rendomize order type
		int OType;
		if(i<EventCnt*0.2)	//let 1st 20% of orders be VIP (just for sake of demo)
			OType = TYPE_VIP;
		else if(i<EventCnt*0.5)	
			OType = TYPE_FROZ;	//let next 30% be Frozen
		else
			OType = TYPE_NRM;	//let the rest be normal

		
		int reg = rand()% REG_CNT;	//randomize region


		//Randomize event time
		EvTime += rand()%4;
		pEv = new ArrivalEvent(EvTime,O_id,(ORD_TYPE)OType,(REGION)reg);
		AddEvent(pEv);

	}	

	int CurrentTimeStep = 1;
	//as long as events queue is not empty yet
	while(!EventsQueue.isEmpty())
	{
		//print current timestep
		char timestep[10];
		itoa(CurrentTimeStep,timestep,10);	
		pGUI->PrintMessage(timestep);


		ExecuteEvents(CurrentTimeStep);	//execute all events at current time step
		//The above line may add new orders to the DEMO_Queue

		//Let's draw all arrived orders by passing them to the GUI to draw

		while(EventsQueue.dequeue(pOrd))
		{
			pGUI->AddOrderForDrawing(pOrd);
			pGUI->UpdateInterface();
		}
		Sleep(1000);
		CurrentTimeStep++;	//advance timestep
	}


	pGUI->PrintMessage("generation done, click to END program");
	pGUI->waitForClick();

	
}*/
////////////////

void Restaurant::AddtoQueue(Order *pOrd)
{
	Queue1.enqueue(pOrd);
}

Order* Restaurant::getOrder()
{
	Order* pOrd;
	Queue1.dequeue(pOrd);
	return pOrd;

}


/// ==> end of DEMO-related function