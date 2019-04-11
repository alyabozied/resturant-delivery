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
				tmp=pRest->GetRegion(i)->dequeueN(j+1);	
				tmp->SetType(TYPE_VIP);
				pRest->GetRegion(i)->InsertVOrder(tmp);
				return ;
			}

		}
	}
}		
		

