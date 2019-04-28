#ifndef __DELIVERY_H_
#define __DELIVERY_H_
#include "..\Defs.h"
#include "Order.h"
class Order;
class delivery
{
	int ID;
	ORD_TYPE type;	    //for each order type there is a corresponding motorcycle type 
	REGION	region;	    //region of the motorcycle
	STATUS	status;	    //idle or in-service
	Order* AssignedOrd;	//to hold the assigned order untill it is delivered then the order info can be printed,						//also implicitly has the service time of the motorcycle by dividing the distance over speed
	double speed;
	int ArrivalTime;	//will be used for priority, when will the motorcycle arrive 
	int Backtime;
public:
	delivery(void);
	delivery::delivery(int , double , STATUS , ORD_TYPE , REGION );
	//Setters and Getters for All Date Members
	
	int GetID()const;
	ORD_TYPE GetType()const;
	double GetSpeed()const;
	REGION GetRegion()const;
	STATUS GetStatus()const;
	Order* GetAssignedOrd()const;
	int GetArrivalTime()const;
	void SetID(int);
	void SetBacktime(int );
	void SetType(ORD_TYPE);
	void SetSpeed(double);
	void SetRegion(REGION);
	void SetStatus(STATUS);
	void SetAssignedOrd(Order*, int,int,int);
	bool operator ==(delivery );
	bool IsBack(int)const;
	~delivery(void);
};

#endif
