#include "Order.h"

Order::Order(int id, ORD_TYPE r_Type, REGION r_region, int dist, double mon)
{
	ID = (id>0&&id<1000)?id:0;	//1<ID<999
	type = r_Type;
	Region = r_region;
	Distance = dist;
	totalMoney = mon;
	if(r_Type == TYPE_VIP)
	priorty = 4*mon - ArrTime  - 2*dist;
	else  
		priorty= - ArrTime;
	
}
Order::Order(int id)
{
	if(id<0||id>1000)
		ID=0;
	ID=id;
}

void Order::SetType(ORD_TYPE oType)
{
	type=oType;
}

Order::~Order()
{
}

int Order::GetID()
{
	return ID;
}


int Order::GetType() const
{
	return type;
}

REGION Order::GetRegion() const
{
	return Region;
}

void Order::SetDistance(int d)
{
	Distance = d>0?d:0;
}

int Order::GetDistance() const
{
	return Distance;
}
bool Order:: operator <(Order &v){
	if(priorty<v.priorty)
		return true;
	else return false;
}

bool Order:: operator >(Order &v){
	if(priorty>v.priorty)
		return true;
	else return false;
}

bool Order:: operator ==(Order& v){
	if(v.ID==ID)
		return true;
	return false;
}

