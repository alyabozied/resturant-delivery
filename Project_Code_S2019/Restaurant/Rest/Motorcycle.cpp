#include "Motorcycle.h"

Motorcycle::Motorcycle()
{
	speed = 0;
	status = IDLE;
}

Motorcycle::Motorcycle(int ID, double Speed, STATUS Status, ORD_TYPE Type)
{
	SetID(ID);
	SetSpeed(Speed);
	SetStatus(Status);
	SetType(Type);
	Changepriority(0); //zero is the time of construction of the motorcycles
}

////////////////////////////////////////////////////////////////////////////////////////////////
//																							  //
//									setters and getters										  //
//																							  //	
////////////////////////////////////////////////////////////////////////////////////////////////

int Motorcycle::GetID()const
{
	return ID;
}

double Motorcycle::GetSpeed()const
{
	return speed;
}

STATUS Motorcycle::GetStatus()const
{
	return status;
}
ORD_TYPE Motorcycle::GetType()const
{
	return type;
}
void Motorcycle::SetID(int I)
{
	ID = I > 0 ? I : 0;
}

void Motorcycle::SetSpeed(double S)
{
	speed = S > 0 ? S : 0;
}

void Motorcycle::SetStatus(STATUS St)
{
	status = (St == IDLE || St == SERV) ? St : IDLE;
}

void Motorcycle::SetType(ORD_TYPE T)
{
	type = (T > -1 && T < TYPE_CNT) ? T : TYPE_NRM;
}

void Motorcycle:: SetAssignedOrd(Order*O)
{
	AssignedOrd=O;
}

void Motorcycle:: SetRegion(REGION R)
{
	region=R;
}

REGION Motorcycle:: GetRegion()const
{
	return region;
}	
Order* Motorcycle:: GetAssignedOrd() const
{
	return AssignedOrd;
}
int  Motorcycle:: GetArrivalTime() const
{
	return ArrivalTime;
}
////////////////////////////////////////////////////////////////////////////////////////////////
//																							  //
//							overloads to check the priority									  //
//																							  //	
////////////////////////////////////////////////////////////////////////////////////////////////

bool Motorcycle:: operator < (Motorcycle M)
{
	if(priority < M.priority)
		return true;
	return false;
}

bool Motorcycle:: operator >(Motorcycle M)
{
	if(priority > M.priority)
		return true;
	return false;
}

bool Motorcycle:: operator ==(Motorcycle M)
{
	if(ID == M.ID)
		return true;
	return false;
}

////////////////////////////////////////////////////////////////////////////////////////////////
//																							  //
//			    changes the priority of the motorcycle after the assignment to be put		  //
//				in the assigned PQ with the time at which it returns is the priority	      //
//																							  //	
////////////////////////////////////////////////////////////////////////////////////////////////

void Motorcycle::Changepriority(int timestp)
{
	if(status == IDLE)
		priority = speed;
	else
		priority = timestp + 2 * (AssignedOrd->GetDistance() / speed); 
}


Motorcycle::~Motorcycle()
{

}

