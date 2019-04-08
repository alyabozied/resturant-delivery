#include "PromotionEvent.h"
#include "..\Rest\Restaurant.h"


PromotionEvent::PromotionEvent(int eTime, int oID, double Exmon):Event(eTime, oID)
{
	ExtraMon = Exmon > 0 ? Exmon :0;
}


void PromotionEvent::Execute(Restaurant* pRest)
{
	//This function should delete an order from the normal orders queue increase the totalmoney of the order
	//then add it to the vip queue
	Order*tmp;
	std::vector<Order*>tmpvec;
	for (int i = 0; i < 4; i++)
	{
		tmpvec=pRest->GetRegion(i)->getVectorNord();
		for (int j = 0; j < int(tmpvec.size()); j++)
		{
			if(tmpvec[j]->GetID() == getOrderID())
			{
			tmp=pRest->GetRegion(i)->dequeueN(j+1);	
			tmp->SetType(TYPE_VIP);
			pRest->GetRegion(i)->InsertVOrder(tmp);
			return ;
			}

		}
	}
}		
		

