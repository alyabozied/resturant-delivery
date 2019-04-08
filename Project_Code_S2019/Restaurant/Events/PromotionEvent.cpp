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
	Order* tmp=new Order(getOrderID());
	int index;
	for (int i = 0; i < 4; i++)
	{
		index =pRest->GetRegion(i)->Sreach(tmp);
		
		if(index!=-1)
		{
			delete tmp;
			tmp=nullptr;
			tmp=pRest->GetRegion(i)->dequeueN(index);
			tmp->SetType(TYPE_VIP);
			pRest->GetRegion(i)->InsertVOrder(tmp);
			return;
		
		}
	
	}
	

}
		
		

