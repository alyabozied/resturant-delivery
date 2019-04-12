#include "Order.h"

Order::Order(int arrt,int id, ORD_TYPE r_Type, REGION r_region, double dist, double mon)
{
	SetArrTime(arrt);
	SetID(id);
	SetType(r_Type);
	SetRegion(r_region);
	SetDistance(dist);
	SetMoney(mon);
	AssignedMotor = nullptr;
	if(r_Type == TYPE_VIP)
		priority = 4 * mon -15* ArrTime  - 2 * dist;
	else  
		priority= - ArrTime;
	;
}

Order::Order(int id)
{
	if(id<0||id>1000)
		ID=0;
	ID=id;
}
////////////////////////////////////////////////////////////////////////////////////////////////
//																							  //
//									setters and getters										  //
//																							  //	
////////////////////////////////////////////////////////////////////////////////////////////////

int Order::GetID() const { return ID; }
ORD_TYPE Order::GetType() const { return type; }
REGION Order::GetRegion() const { return Region; }
double Order::GetDistance() const { return Distance; }
double Order::GetMoney() const { return totalMoney; }
int Order::GetArrTime() const {return ArrTime;}
int Order::GetFinishTime() const {return FinishTime; }
int Order::GetServTime() const { return ServTime; }
int Order::GetWaitingTime() const { return WaitingTime; }
double Order::Getpriority() const { return priority; }
Motorcycle* Order::GetMotor() const { return AssignedMotor; }



void Order::SetID(int id) { ID = (id >= 0 && id < 1000) ? id : 0; }
void Order::SetType(ORD_TYPE oType){ type = (oType >= 0 && oType < 4) ? oType : TYPE_NRM; }
void Order::SetRegion(REGION R){ Region = (R >= A_REG && R < REG_CNT) ? R : A_REG; }
void Order::SetDistance(double d){ Distance = (d > 0) ? d : 100; }
void Order::SetMoney(double m){ totalMoney = (m > 0) ? m : 0; }
void Order::SetArrTime(int t){ ArrTime = (t > 0) ? t : 0; }
void Order::SetFinishTime(int t){ FinishTime = (t > 0) ? t : 0; }
void Order::SetServTime(int t){ ServTime = (t > 0) ? t : 0; }
void Order::SetWaitingTime(int t){ WaitingTime = (t > 0) ? t : 0; }


////////////////////////////////////////////////////////////////////////////////////////////////
//																							  //
//								overloads for priority checks								  //
//																							  //	
////////////////////////////////////////////////////////////////////////////////////////////////

bool Order:: operator <(Order &v)
{
	if(priority<v.priority)
		return true;
	else return false;
}

bool Order:: operator >(Order &v)
{
	if(priority>v.priority)
		return true;
	else return false;
}

bool Order:: operator ==(Order& v)
{
	if(v.ID==ID)
		return true;
	return false;
}

////////////////////////////////////////////////////////////////////////////////////////////////
//																							  //
//			    	changes the priority of the order after the assignment to be 			  //
//					  put in the assigned PQ with the finish time as priority				  //	
//																							  //	
////////////////////////////////////////////////////////////////////////////////////////////////

void Order::Changepriority(int Currtimestp)
{
	SetWaitingTime(Currtimestp - ArrTime);
	SetFinishTime(ArrTime + ServTime + WaitingTime);
	priority = FinishTime;
}


//function to assign a motorcycle for the order
void Order::AssignMotor(Motorcycle* m, int timestp)
{
	AssignedMotor = m; 
	SetServTime(Distance / m->GetSpeed());
	Changepriority(timestp);
}
Order::~Order()
{
}