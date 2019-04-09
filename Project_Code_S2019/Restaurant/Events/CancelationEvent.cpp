#include "CancelationEvent.h"
#include "..\Rest\Restaurant.h"


CancelationEvent::CancelationEvent(int eTime, int oID):Event(eTime, oID)
{
	
}


void CancelationEvent::Execute(Restaurant* pRest)
{
	//This function should delete an order from the normal orders queue
		


	std::vector<Order*>tmpvec;
	for (int i = 0; i < 4; i++)
	{
		tmpvec=pRest->GetRegion(i)->getVectorNord();

		for (int j = 0; j < int(tmpvec.size()); j++)
		{

			if(tmpvec[j]->GetID() == getOrderID())
			{
			delete pRest->GetRegion(i)->dequeueN(j+1);	
			return ;
			}

		}
		
		
	}
	
	
}
	


