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

////////////////////////////////////////////////////////////////////////////////////////////////
//																							  //
//								different setters and getters								  //
//																							  //	
////////////////////////////////////////////////////////////////////////////////////////////////



int Restaurant::GetAutoProm()const
{
	return AutoProm;
}

void Restaurant::SetAutoProm(int x)
{
	AutoProm = AutoProm > 0 ? AutoProm : 10;
}

Region* Restaurant::GetRegion(int index)
{
	return &R[index];
}



////////////////////////////////////////////////////////////////////////////////////////////////
//																							  //
//									Event handling functions								  //
//																							  //	
////////////////////////////////////////////////////////////////////////////////////////////////

//adds a new event to the queue of events
void Restaurant::AddEvent(Event* pE)	
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


////////////////////////////////////////////////////////////////////////////////////////////////
//																							  //
//									input reading function									  //
//																							  //	
////////////////////////////////////////////////////////////////////////////////////////////////


bool Restaurant::ReadFile()
{
	InOutFile loadfile(this, pGUI);
	if(loadfile.Read())
		return true;
	return false;
}


////////////////////////////////////////////////////////////////////////////////////////////////
//																							  //
//								a simple simulation function								  //
//																							  //	
////////////////////////////////////////////////////////////////////////////////////////////////

void Restaurant::simulate()  
{
	//prompt the user again and again till a valid file name is entered
	while(!ReadFile()){}

	int currstep = 1 ;

	//print the different info about the different regions
	PrintStatuesBar();

	//flag to check if there is still an order not served so simulation doesn't stop
	bool FlagOrd=true;

	while(!EventsQueue.isEmpty() || FlagOrd )
	{
		Order *ord=nullptr;
		ExecuteEvents(currstep);
		//load gui returns true if there is still orders not served
		FlagOrd=LoadGUI();
		char timestep[10];
		_itoa_s(currstep,timestep,10);
		
		//functions needed for the interface
		pGUI->waitForClick();
		pGUI->UpdateInterface();
		PrintStatuesBar();
		pGUI->DrawTimeStepCenter(timestep);
		currstep++;

		//delete the order whose time has come
		DeleteMax();

		//update the interface after deleting the orders whose time has come
		pGUI->ResetDrawingList();
		FlagOrd=LoadGUI();
		pGUI->waitForClick();
		PrintStatuesBar();
		pGUI->UpdateInterface();
		pGUI->DrawTimeStepCenter(timestep);
		pGUI->ResetDrawingList();

	
	}
	pGUI->PrintMessage("generation done, click to END program");
	pGUI->waitForClick();

}
void Restaurant::PrintStatuesBar()
{

	char NM[4], VM [4], FM[4], NOrd [4], VOrd[4], FOrd[4];
	string RN1 ="RegionA NMotors: "+string(itoa(R[0].Get_NMotorCnt(),NM,10))+",    RegionA NOrders: "+string(itoa(R[0].GetNOrdCnt(),NOrd,10));			
	string RV1 =",    RegionA VMotors: "+string(itoa(R[0].Get_VMotorCnt(),VM,10))+",    RegionA VOrders: "+string(itoa(R[0].GetVOrdCnt(),VOrd,10));			
	string RF1 =",    RegionA FMotors: "+string(itoa(R[0].Get_FMotorCnt(),FM,10))+",    RegionA FOrders: "+string(itoa(R[0].GetFOrdCnt(),FOrd,10));			
	string RN2 ="RegionB NMotors: "+string(itoa(R[1].Get_NMotorCnt(),NM,10))+",    RegionB NOrders: "+string(itoa(R[1].GetNOrdCnt(),NOrd,10));			
	string RV2 =",    RegionB VMotors: "+string(itoa(R[1].Get_VMotorCnt(),VM,10))+",    RegionB VOrders: "+string(itoa(R[1].GetVOrdCnt(),VOrd,10));			
	string RF2 =",    RegionB FMotors: "+string(itoa(R[1].Get_FMotorCnt(),FM,10))+",    RegionB FOrders: "+string(itoa(R[1].GetFOrdCnt(),FOrd,10));			
	string RN3 ="RegionC NMotors: "+string(itoa(R[2].Get_NMotorCnt(),NM,10))+",    RegionC NOrders: "+string(itoa(R[2].GetNOrdCnt(),NOrd,10));			
 	string RV3 =",    RegionC VMotors: "+string(itoa(R[2].Get_VMotorCnt(),VM,10))+",    RegionC VOrders: "+string(itoa(R[2].GetVOrdCnt(),VOrd,10));		
	string RF3 =",    RegionC FMotors: "+string(itoa(R[2].Get_FMotorCnt(),FM,10))+",    RegionC FOrders: "+string(itoa(R[2].GetFOrdCnt(),FOrd,10));		
	string RN4 ="RegionD NMotors: "+string(itoa(R[3].Get_NMotorCnt(),NM,10))+",    RegionD NOrders: "+string(itoa(R[3].GetNOrdCnt(),NOrd,10));			
	string RV4 =",    RegionD VMotors: "+string(itoa(R[3].Get_VMotorCnt(),VM,10))+",    RegionD VOrders: "+string(itoa(R[3].GetVOrdCnt(),VOrd,10));			
	string RF4 =",    RegionD FMotors: "+string(itoa(R[3].Get_FMotorCnt(),FM,10))+",    RegionD FOrders: "+string(itoa(R[3].GetFOrdCnt(),FOrd,10));
	pGUI->PrintMessage(RN1+RV1+RF1,RN2+RV2+RF2,RN3+RV3+RF3,RN4+RV4+RF4);


}


bool Restaurant::LoadGUI()
{
	Order*const* tmpArr;

	//flag if true means there is still orders waiting to be seved
	bool flag=false;
	Order*tmpOrd;
	for (int j = 0; j < 4; j++)
	{
		//load the gui with the VIP orders
		int OrderCnt = R[j].GetVOrdCnt();
		for (int i = 0; i < OrderCnt; i++)
		{
			tmpOrd=R[j].dequeueV();
			pGUI->AddOrderForDrawing(tmpOrd);
			R[j].InsertVOrder(tmpOrd);
			flag=true;
		}

		//load the gui with the frozen orders
		tmpArr=R[j].GetArrFOrd();
		OrderCnt = R[j].GetFOrdCnt();
		for (int i = 0; i < OrderCnt; i++)
		{
			pGUI->AddOrderForDrawing(tmpArr[i]);
			flag=true;
		}
		
		//load the gui with normal orders
		tmpArr=R[j].GetArrNOrd();
		OrderCnt = R[j].GetNOrdCnt();
		for (int i = 0; i < OrderCnt; i++)
		{
			pGUI->AddOrderForDrawing(tmpArr[i]);
			flag=true;
		}
		
	}

	return flag;

}


void Restaurant::DeleteMax()
{
	Order *deletedOrd = nullptr;
	for (int i = 0; i < 4; i++)
	{
		// delete the first vip order in each region if exists
		if(R[i].GetVOrdCnt())
		{
			deletedOrd=R[i].dequeueV();
			delete deletedOrd;
			deletedOrd=nullptr;
		}

		//delete the first frozen order in each region in case exists 
		 if(!R[i].FOrdisEmpty())
		{
			deletedOrd=	R[i].dequeueF();
			delete deletedOrd;
			deletedOrd=nullptr;

		}

		//delete the first waiting order in each region case exists 
		 if(R[i].GetNOrdCnt())
			{
				deletedOrd=R[i].dequeueN(1);
				delete deletedOrd;
				deletedOrd=nullptr;
			}
	}

}


Restaurant::~Restaurant()
{
		delete pGUI;
}
