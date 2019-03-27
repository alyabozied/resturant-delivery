#include "Region.h"


Region::Region(void)
{
	
	N_Motors = V_Motors = F_Motors = 0;
}

void Region::FillMotors(int NMotors, int VMotors, int FMotors, Motorcycle **NM , Motorcycle **VM, Motorcycle **FM)
{
	//insert Normal Motorcycles to its list from Unorders array to an Ordered Piriorty list and set the Number of the MotorCycles
	for (int i = 0; i < NMotors; i++)
	{
		NMotorQueue.insert(NM[i]);
	}

	N_Motors=NMotors;

	//insert VIP Motorcycles to its list from Unorders array to an Ordered Piriorty list 

	for (int i = 0; i < VMotors; i++)
	{
		VMotorQueue.insert(VM[i]);
	}

	V_Motors=VMotors;

	//insert Frozen Motorcycles to its list from Unorders array to an Ordered Piriorty list 

	for (int i = 0; i < FMotors; i++)
	{
		FMotorQueue.insert(FM[i]);
	}

	F_Motors=FMotors;

}


//insert a Frozen Order to the list 
void Region::InsertFOrder(Order* F)
{
	FOrderQueue.enqueue(F);
}

//insert a Vip order to the list
void Region::InsertNOrder(Order* N)
{
	NOrderQueue.insert(N);
}

//insert a Normal order to the list
void Region::InsertVOrder(Order* V)
{
	VOrderQueue.insert(V);
}


int Region::getVcount(){ return VOrderQueue.getcount(); }

int Region::getNcount(){ return NOrderQueue.getcount(); }

bool Region::Fisempty(){ return FOrderQueue.isEmpty();}


Order* Region::dequeueN() 
{ 
	Order* ord = NOrderQueue.extractMax();
	return ord; 
}

Order* Region::dequeueV() 
{ 
	Order* ord = VOrderQueue.extractMax();
	return ord; 
}

Order* Region::dequeueF()
{ 
	Order *ord ;
	FOrderQueue.dequeue(ord);
	return  ord;
}
void Region::DeleteMotors()
{
	while (NMotorQueue.getcount() != 0)
	{
		delete NMotorQueue.extractMax();
	}
	while (VMotorQueue.getcount() != 0)
	{
		delete VMotorQueue.extractMax();
	}
	while (FMotorQueue.getcount() != 0)
	{
		delete FMotorQueue.extractMax();
	}
}






Region::~Region(void)
{
}
