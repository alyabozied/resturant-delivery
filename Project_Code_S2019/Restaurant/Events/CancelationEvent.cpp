#include "CancelationEvent.h"
#include "..\Rest\Restaurant.h"


CancelationEvent::CancelationEvent(int eTime, int oID):Event(eTime, oID)
{
	
}


void CancelationEvent::Execute(Restaurant* pRest)
{
	//This function should delete an order from the normal orders queue
		
	Order* const* TmpArr;
	for (int i = 0; i < REG_CNT; i++)
	{
		TmpArr = pRest->GetRegion(i)->GetArrNOrd();
		int Cnt = pRest->GetRegion(i)->GetNOrdCnt();

		for (int j = 0; j < Cnt; j++)
		{
			if(TmpArr[j]->GetID() == getOrderID())
			{
				delete pRest->GetRegion(i)->GetNOrder(j+1);	
				delete  []TmpArr;
				return ;
			}
		}
		delete []TmpArr; 
	}

}
	


