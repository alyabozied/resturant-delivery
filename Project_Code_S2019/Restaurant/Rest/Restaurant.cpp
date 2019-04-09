#define _CRT_SECURE_NO_WARNINGS
#define _CRT_NONSTDC_NO_DEPRECATE
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <conio.h>
#include <stdio.h>
#include <math.h>
#include <io.h>
#include <fcntl.h>
#include <malloc.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <cstdlib>
#include <time.h>
#include <iostream>
#include <fstream>
#include "Restaurant.h"
#include "..\Events\ArrivalEvent.h"
#include "..\Events\CancelationEvent.h"
#include "..\Events\PromotionEvent.h"
using namespace std;


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


int Restaurant::GetAutoProm()const
{
	return AutoProm;
}

void Restaurant::SetAutoProm(int x)
{
	AutoProm = AutoProm > 0 ? AutoProm : 10;
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
	while(!ReadFile()){}
	int currstep = 1 ;
	PrintStatuesBar();
	bool FlagOrd=true;
	while(!EventsQueue.isEmpty() || FlagOrd )
	{
		Order *ord=nullptr;
		ExecuteEvents(currstep);
		FlagOrd=LoadGUI();
		char timestep[10];
		_itoa_s(currstep,timestep,10);			
		pGUI->waitForClick();
		pGUI->UpdateInterface();
		PrintStatuesBar();
		pGUI->DrawTimeStepCenter(timestep);
		currstep++;
		DeleteMax();
		pGUI->ResetDrawingList();
		FlagOrd=LoadGUI();
		pGUI->waitForClick();
		PrintStatuesBar();
		pGUI->UpdateInterface();
		pGUI->DrawTimeStepCenter(timestep);
		pGUI->ResetDrawingList();

	
	}
	//free the space allocated for the motorcycles
	for (int i = 0; i < 4; i++)
	{
		GetRegion(i)->DeleteMotors();
	}
	pGUI->PrintMessage("generation done, click to END program");
	pGUI->waitForClick();

}
void Restaurant::PrintStatuesBar()
{

	char NM[4], VM [4], FM[4], NOrd [4], VOrd[4], FOrd[4];
	string RN1 ="Region1 NMotors: "+string(itoa(R[0].Get_NMotorC(),NM,10))+",    Region1 NOrders: "+string(itoa(R[0].getNcount(),NOrd,10));			
	string RV1 =",    Region1 VMotors: "+string(itoa(R[0].Get_VMotorC(),VM,10))+",    Region1 VOrders: "+string(itoa(R[0].getVcount(),VOrd,10));			
	string RF1 =",    Region1 FMotors: "+string(itoa(R[0].Get_FMotorC(),FM,10))+",    Region1 FOrders: "+string(itoa(R[0].getFcount(),FOrd,10));			
	string RN2 ="Region2 NMotors: "+string(itoa(R[1].Get_NMotorC(),NM,10))+",    Region2 NOrders: "+string(itoa(R[1].getNcount(),NOrd,10));			
	string RV2 =",    Region2 VMotors: "+string(itoa(R[1].Get_VMotorC(),VM,10))+",    Region2 VOrders: "+string(itoa(R[1].getVcount(),VOrd,10));			
	string RF2 =",    Region2 FMotors: "+string(itoa(R[1].Get_FMotorC(),FM,10))+",    Region2 FOrders: "+string(itoa(R[1].getFcount(),FOrd,10));			
	string RN3 ="Region3 NMotors: "+string(itoa(R[2].Get_NMotorC(),NM,10))+",    Region3 NOrders: "+string(itoa(R[2].getNcount(),NOrd,10));			
 	string RV3 =",    Region3 VMotors: "+string(itoa(R[2].Get_VMotorC(),VM,10))+",    Region3 VOrders: "+string(itoa(R[2].getVcount(),VOrd,10));		
	string RF3 =",    Region3 FMotors: "+string(itoa(R[2].Get_FMotorC(),FM,10))+",    Region3 FOrders: "+string(itoa(R[2].getFcount(),FOrd,10));		
	string RN4 ="Region4 NMotors: "+string(itoa(R[3].Get_NMotorC(),NM,10))+",    Region4 NOrders: "+string(itoa(R[3].getNcount(),NOrd,10));			
	string RV4 =",    Region4 VMotors: "+string(itoa(R[3].Get_VMotorC(),VM,10))+",    Region4 VOrders: "+string(itoa(R[3].getVcount(),VOrd,10));			
	string RF4 =",    Region4 FMotors: "+string(itoa(R[3].Get_FMotorC(),FM,10))+",    Region4 FOrders: "+string(itoa(R[3].getFcount(),FOrd,10));
	pGUI->PrintMessage(RN1+RV1+RF1,RN2+RV2+RF2,RN3+RV3+RF3,RN4+RV4+RF4);


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
		 tmp=R[i].dequeueN(1);
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
				deletedOrd=R[i].dequeueN(1);
				delete deletedOrd;
				deletedOrd=nullptr;
			}
	}

}

