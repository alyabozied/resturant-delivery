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
		idelNMotorQ.insert(NM[i]);
	}

	N_Motors=NMotors;

	//insert VIP Motorcycles to its list from Unorders array to an Ordered Piriorty list 

	for (int i = 0; i < VMotors; i++)
	{
		idelVMotorQ.insert(VM[i]);
	}

	V_Motors=VMotors;

	//insert Frozen Motorcycles to its list from Unorders array to an Ordered Piriorty list 

	for (int i = 0; i < FMotors; i++)
	{
		idelFMotorQ.insert(FM[i]);
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
	NOrderQueue.insert(NOrderQueue.getLength()+1,N);
}

//insert a Normal order to the list
void Region::InsertVOrder(Order* V)
{
	VOrderQueue.insert(V);
}


int Region::getVcount(){ return VOrderQueue.getcount(); }

int Region::getNcount(){ return NOrderQueue.getLength(); }

bool Region::Fisempty(){ return FOrderQueue.isEmpty();}


Order* Region::dequeueN(int postion) 
{ 
	Order* ord ;
	NOrderQueue.remove(postion,ord);
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
	while (idelNMotorQ.getcount() != 0)
	{
		delete idelNMotorQ.extractMax();
	}
	while (idelVMotorQ.getcount() != 0)
	{
		delete idelVMotorQ.extractMax();
	}
	while (idelFMotorQ.getcount() != 0)
	{
		delete idelFMotorQ.extractMax();
	}
}


int Region::Get_FMotorC()const
{
	return F_Motors;
}



int Region::Get_NMotorC()const
{
	return N_Motors;
}



int Region::Get_VMotorC()const
{
	return V_Motors;
}

int Region::getFcount()
{
	return FOrderQueue.Get_count();
}
std::vector<Order*> Region::getVectorNord()
{
	return NOrderQueue.ToVector();
}




Region::~Region(void)
{
}
