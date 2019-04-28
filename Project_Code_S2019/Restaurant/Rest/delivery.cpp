#include "delivery.h"

delivery::delivery()
{
	speed = 0;
	status = IDLE;
}

delivery::delivery(int ID, double Speed, STATUS Status, ORD_TYPE Type, REGION r)
{
	SetID(ID);
	SetSpeed(Speed);
	SetStatus(Status);
	SetType(Type);
	SetRegion(r);
	Changepriority(0); //zero is the time of construction of the deliverys
}

////////////////////////////////////////////////////////////////////////////////////////////////
//																							  //
//									setters and getters										  //
//																							  //	
////////////////////////////////////////////////////////////////////////////////////////////////

int delivery::GetID()const
{
	return ID;
}

double delivery::GetSpeed()const
{
	return speed;
}

STATUS delivery::GetStatus()const
{
	return status;
}
ORD_TYPE delivery::GetType()const
{
	return type;
}
void delivery::SetID(int I)
{
	ID = I > 0 ? I : 0;
}

void delivery::SetSpeed(double S)
{
	speed = S > 0 ? S : 0;
}

void delivery::SetStatus(STATUS St)
{
	status = (St == IDLE || St == SERV) ? St : IDLE;
}

void delivery::SetType(ORD_TYPE T)
{
	type = (T > -1 && T < TYPE_CNT) ? T : TYPE_NRM;
}

void delivery:: SetAssignedOrd(Order*O,int timestep, int timed, int timeT)
{
	AssignedOrd=O;
	status=SERV;
	Changepriority(timestep);
	O->Delivery(this,timestep,timed,timeT);
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



////////////////////////////////////////////////////////////////////////////////////////////////
//																							  //
//							overloads to check the priority									  //
//																							  //	
////////////////////////////////////////////////////////////////////////////////////////////////

bool delivery:: operator < (delivery M)
{
	if(priority < M.priority)
		return true;
	return false;
}

bool delivery:: operator >(delivery M)
{
	if(priority > M.priority)
		return true;
	return false;
}

bool delivery:: operator ==(delivery M)
{
	if(ID == M.ID)
		return true;
	return false;
}

////////////////////////////////////////////////////////////////////////////////////////////////
//																							  //
//			    changes the priority of the delivery after the assignment to be put		  //
//				in the assigned PQ with the time at which it returns is the priority	      //
//																							  //	
////////////////////////////////////////////////////////////////////////////////////////////////

void delivery::Changepriority(int timestp)
{
	if(status == IDLE)
				priority = speed;	
	else

	{
		priority = -1*(timestp + 2 * (AssignedOrd->GetDistance() / speed)); 
	}
}


bool delivery::IsBack(int timestep)const
{
	return timestep == -priority ;
}



delivery::~delivery()
{

}

