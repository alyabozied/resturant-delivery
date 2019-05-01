#include "Motorcycle.h"

Motorcycle::Motorcycle()
{
	speed = 0;
	status = IDLE;
	damagedT = -1; 
	tiredT = -1;
}

Motorcycle::Motorcycle(int ID, double Speed, STATUS Status, ORD_TYPE Type, REGION r)
{
	SetID(ID);
	SetSpeed(Speed);
	SetStatus(Status);
	SetType(Type);
	SetRegion(r);
	Changepriority(0); //zero is the time of construction of the motorcycles
	damagedT = -1; 
	tiredT = -1;
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

void Motorcycle:: SetAssignedOrd(Order*O,int timestep, int timed, int timeT)
{
	AssignedOrd=O;
	status=SERV;
	ordtype = O->GetType();
	Changepriority(timestep);
	O->AssignMotor(this,timestep,timed,timeT);
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

int Motorcycle::getdamagedT() const 
{
	return damagedT;
}

int Motorcycle::gettiredT() const 
{
	return tiredT;
}

ORD_TYPE Motorcycle::getordtype() const
{
	return ordtype;
}

///////////////////////////////////////////////////////////////////////////////////////////////
//																							 //
//								Motorcycle state functions									 //
//																							 //
///////////////////////////////////////////////////////////////////////////////////////////////

void Motorcycle::SetDamaged(int d)  // sets the time the motors stays damaged 
{
	damagedT = d;
}

void Motorcycle::SetTired(int t)     // sets the time the motor stays tired
{
	tiredT = t;
}

bool Motorcycle::Isdamaged(int d)	// checks if the motor is damaged
{
	if(damagedT > d ) 
		return true;
	return false;
}

bool Motorcycle::Istired(int t)     // checks if the motor is tired
{
	if(tiredT > t) 
		return true;
	return false;
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
		priority = -1*(timestp + 2 * (AssignedOrd->GetDistance() / speed)); 
}


bool Motorcycle::IsBack(int timestep)const
{
	return timestep == -priority ;
}



Motorcycle::~Motorcycle()
{

}

