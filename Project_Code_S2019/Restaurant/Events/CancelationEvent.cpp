#include "CancelationEvent.h"
#include "..\Rest\Restaurant.h"


CancelationEvent::CancelationEvent(int eTime, int oID):Event(eTime, oID)
{
	
}


void CancelationEvent::Execute(Restaurant* pRest)
{
	//This function should delete an order from the normal orders queue
	
	Queue<Order*>tmpQ;
	Order* tmp;
	bool flag =false;
	char tempnum[4];
	for (int i = 0; i < 4; i++)
	{



		while(pRest->GetRegion(i)->getNcount())
		{
		tmp=pRest->GetRegion(i)->dequeueN();
		
		if(tmp->GetID() == getOrderID())
			{
				//pRest->pGUI->PrintMessage("Order with ID : "+string(itoa(getOrderID(),tempnum,4))+"has cancled has order " );
				delete tmp;
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
