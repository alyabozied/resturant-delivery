#ifndef __ARRIVAL_EVENT_H_
#define __ARRIVAL_EVENT_H_

#include "Event.h"


//class for the arrival event
class ArrivalEvent: public Event
{
	double OrdDistance;  	//order distance
	ORD_TYPE OrdType;		//order type: Normal, Frozen, VIP
	REGION OrdRegion;       //Region of this order	                
	double OrdMoney;	    //Total order money
	bool hard;
public:
	ArrivalEvent(int eTime, int oID, ORD_TYPE oType, REGION reg);
	ArrivalEvent(int eTime, int oID, ORD_TYPE oType, REGION reg, double dist, double mon, bool);
	virtual void Execute(Restaurant *pRest);	//override execute function

};

#endif