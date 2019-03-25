#pragma once

#include "Event.h"


//class for the cancelation event
class CancelationEvent: public Event
{

public:
	CancelationEvent(int eTime, int oID);
	
	virtual void Execute(Restaurant *pRest);	//override execute function

};

