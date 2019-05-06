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
	 NServedOrd[0] = 0;
	 NServedOrd[1] = 0;
	 NServedOrd[2] = 0;
	 NServedOrd[3] = 0;
	 FServedOrd[0] = 0;
	 FServedOrd[1] = 0;
	 FServedOrd[2] = 0;
	 FServedOrd[3] = 0;
	 VServedOrd[0] = 0;
	 VServedOrd[1] = 0;
	 VServedOrd[2] = 0;
	 VServedOrd[3] = 0;

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

void Restaurant::wait(PROG_MODE mode)
{
	if(mode == MODE_INTR)		   // Waiting to show changes before assigning motorcycles to orders
		pGUI->waitForClick();
	else
		Sleep(1000);
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
	string  PrintAssigned;

	//print the different info about the different regions
	PrintStatusBar(PrintAssigned);

	//flag to check if there is still an order not served so simulation doesn't stop
	bool FlagOrd=true,FlagunAssign[4]={true,true,true,true};
	
	while(!EventsQueue.isEmpty() || FlagOrd || FlagunAssign[0] || FlagunAssign[1] || FlagunAssign[2] || FlagunAssign[3])
	{
		
		ExecuteEvents(currstep);	   // Executing events
		_itoa_s(currstep,timestep,10); // converting timestep to be printed
		
		wait(mode);						// Waiting according to the mode of the simulation
		RestUpdate(timestep, PrintAssigned);		   // Updates the interface 
		wait(mode);

		AssignOrders(currstep, PrintAssigned);			//Assign the order whose time has come
		FlagOrd= RestUpdate(timestep, PrintAssigned);  //Updates the interface and sets the order flag
		PrintAssigned = "";
		bool FlagPrint = true;
		while(ServedOrder.getcount() && FlagPrint)
		{
			Order* tmpord = ServedOrder.getmax();
			if(tmpord->GetFinishTime() == currstep)
			{
				if(tmpord->GetType() == TYPE_NRM)
					NServedOrd[tmpord->GetRegion()]++;
				if(tmpord->GetType() == TYPE_VIP)
					VServedOrd[tmpord->GetRegion()]++;
				if(tmpord->GetType() == TYPE_FROZ)
					FServedOrd[tmpord->GetRegion()]++;
				Out.Write(tmpord);
				delete tmpord;
				ServedOrder.extractMax();
				FlagPrint = true;
			}
			else
				FlagPrint = false;
		}
		for (int i = 0; i < 4; i++)
		{
			FlagunAssign[i] = R[i].UnAssignMotors(currstep);
			R[i].Promote(AutoProm, currstep);
			
		}
		currstep++;
	}
		PrintAssigned = "";  
	
	Out.PrintStatstics();	
	pGUI->PrintMessage("generation done, click to END program","","","",PrintAssigned,"");
	pGUI->waitForClick();

}


