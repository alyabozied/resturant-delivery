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
	Queue<Order*>tmpQ;
	Order* tmp;
	bool flag =false;

	for (int i = 0; i < 4; i++)
	{

		while(pRest->GetRegion(i)->getNcount())
		{
		tmp=pRest->GetRegion(i)->dequeueN();
		
		if(tmp->GetID() == getOrderID())
			{
				tmp->SetType(TYPE_VIP);
				pRest->GetRegion(i)->InsertVOrder(tmp);
				tmp=nullptr;
				flag=true;
				break;
		}
		else
			tmpQ.enqueue(tmp);

		}
		while (!tmpQ.isEmpty())
		{
			tmpQ.dequeue(tmp);
			pRest->GetRegion(i)->InsertNOrder(tmp);
		}
		if(flag)
		return ; 
	}



}
