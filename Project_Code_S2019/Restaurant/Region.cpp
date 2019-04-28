#include "Region.h"


Region::Region(void)
{
	
	N_MotorsCnt = V_MotorsCnt = F_MotorsCnt = Neardelivery = NOrderCount = VOrderCount = FOrderCount = wholePoreders = wholeNearoreders = wholeNorders = wholeForders = wholeVoreders=  POrderCount = NearOrderCount = 0;
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

void Region::Insertrdelivery(int id, double speed, STATUS s, ORD_TYPE t, REGION r)
{
	delivery* D = new delivery (id, speed, s, t, r);
	Neardelivery++;
	idealdelivery.insert(D);
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

void Region::InsertNearOrder(Order* Near)
{
	NearOrderCount++;
	NearOrderQueue.enqueue(Near);
}
void Region::InsertPOrder(Order* P)
{
	POrderCount++;
	POrderQueue.insert(P); 
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
int Region::GetPOrdCnt(){ return POrderQueue.getcount();}
int Region::GetNearOrdCnt(){ return NearOrderQueue.Get_count();}
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

Order* const* Region::GetArrNearOrd()
{
	return NearOrderQueue.ToArray();
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

Order* Region::dequeueP() 
{ 
	Order* ord = POrderQueue.extractMax();
	POrderCount--;
	return ord; 
}

Order* Region::dequeueNear() 
{ 
	Order* ord; 
	NearOrderQueue.dequeue(ord);
	NearOrderCount--;
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


void Region::DeleteMotorsAndDelivery()
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
	delivery *tmp ;
	while (serdelivery.getcount())
	{
		delete serdelivery.extractMax();
	}
	
	while (idealdelivery.extractMax())
	{
		delete idealdelivery.extractMax();
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////
//																							  //
//				functions to return the whole number of different orders					  //
//																							  //	
////////////////////////////////////////////////////////////////////////////////////////////////

int Region::GetWholeFOrdCount() const{ return wholeForders; }
int Region::GetWholeNOrdCount() const{ return wholeNorders; }
int Region::GetWholeVOrdCount() const{ return wholeVoreders; }
int Region::GetWholePOrdCount() const{ return wholePoreders; }
int Region::GetWholeNearOrdCount() const{ return wholeNearoreders; }
///////////////////////////////////////////////////////////////////////////////////////////////
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


int Region::Get_NearMotorCnt()const
{
	return Neardelivery;
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
	while(NOrderCount != 0 && N_MotorsCnt != 0)
	{
		NMotor = idelNMotorQ.extractMax();
		NOrderQueue.remove(1,tmp);
		NMotor->SetAssignedOrd(tmp,timestep,timed,timeT);
		servMotorQ.insert(NMotor);
		serv->insert(tmp);
		N_MotorsCnt--;
		NOrderCount--;
	}
		
	while(NOrderCount != 0 && V_MotorsCnt != 0 && VOrderCount == 0)
	{
		VMotor = idelVMotorQ.extractMax();
		NOrderQueue.remove(1,tmp);
		VMotor->SetAssignedOrd(tmp,timestep,timed,timeT);
		servMotorQ.insert(VMotor);
		serv->insert(tmp);
		V_MotorsCnt--;
		NOrderCount--;
	}
		
	return NOrderCount == 0  ;

}

void Region::recovered(int timestep)
{
	Motorcycle* temp;
	while(Damaged.getcount() !=0)
	{
		temp = Damaged.extractMax();
		if(temp->getdamagedT() == timestep)
		{
			temp->SetDamaged(0);
			temp->Changepriority(timestep);
			if(temp->GetType() == TYPE_NRM)
			{
				wholeNorders++;
				idelNMotorQ.insert(temp);
				N_MotorsCnt++;
			}
			else
				if(temp->GetType() ==TYPE_FROZ)
				{
					wholeForders++;
					idelFMotorQ.insert(temp);
					F_MotorsCnt++;
				}
			else	
			{
				wholeVoreders++;
				idelVMotorQ.insert(temp);
				V_MotorsCnt++;
			}

		}
		else
			Damaged.insert(temp);
		return ;
	}
	
}

bool Region::UnAssignMotors(int timestep)
{
	delivery *tmpD =  nullptr;
	Motorcycle * tmpM =nullptr;
	if(servMotorQ.getcount())
		while (servMotorQ.getcount() && servMotorQ.getmax()->IsBack(timestep))
		{
			tmpM = servMotorQ.extractMax();
			tmpM->SetStatus(IDLE);
			tmpM->Changepriority(timestep);
		

			if(tmpM->Isdamaged(timestep))
			{
				Damaged.insert(tmpM);
			}
			else
			{				
				if(tmpM->GetType() == TYPE_NRM)
				{
					wholeNorders++;
					idelNMotorQ.insert(tmpM);
					N_MotorsCnt++;				
				}
				else
					if(tmpM->GetType() ==TYPE_FROZ)
					{
						wholeForders++;
						idelFMotorQ.insert(tmpM);
						F_MotorsCnt++;
					}
					else 
				{
					if(tmpM->GetAssignedOrd()->GetType() == TYPE_VIP)
					wholeVoreders++;
					idelVMotorQ.insert(tmpM);
					V_MotorsCnt++;	
				}
			}
		}
		tmpD = serdelivery.getmax();
		if(serdelivery.getcount() && tmpD->IsBack(timestep) )
		{
			tmpD=serdelivery.extractMax();
			tmpD->SetStatus(IDLE);
			tmpD->Changepriority(timestep);
			wholeNearoreders++;
			idealdelivery.insert(tmpD);
			Neardelivery++;

		}

		return servMotorQ.getcount() ||serdelivery.getcount();
}




bool Region::AssignOrdFMotor(int timestep , int timed , int timeT, priorityQueue<Order*>* serv)
{
	Order*tmp = nullptr;
	Motorcycle*FMotor = nullptr;
	while(FOrderCount != 0 && F_MotorsCnt != 0)
	{
		FMotor = idelFMotorQ.extractMax();
		FOrderQueue.dequeue(tmp);
		FMotor->SetAssignedOrd(tmp,timestep,timed,timeT);
		servMotorQ.insert(FMotor);
		serv->insert(tmp);
		F_MotorsCnt--;
		FOrderCount--;
	}
	
		return FOrderCount == 0 ;

}



bool Region::AssignOrdNeardelivery(int timestep , int timed , int timeT, priorityQueue<Order*>* serv)
{
	Order*tmp = nullptr;
	delivery * tmpd = nullptr;
	while(NearOrderCount != 0 && idealdelivery.getcount() != 0)
	{
		tmpd = idealdelivery.extractMax();
		NearOrderQueue.dequeue(tmp);
		tmpd->SetAssignedOrd(tmp,timestep,timed,timeT);
		serdelivery.insert(tmpd);
		serv->insert(tmp);
		Neardelivery--;
		NearOrderCount--;
	}
	
		return NearOrderCount == 0 ;

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
		tmp = VOrderQueue.extractMax();
		VMotor->SetAssignedOrd(tmp,timestep,timed,timeT);
		servMotorQ.insert(VMotor);
		serv->insert(tmp);
		V_MotorsCnt--;
		VOrderCount--;
	}

	while(VOrderCount != 0 && N_MotorsCnt != 0)
	{
		NMotor = idelNMotorQ.extractMax();
		tmp = VOrderQueue.extractMax();
		NMotor->SetAssignedOrd(tmp,timestep,timed,timeT);
		servMotorQ.insert(NMotor);
		serv->insert(tmp);
		N_MotorsCnt--;
		VOrderCount--;
	}

	while(VOrderCount != 0 && F_MotorsCnt != 0)
	{
		FMotor = idelFMotorQ.extractMax();
		tmp = VOrderQueue.extractMax();
		FMotor->SetAssignedOrd(tmp,timestep,timed,timeT);
		servMotorQ.insert(FMotor);
		serv->insert(tmp);
		F_MotorsCnt--;
		VOrderCount--;
	}

	return VOrderCount == 0 ;
}


bool Region::AssignOrdPMotor(int timestep , int timed , int timeT, priorityQueue<Order*>* serv)
{
	Order*tmp = nullptr;
	Motorcycle*VMotor = nullptr;
	Motorcycle*NMotor = nullptr;
	Motorcycle*FMotor = nullptr;
	Queue<Motorcycle*> temp ;
	int AssignedMotortoserv = 3;
	int tempv =0 , tempn =0 , tempf =0 , tempcount =0 ;
	if(V_MotorsCnt >= 3  )
	{
		tempn = 0;
		tempf = 0;
		if(V_MotorsCnt == 3 )
		{
		tempv = V_MotorsCnt;
		}
		else
			tempv =3;
	
	}
	else if(V_MotorsCnt + N_MotorsCnt >=3 )
	{
		tempf = 0;
		tempv = V_MotorsCnt;
		while (tempv+tempn < 3 )
		{
			tempn++;
		}
	}
	else if(V_MotorsCnt + N_MotorsCnt + F_MotorsCnt >= 3 )
	{
		tempn = N_MotorsCnt;
		tempv = V_MotorsCnt;
		while (tempv+tempn+tempf < 3 )
		{
			tempf++;
		}

	}

	while(POrderCount != 0 && V_MotorsCnt != 0 && AssignedMotortoserv != 0 && tempv != 0 )
	{
		if(tempcount == 0)
		tmp = POrderQueue.extractMax();
		for (int i = 0; i < tempv; i++)
		{
		VMotor = idelVMotorQ.extractMax();
		VMotor->SetAssignedOrd(tmp,timestep,timed,timeT);
		if(tempcount == 0)
		serv->insert(tmp);
		servMotorQ.insert(VMotor);
		V_MotorsCnt--;
		tempcount++;
		if(tempcount == 3)
		{
		POrderCount--;
		wholePoreders++;
		tempcount =0;
		}

		}
			
	}

	while(POrderCount != 0 && N_MotorsCnt != 0 && AssignedMotortoserv != 0 &&  tempn != 0)
	{
		if(tempcount == 0)
		tmp = POrderQueue.extractMax();
		for (int i = 0; i < tempn; i++)
		{
		NMotor = idelNMotorQ.extractMax();
		NMotor->SetAssignedOrd(tmp,timestep,timed,timeT);
		if(tempcount == 0 )
		serv->insert(tmp);
		servMotorQ.insert(NMotor);
		N_MotorsCnt--;
		tempcount++;
		
		
		if(tempcount == 3)
		{
		POrderCount--;
		wholePoreders++;
		tempcount =0;
		}
		}

	}
	while(POrderCount != 0 && F_MotorsCnt != 0 && AssignedMotortoserv != 0 &&  tempf != 0)
	{
		if(tempcount == 0)
		tmp = POrderQueue.extractMax();
		for (int i = 0; i < tempf; i++)
		{
		FMotor = idelFMotorQ.extractMax();
		FMotor->SetAssignedOrd(tmp,timestep,timed,timeT);
		if(tempcount == 0)
		serv->insert(tmp);
		servMotorQ.insert(FMotor);
		F_MotorsCnt--;
		tempcount++;
		if(tempcount == 3)
		{
		POrderCount--;
		wholePoreders++;
		tempcount =0;
		}
	}
	}
	return POrderCount == 0 ;
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
	DeleteMotorsAndDelivery();
	while (!DeletedOrderQueue.isEmpty())
	{
		 DeletedOrderQueue.enqueue(tmp);
		 delete tmp;
	}
}
