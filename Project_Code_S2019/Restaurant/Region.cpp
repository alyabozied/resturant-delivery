#include "Region.h"


Region::Region(void)
{
	
	N_MotorsCnt = V_MotorsCnt = F_MotorsCnt = NOrderCount = VOrderCount = FOrderCount =wholeNorders=wholeForders=wholeVoreders= 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////
//																							  //
//					functions to insert different types motorcycles							  //
//					        	 read from the input file									  //
//																							  //	
////////////////////////////////////////////////////////////////////////////////////////////////

void Region::InsertFMotor(int id, double speed, STATUS s, ORD_TYPE t, REGION r)
{
	Motorcycle* M = new Motorcycle (id, speed, s, t, r);
	F_MotorsCnt++;
	idelFMotorQ.insert(M);
}

void Region::InsertNMotor(int id, double speed, STATUS s, ORD_TYPE t, REGION r)
{
	Motorcycle* M = new Motorcycle (id, speed, s, t, r);
	N_MotorsCnt++;
	idelNMotorQ.insert(M);
}

void Region::InsertVMotor(int id, double speed, STATUS s, ORD_TYPE t, REGION r)
{
	Motorcycle* M = new Motorcycle (id, speed, s, t, r);
	V_MotorsCnt++;
	idelVMotorQ.insert(M);
}



////////////////////////////////////////////////////////////////////////////////////////////////
//																							  //
//					functions to insert different types orders								  //
//					         in the convinient list											  //
//																							  //	
////////////////////////////////////////////////////////////////////////////////////////////////


void Region::InsertFOrder(Order* F)
{
	FOrderCount++;
	FOrderQueue.enqueue(F);
}
void Region::InsertNOrder(Order* N)
{
	NOrderCount++;
	NOrderQueue.insert(NOrderQueue.getLength()+1,N);
}
void Region::InsertVOrder(Order* V)
{
	VOrderCount++;
	VOrderQueue.insert(V); 
}


////////////////////////////////////////////////////////////////////////////////////////////////
//																							  //
//					functions to get the number of not served								  //
//							orders of different types									      //
//																							  //	
////////////////////////////////////////////////////////////////////////////////////////////////


int Region::GetVOrdCnt(){ return VOrderQueue.getcount(); }
int Region::GetNOrdCnt(){ return NOrderQueue.getLength();}
int Region::GetFOrdCnt(){ return FOrderQueue.Get_count();}
bool Region::FOrdisEmpty(){ return FOrderQueue.isEmpty();}


////////////////////////////////////////////////////////////////////////////////////////////////
//																							  //
//					functions to return an array of the different							  //
//							      types of orders										      //
//																							  //	
////////////////////////////////////////////////////////////////////////////////////////////////



Order* const* Region::GetArrVOrd()
{
	return VOrderQueue.ToArray();
}

Order* const* Region::GetArrFOrd()
{
	return FOrderQueue.ToArray();
}

Order*const* Region::GetArrNOrd()
{
	return NOrderQueue.ToArray();
}

////////////////////////////////////////////////////////////////////////////////////////////////
//																							  //
//					functions to delete the convinient order								  //
//																							  //	
////////////////////////////////////////////////////////////////////////////////////////////////


Order* Region::GetNOrder(int postion) 
{ 
	Order* ord ;
	NOrderQueue.remove(postion,ord);
	NOrderCount--;
	return ord; 
}

Order* Region::dequeueV() 
{ 
	Order* ord = VOrderQueue.extractMax();
	VOrderCount--;
	return ord; 
}

Order* Region::dequeueF()
{ 
	Order *ord ;
	FOrderQueue.dequeue(ord);
	FOrderCount--;
	return  ord;
}

////////////////////////////////////////////////////////////////////////////////////////////////
//																							  //
//					functions to deallocate the motocycles									  //
//																							  //	
////////////////////////////////////////////////////////////////////////////////////////////////


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
	while (servFMotorQ.getcount() != 0)
	{
		delete  servFMotorQ.extractMax();
	}
	while (servNMotorQ.getcount() != 0)
	{
		delete servNMotorQ.extractMax();		
	}
	while (servVMotorQ.getcount() != 0)
	{
		delete servVMotorQ.extractMax();
	}

}

////////////////////////////////////////////////////////////////////////////////////////////////
//																							  //
//				functions to return the whole number of different orders					  //
//																							  //	
////////////////////////////////////////////////////////////////////////////////////////////////

