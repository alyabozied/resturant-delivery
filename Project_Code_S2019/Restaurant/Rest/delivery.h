#ifndef __delivery_H_
#define __delivery_H_


#include "..\Defs.h"
#include "Order.h"
class Order;
#pragma once
class delivery	
{
	int ID;
	ORD_TYPE type;	    //for each order type there is a corresponding delivery type 
	double speed;		//meters it can move in one clock tick (in one timestep)
	REGION	region;	    //region of the delivery
	STATUS	status;	    //idle or in-service
	Order* AssignedOrd;	//to hold the assigned order untill it is delivered then the order info can be printed,
	int ArrivalTime;	//will be used for priority, when will the delivery arrive 
	int priority;
public:
	delivery();
	delivery(int ID, double Speed, STATUS Status, ORD_TYPE Type, REGION);
	
	//Setters and Getters for All Date Members
	
	int GetID()const;
	ORD_TYPE GetType()const;
	double GetSpeed()const;
	REGION GetRegion()const;
	STATUS GetStatus()const;
	Order* GetAssignedOrd()const;
	int GetArrivalTime()const;
	void SetID(int);
	void SetType(ORD_TYPE);
	void SetSpeed(double);
	void SetRegion(REGION);
	void SetStatus(STATUS);
	void SetAssignedOrd(Order*, int,int,int);

	//function to check if the motor cycle returned
	bool IsBack(int)const;
	//overloads for the priority checking
	bool operator <(delivery M);
	bool operator >(delivery M);
	bool operator ==(delivery M);
	
	void Changepriority(int timestp);    //the priority changes if the motor is idle or serving

	virtual ~delivery();
};

#endif