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
		Simulate(mode);
		break;
	case MODE_STEP:
		Simulate(mode);
		break;
	case MODE_SLNT:
		Silent();
		break;
	case MODE_EXIT :
		break;

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

void Restaurant::SetTimeDam(int t){ TimeDam = t ;}

void Restaurant::SetTimeTir(int t ){  TimeTir = t;}
/*
int Restaurant::getTimeDam(){ return TimeDam;}

int Restaurant::getTimeTir(){ return TimeTir;}
*/
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
	InputFile loadfile(this, pGUI);
	if(loadfile.Read())
		return true;
	return false;
}


////////////////////////////////////////////////////////////////////////////////////////////////
//																							  //
//								Different modes functions									  //
//																							  //	
////////////////////////////////////////////////////////////////////////////////////////////////

void Restaurant::Simulate(PROG_MODE mode)    // Interactive mode
{
	//prompt the user again and again till a valid file name is entered
	while(!ReadFile()) {}			// Reading input data from a file 
	OutputFile Out(this, pGUI);
	int currstep = 1 ;
	char timestep[10];
	

	//print the different info about the different regions
	PrintStatusBar();

	//flag to check if there is still an order not served so simulation doesn't stop
	bool FlagOrd=true,FlagunAssign[REG_CNT]={true,true,true,true};
	
	while(!EventsQueue.isEmpty() || FlagOrd || FlagunAssign[0] || FlagunAssign[1] || FlagunAssign[2] || FlagunAssign[3])
	{
		ExecuteEvents(currstep);	   // Executing events
		_itoa_s(currstep,timestep,10); // converting timestep to be printed
		
		if(mode == MODE_INTR)		   // Waiting according to the mode of operation
			pGUI->waitForClick();
		//else 
			//Sleep(1000);

		RestUpdate(timestep);		   // Updates the interface 

		if(mode == MODE_INTR)		   // Waiting to show changes before assigning motorcycles to orders
			pGUI->waitForClick();
		else
			Sleep(1000);

		AssignOrders(currstep);			//Assign the order whose time has come
		FlagOrd= RestUpdate(timestep);  //Updates the interface and sets the order flag
		bool FlagPrint = true;
		while(ServedOrder.getcount() && FlagPrint)
		{
			Order* tmpord = ServedOrder.getmax();
			if(tmpord->GetFinishTime() == currstep)
			{
					Out.Write(tmpord);
					delete tmpord;
					ServedOrder.extractMax();
					FlagPrint = true;
			}
			else
				FlagPrint = false;
		}
		for (int i = 0; i < REG_CNT; i++)
		{
			FlagunAssign[i] = R[i].UnAssignMotors(currstep);
			R[i].Promote(AutoProm, currstep);
			
		}
		currstep++;
		
	}
	
	Out.PrintStatstics();	
	pGUI->PrintMessage("generation done, click to END program");
	pGUI->waitForClick();

}

void Restaurant::Silent()
{
	while(!ReadFile()) {}			// Reading input data from a file 
	OutputFile Out(this, pGUI);
	int currstep = 1 ;


	//flag to check if there is still an order not served so simulation doesn't stop
	bool FlagOrd=true,FlagunAssign[REG_CNT]={true,true,true,true};
	
	while(!EventsQueue.isEmpty() || FlagOrd || FlagunAssign[0] || FlagunAssign[1] || FlagunAssign[2] || FlagunAssign[3])
	{
		ExecuteEvents(currstep);
		
		//load gui returns true if there is still orders not served
		FlagOrd=LoadGUI();
		
		//Assign the order whose time has come
		
		AssignOrders(currstep);
		//update the interface after deleting the orders whose time has come
		
		FlagOrd=LoadGUI();
		for (int i = 0; i < REG_CNT; i++)
		{
			FlagunAssign[i] = R[i].UnAssignMotors(currstep);
			R[i].Promote(AutoProm, currstep);
		}
		bool FlagPrint = true;
		while(ServedOrder.getcount() && FlagPrint)
		{
			Order* tmpord = ServedOrder.getmax();
			if(tmpord->GetFinishTime() == currstep)
			{
					Out.Write(tmpord);
					delete tmpord;
					ServedOrder.extractMax();
					FlagPrint = true;
			}
			else
				FlagPrint = false;
		}
		currstep++;
	}
	Out.PrintStatstics();	
	pGUI->PrintMessage("generation done, click to END program");
	pGUI->waitForClick();
}

//////////////////////////////////////////////////////////////////////////////////////////////////