int Region::GetWholeFOrdCount() const{ return wholeForders; }
int Region::GetWholeNOrdCount() const{ return 	wholeNorders; }
int Region::GetWholeVOrdCount() const{ return wholeVoreders; }

////////////////////////////////////////////////////////////////////////////////////////////////
//																							  //
//					functions to return the number of the motorcycles						  //
//																							  //	
////////////////////////////////////////////////////////////////////////////////////////////////


int Region::Get_FMotorCnt()const
{
	return F_MotorsCnt;
}


int Region::Get_NMotorCnt()const
{
	return N_MotorsCnt;
}


int Region::Get_VMotorCnt()const
{
	return V_MotorsCnt;
}



////////////////////////////////////////////////////////////////////////////////////////////////
//																							  //
//					functions to Assign an order to motorcylce      						  //
//																							  //	
////////////////////////////////////////////////////////////////////////////////////////////////

bool Region::AssignOrdNMotor(int timestep , int timed , int timeT, priorityQueue<Order*>* serv)
{
	Order*tmp = nullptr;
	Motorcycle*NMotor = nullptr;
	Motorcycle*VMotor = nullptr;
	Queue<Motorcycle*> temp;
	while(NOrderCount != 0 && N_MotorsCnt != 0)
	{
		NMotor = idelNMotorQ.extractMax();
		if(NMotor->Isdamaged(timestep))
		{
			temp.enqueue(NMotor); N_MotorsCnt--; continue;
		}
		NOrderQueue.remove(1,tmp);
		NMotor->SetAssignedOrd(tmp,timestep,timed,timeT);
		tmp->AssignMotor(NMotor, timestep, timed , timeT);
		servNMotorQ.insert(NMotor);
		serv->insert(tmp);
		N_MotorsCnt--;
		NOrderCount--;
	}
	while(!temp.isEmpty())
	{
		temp.dequeue(NMotor);
		idelNMotorQ.insert(NMotor);
		N_MotorsCnt++;
	}
		
	while(NOrderCount != 0 && V_MotorsCnt != 0 && VOrderCount == 0)
	{
		VMotor = idelVMotorQ.extractMax();
		if(VMotor->Isdamaged(timestep))
		{
			temp.enqueue(VMotor);
			V_MotorsCnt--;
			continue;
		}
		NOrderQueue.remove(1,tmp);
		VMotor->SetAssignedOrd(tmp,timestep,timed,timeT);
		tmp->AssignMotor(VMotor, timestep,timed, timeT);
		servVMotorQ.insert(VMotor);
		serv->insert(tmp);
		V_MotorsCnt--;
		NOrderCount--;
	}
	while(!temp.isEmpty())
	{
		temp.dequeue(VMotor);
		idelVMotorQ.insert(VMotor);
		V_MotorsCnt++;
	}
		
	return NOrderCount == 0  ;

}

bool Region::UnAssignMotors(int timestep)
{

	Motorcycle * tmpM =nullptr;
	if(servVMotorQ.getcount())
		while (servVMotorQ.getcount() && servVMotorQ.getmax()->IsBack(timestep))
		{
			wholeForders++;
			tmpM = servVMotorQ.extractMax();
			tmpM->SetStatus(IDLE);
			tmpM->Changepriority(timestep);
			idelVMotorQ.insert(tmpM);
			V_MotorsCnt++;
			
		}

		
	if(servNMotorQ.getcount())
		while (servNMotorQ.getcount() && servNMotorQ.getmax()->IsBack(timestep))
		{
			wholeNorders++;
			tmpM = servNMotorQ.extractMax();
			tmpM->SetStatus(IDLE);
			tmpM->Changepriority(timestep);
			idelNMotorQ.insert(tmpM);
			N_MotorsCnt++;

		}

		
	if(servFMotorQ.getcount())
		while (servFMotorQ.getcount() && servFMotorQ.getmax()->IsBack(timestep))
		{
			wholeVoreders++;
			tmpM = servFMotorQ.extractMax();
			tmpM->SetStatus(IDLE);
			tmpM->Changepriority(timestep);		
			idelFMotorQ.insert(tmpM);
			F_MotorsCnt++;
		}


		return servFMotorQ.getcount() || servNMotorQ.getcount() || servVMotorQ.getcount();
}




