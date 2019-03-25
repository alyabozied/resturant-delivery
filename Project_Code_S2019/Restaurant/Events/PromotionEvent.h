#pragma once

#include "Event.h"


//class for the promotion event
class PromotionEvent: public Event
{
	double ExtraMon;
public:
	PromotionEvent(int eTime, int oID, double Exmon);
	
	virtual void Execute(Restaurant *pRest);	//override execute function

};