void Restaurant::PrintStatusBar()
{

	char NM[REG_CNT], VM [REG_CNT], FM[REG_CNT], NOrd [REG_CNT], VOrd[REG_CNT], FOrd[REG_CNT];
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

bool Restaurant::RestUpdate(string timestep)
{
		bool check = LoadGUI();
		pGUI->UpdateInterface();
		pGUI->DrawTimeStepCenter(timestep);
		PrintStatusBar();
		return check;
}

bool Restaurant::LoadGUI()
{
	Order*const* tmpArr;

	//flag if true means there is still orders waiting to be seved
	bool flag = false;
	Order*tmpOrd;
	for (int j = 0; j < REG_CNT; j++)
	{
		//load the gui with the party orders
		int OrderCnt = R[j].GetPOrdCnt();
		// to store the party orders then put them again in the priorityQ after filling the gui array
		Queue<Order*> tmpQ;
		for (int i = 0; i < OrderCnt; i++)
		{
			tmpOrd = R[j].dequeueP();
			pGUI->AddOrderForDrawing(tmpOrd);
			tmpQ.enqueue(tmpOrd);
			flag=true;
		}
		while(!tmpQ.isEmpty())
		{
			tmpQ.dequeue(tmpOrd);
			R[j].InsertPOrder(tmpOrd);
		}
		//load the gui with the VIP orders
		 OrderCnt = R[j].GetVOrdCnt();
		// to store the vip orders then put them again in the priorityQ after filling the gui array
		for (int i = 0; i < OrderCnt; i++)
		{
			tmpOrd = R[j].dequeueV();
			pGUI->AddOrderForDrawing(tmpOrd);
			tmpQ.enqueue(tmpOrd);
			flag=true;
		}
		while(!tmpQ.isEmpty())
		{
			tmpQ.dequeue(tmpOrd);
			R[j].InsertVOrder(tmpOrd);
		}

		//load the gui with the frozen orders
		tmpArr = R[j].GetArrFOrd();
		OrderCnt = R[j].GetFOrdCnt();
		for (int i = 0; i < OrderCnt; i++)
		{
			pGUI->AddOrderForDrawing(tmpArr[i]);
			flag=true;
		}
		delete []tmpArr;
		tmpArr = nullptr;
		//load the gui with normal orders
		tmpArr = R[j].GetArrNOrd();
		OrderCnt = R[j].GetNOrdCnt();
		for (int i = 0; i < OrderCnt; i++)
		{
			pGUI->AddOrderForDrawing(tmpArr[i]);
			flag=true;
		}
		delete tmpArr;
		tmpArr = nullptr;
		//load the gui with the frozen orders
		tmpArr = R[j].GetArrNearOrd();
		OrderCnt = R[j].GetNearOrdCnt();
		for (int i = 0; i < OrderCnt; i++)
		{
			pGUI->AddOrderForDrawing(tmpArr[i]);
			flag=true;
		}
		delete []tmpArr;
		tmpArr = nullptr;
	}

	return flag;

}


void Restaurant::AssignOrders(int timestep)
{
	bool Flag = true;
	for (int i = 0; i < REG_CNT; i++)
	{
		//	Returns the recovered motorcycles to the idle lists before assiging
		R[i].recovered(timestep);

		// Assign first party order in each region if exists to a motorcycle
		if(R[i].GetPOrdCnt())
		{
			Flag = R[i].AssignOrdPMotor(timestep,TimeDam,TimeTir, &ServedOrder);
		}
		if(Flag)
		{
		// Assign first vip order in each region if exists to a motorcycle
		if(R[i].GetVOrdCnt())
		{
			R[i].AssignOrdVMotor(timestep,TimeDam,TimeTir, &ServedOrder);
		}
		//Assign  first frozen order in each region in case exists to a froozen motorcycle 
		 if(!R[i].FOrdisEmpty())
		{
			R[i].AssignOrdFMotor(timestep,TimeDam,TimeTir, &ServedOrder);
		}

		//Assign first waiting Normal order in each region case exists to a Motorcycle 
		if(R[i].GetNOrdCnt())
		{
			R[i].AssignOrdNMotor(timestep,TimeDam,TimeTir, &ServedOrder);
		}
		}
		//Assign first waiting Near order in each region case exists to a Motorcycle 
		if(R[i].GetNearOrdCnt())
		{
			R[i].AssignOrdNeardelivery(timestep,TimeDam,TimeTir, &ServedOrder);
		}
		
	}

}



Restaurant::~Restaurant()
{
		delete pGUI;
}