void Restaurant::Silent()
{
	while(!ReadFile()) {}			// Reading input data from a file 
	OutputFile Out(this, pGUI);
	int currstep = 1 ;
	string  PrintAssigned ;

	//flag to check if there is still an order not served so simulation doesn't stop
	bool FlagOrd=true,FlagunAssign[4]={true,true,true,true};
	
	while(!EventsQueue.isEmpty() || FlagOrd || FlagunAssign[0] || FlagunAssign[1] || FlagunAssign[2] || FlagunAssign[3])
	{
		PrintAssigned = "";
		ExecuteEvents(currstep);
		
		//load gui returns true if there is still orders not served
		FlagOrd=LoadGUI();
		
		//Assign the order whose time has come
		
		AssignOrders(currstep, PrintAssigned);
		//update the interface after deleting the orders whose time has come
		
		FlagOrd=LoadGUI();
		for (int i = 0; i < 4; i++)
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
		PrintAssigned = "";  
		Out.PrintStatstics();	
		pGUI->PrintMessage("generation done, click to END program","","","",PrintAssigned,"");
		pGUI->waitForClick();
}

//////////////////////////////////////////////////////////////////////////////////////////////////

void Restaurant::PrintStatusBar(string actions)
{
	string assignedA = " ";
	string assignedB = " ";
	string assignedC = " ";
	string assignedD = " ";
	if(actions.length() > 2)
	{
		int pos[4];
		pos[0] = actions.find("Region1") + 7;
		pos[1] = actions.find("Region2") + 7;
		pos[2] = actions.find("Region3") + 7;
		pos[3] = actions.find("Region4") + 7;
		assignedA += actions.substr(pos[0], pos[1] - pos[0] - 7);
		assignedB += actions.substr(pos[1], pos[2] - pos[1] - 7);
		assignedC += actions.substr(pos[2], pos[3] - pos[2] - 7);
		assignedD += actions.substr(pos[3]);
	}
	char NM[4], VM [4], FM[4], NOrd [4], VOrd[4], FOrd[4];
	string RN1 ="RegionA   NMotors: "+string(itoa(R[0].Get_NMotorCnt(),NM,10))+",     NOrders: "+string(itoa(R[0].GetNOrdCnt(),NOrd,10));			
	string RV1 =",     VMotors: "+string(itoa(R[0].Get_VMotorCnt(),VM,10))+",     VOrders: "+string(itoa(R[0].GetVOrdCnt(),VOrd,10));			
	string RF1 =",     FMotors: "+string(itoa(R[0].Get_FMotorCnt(),FM,10))+",     FOrders: "+string(itoa(R[0].GetFOrdCnt(),FOrd,10));			
	string RN2 ="RegionB   NMotors: "+string(itoa(R[1].Get_NMotorCnt(),NM,10))+",     NOrders: "+string(itoa(R[1].GetNOrdCnt(),NOrd,10));			
	string RV2 =",     VMotors: "+string(itoa(R[1].Get_VMotorCnt(),VM,10))+",     VOrders: "+string(itoa(R[1].GetVOrdCnt(),VOrd,10));			
	string RF2 =",     FMotors: "+string(itoa(R[1].Get_FMotorCnt(),FM,10))+",     FOrders: "+string(itoa(R[1].GetFOrdCnt(),FOrd,10));			
	string RN3 ="RegionC   NMotors: "+string(itoa(R[2].Get_NMotorCnt(),NM,10))+",     NOrders: "+string(itoa(R[2].GetNOrdCnt(),NOrd,10));			
 	string RV3 =",     VMotors: "+string(itoa(R[2].Get_VMotorCnt(),VM,10))+",     VOrders: "+string(itoa(R[2].GetVOrdCnt(),VOrd,10));		
	string RF3 =",     FMotors: "+string(itoa(R[2].Get_FMotorCnt(),FM,10))+",     FOrders: "+string(itoa(R[2].GetFOrdCnt(),FOrd,10));		
	string RN4 ="RegionD   NMotors: "+string(itoa(R[3].Get_NMotorCnt(),NM,10))+",     NOrders: "+string(itoa(R[3].GetNOrdCnt(),NOrd,10));			
	string RV4 =",     VMotors: "+string(itoa(R[3].Get_VMotorCnt(),VM,10))+",     VOrders: "+string(itoa(R[3].GetVOrdCnt(),VOrd,10));			
	string RF4 =",     FMotors: "+string(itoa(R[3].Get_FMotorCnt(),FM,10))+",     FOrders: "+string(itoa(R[3].GetFOrdCnt(),FOrd,10));
	string R1ALL =  "RegionA [Nord:"+string(itoa(NServedOrd[0],NM,10))+",Vord:" +string(itoa(VServedOrd[0],NM,10))+",Ford :" +string(itoa(FServedOrd[0],NM,10))+"]";
	string R2ALL =  " , RegionB [Nord:" +string(itoa(NServedOrd[1],NM,10))+",Vord:" +string(itoa(VServedOrd[1],NM,10))+",Ford:" +string(itoa(FServedOrd[1],NM,10))+"]";
	string R3ALL =  " , RegionC [Nord:" +string(itoa(NServedOrd[2],NM,10))+",Vord:" +string(itoa(VServedOrd[2],NM,10))+",Ford:" +string(itoa(FServedOrd[2],NM,10))+"]";
	string R4ALL =  " , REgionD [Nord:" +string(itoa(NServedOrd[3],NM,10))+",Vord:" +string(itoa(VServedOrd[3],NM,10))+",Ford:" +string(itoa(FServedOrd[3],NM,10))+"]";
	pGUI->PrintMessage(RN1+RV1+RF1+assignedA, RN2+RV2+RF2+assignedB, RN3+RV3+RF3+assignedC, RN4+RV4+RF4+assignedD, R1ALL+R2ALL+R3ALL+R4ALL);

}


bool Restaurant::RestUpdate(string timestep, string actions)
{
		bool check = LoadGUI();
		pGUI->UpdateInterface();
		pGUI->DrawTimeStepCenter(timestep);
		PrintStatusBar(actions);
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
		//load the gui with the VIP orders
		int OrderCnt = R[j].GetVOrdCnt();
		// to store the vip orders then put them again in the priorityQ after filling the gui array
		Queue<Order*> tmpQ;
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
	}

	return flag;

}


void Restaurant::AssignOrders(int timestep, string& s)
{
	for (int i = 0; i < 4; i++)
	{
		s += "Region";
		s += to_string(i + 1);
		//	Returns the recovered motorcycles to the idle lists before assiging
		R[i].recovered(timestep);
		// Assign first vip order in each region if exists to a motorcycle
		if(R[i].GetVOrdCnt())
		{
			R[i].AssignOrdVMotor(timestep,TimeDam,TimeTir, &ServedOrder, s);
			
		}

		//Assign  first frozen order in each region in case exists to a froozen motorcycle 
		 if(!R[i].FOrdisEmpty())
		{
			R[i].AssignOrdFMotor(timestep,TimeDam,TimeTir, &ServedOrder, s);
		}

		//Assign first waiting Normal order in each region case exists to a Motorcycle 
		if(R[i].GetNOrdCnt())
		{
			R[i].AssignOrdNMotor(timestep,TimeDam,TimeTir, &ServedOrder, s);
		}
		s += " ";
	}

}

Restaurant::~Restaurant()
{
		delete pGUI;
}
