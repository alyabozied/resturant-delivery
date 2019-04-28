#include "delivery.h"




delivery::delivery()
{
	Backtime=0;
	speed = 0;
	status = IDLE;
}

delivery::delivery(int ID, double Speed, STATUS Status, ORD_TYPE Type, REGION r)
{
	Backtime=0;
	SetID(ID);
	SetSpeed(Speed);
	SetStatus(Status);
	SetType(Type);
	SetRegion(r);
}


////////////////////////////////////////////////////////////////////////////////////////////////
//																							  //
//									setters and getters										  //
//																							  //	
////////////////////////////////////////////////////////////////////////////////////////////////

int delivery:: GetID()const
{
	return ID;
}

double delivery:: GetSpeed()const
{
	return speed;
}

STATUS delivery:: GetStatus()const
{
	return status;
}
ORD_TYPE delivery:: GetType()const
{
	return type;
}
void delivery:: SetID(int I)
{
	ID = I > 0 ? I : 0;
}

void delivery:: SetSpeed(double S)
{
	speed = S > 0 ? S : 0;
}

void delivery:: SetStatus(STATUS St)
{
	status = (St == IDLE || St == SERV) ? St : IDLE;
}

void delivery:: SetType(ORD_TYPE T)
{
	type = (T > -1 && T < TYPE_CNT) ? T : TYPE_NRM;
}

void delivery:: SetAssignedOrd(Order*O,int timestep, int timed, int timeT)
{
	O->Delivery(speed,timestep,timed,timeT);
	AssignedOrd=O;
	SetBacktime(O->GetArrTime() + O->GetWaitingTime()+ 2* O->GetDistance()/speed);
	status=SERV;

}


void delivery:: SetBacktime(int S)
{
	Backtime = S > 0 ? S : 0 ;
}

void delivery:: SetRegion(REGION R)
{
	region=R;
}

REGION delivery:: GetRegion()const
{
	return region;
}	
Order* delivery:: GetAssignedOrd() const
{
	return AssignedOrd;
}
int  delivery:: GetArrivalTime() const
{
	return ArrivalTime;
}

bool  delivery:: operator ==(delivery d)
{
	if(ID == d.ID)
		return true;
	return false;
}

bool delivery::IsBack(int timestep)const
{
	return timestep == Backtime ; 
}
delivery::~delivery(void)
{
}
