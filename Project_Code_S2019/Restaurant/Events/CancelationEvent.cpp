#include "CancelationEvent.h"
#include "..\Rest\Restaurant.h"


CancelationEvent::CancelationEvent(int eTime, int oID):Event(eTime, oID)
{
	
}


void CancelationEvent::Execute(Restaurant* pRest)
{
	//This function should delete an order from the normal orders queue
		
	Order* tmp=new Order(this->getOrderID());
	int index;
	for (int i = 0; i < 4; i++)
	{
		index =pRest->GetRegion(i)->Sreach(tmp);
		if(index!=-1)
		{
			delete tmp;
			tmp= nullptr;
			tmp = pRest->GetRegion(i)->dequeueN(index);
			delete tmp;
			tmp = nullptr;
			return;	
		}
		
	}
	
	
}
	


