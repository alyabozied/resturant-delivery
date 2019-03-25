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
	

}