bool Region::AssignOrdFMotor(int timestep , int timed , int timeT, priorityQueue<Order*>* serv)
{
	Order*tmp = nullptr;
	Motorcycle*FMotor = nullptr;
	Queue<Motorcycle*> temp;
	while(FOrderCount != 0 && F_MotorsCnt != 0)
	{
		FMotor = idelFMotorQ.extractMax();
		if(FMotor->Isdamaged(timestep))
		{
			temp.enqueue(FMotor); F_MotorsCnt--; continue;
		}
		FOrderQueue.dequeue(tmp);
		FMotor->SetAssignedOrd(tmp,timestep,timed,timeT);
		tmp->AssignMotor(FMotor, timestep,timed,timeT);
		servFMotorQ.insert(FMotor);
		serv->insert(tmp);
		F_MotorsCnt--;
		FOrderCount--;
	}
	while(!temp.isEmpty())
	{
		temp.dequeue(FMotor);
		idelFMotorQ.insert(FMotor);
		F_MotorsCnt++;
	}
		return FOrderCount == 0 ;

}



bool Region::AssignOrdVMotor(int timestep , int timed , int timeT, priorityQueue<Order*>* serv)
{
	Order*tmp = nullptr;
	Motorcycle*VMotor = nullptr;
	Motorcycle*NMotor = nullptr;
	Motorcycle*FMotor = nullptr;
	Queue<Motorcycle*> temp ;
	while(VOrderCount != 0 && V_MotorsCnt != 0)
	{
		VMotor = idelVMotorQ.extractMax();
		if(VMotor->Isdamaged(timestep)) { temp.enqueue(VMotor); V_MotorsCnt--;continue;}
		tmp = VOrderQueue.extractMax();
		VMotor->SetAssignedOrd(tmp,timestep,timed,timeT);
		tmp->AssignMotor(VMotor, timestep,timed,timeT);
		servVMotorQ.insert(VMotor);
		serv->insert(tmp);
		V_MotorsCnt--;
		VOrderCount--;
	}
	while (!temp.isEmpty())
	{
	temp.dequeue(VMotor);
	idelVMotorQ.insert(VMotor);
	V_MotorsCnt++;
	}

	while(VOrderCount != 0 && N_MotorsCnt != 0)
	{
		NMotor = idelNMotorQ.extractMax();
		if(NMotor->Isdamaged(timestep)){ temp.enqueue(NMotor); N_MotorsCnt--; continue;}
		tmp = VOrderQueue.extractMax();
		NMotor->SetAssignedOrd(tmp,timestep,timed,timeT);
		tmp->AssignMotor(NMotor, timestep,timed,timeT);
		servNMotorQ.insert(NMotor);
		serv->insert(tmp);
		N_MotorsCnt--;
		VOrderCount--;
	}
	while(!temp.isEmpty())
	{
		temp.dequeue(NMotor);
		idelNMotorQ.insert(NMotor);
		N_MotorsCnt++;	
	}
	while(VOrderCount != 0 && F_MotorsCnt != 0)
	{
		FMotor = idelFMotorQ.extractMax();
		if(FMotor->Isdamaged(timestep)) { temp.enqueue(FMotor); F_MotorsCnt--; continue;}
		tmp = VOrderQueue.extractMax();
		FMotor->SetAssignedOrd(tmp,timestep,timed,timeT);
		tmp->AssignMotor(FMotor, timestep,timed,timeT);
		servFMotorQ.insert(FMotor);
		serv->insert(tmp);
		F_MotorsCnt--;
		VOrderCount--;
	}
	while(!temp.isEmpty())
	{
		temp.dequeue(FMotor);
		idelFMotorQ.insert(FMotor);
		F_MotorsCnt++;
	}
		return VOrderCount == 0 ;
}



void Region::Promote(int autop , int timestep)
{
	Order*const*Arrytmp =NOrderQueue.ToArray();
	Order *tmp=nullptr;
	int counter =NOrderCount;
	for (int i = 0; i < counter; i++)
	{
		if((timestep-Arrytmp[i]->GetArrTime())>=autop)
		{
			Order* VIP = new Order(Arrytmp[i]->GetArrTime() ,Arrytmp[i]->GetID(), TYPE_VIP, Arrytmp[i]->GetRegion(), Arrytmp[i]->GetDistance(), Arrytmp[i]->GetMoney());
			NOrderQueue.remove(1,tmp);
			delete tmp;
			InsertVOrder(VIP);
			NOrderCount--;
		}
		else 
			break;
	}
	delete [] Arrytmp;

}


Region::~Region(void)
{
	Order*tmp;
	DeleteMotors();
	while (!DeletedOrderQueue.isEmpty())
	{
		 DeletedOrderQueue.enqueue(tmp);
		 delete tmp;
	}
}
