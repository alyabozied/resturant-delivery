#include "PromotionEvent.h"
#include "..\Rest\Restaurant.h"


PromotionEvent::PromotionEvent(int eTime, int oID, double Exmon):Event(eTime, oID)
{
	ExtraMon = Exmon > 0 ? Exmon : 100;
}


void PromotionEvent::Execute(Restaurant* pRest)
{
	//This function should delete an order from the normal orders queue increase the totalmoney of the order
	//then add it to the vip queue

	Order *tmp;
	Order *const*TmpArr;
	for (int i = 0; i < 4; i++)
	{
		TmpArr = pRest->GetRegion(i)->GetArrNOrd();
		int Cnt = pRest->GetRegion(i)->GetNOrdCnt();

		for (int j = 0; j < Cnt; j++)
		{
			if(TmpArr[j]->GetID() == getOrderID())
			{
				tmp=pRest->GetRegion(i)->GetNOrder(j+1);	
				Order* VIP = new Order(tmp->GetArrTime() ,tmp->GetID(), TYPE_VIP, tmp->GetRegion(), tmp->GetDistance(), tmp->GetMoney());
				pRest->GetRegion(i)->InsertVOrder(VIP);
				delete tmp;
				delete []TmpArr;
				return ;
			}

		}
		delete []TmpArr;
	}
}		
		

