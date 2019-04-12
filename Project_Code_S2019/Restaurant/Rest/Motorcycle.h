#ifndef __MOTORCYCLE_H_
#define __MOTORCYCLE_H_


#include "..\Defs.h"
#include "Order.h"
class Order;
#pragma once
class Motorcycle	
{
	int ID;
	ORD_TYPE type;	    //for each order type there is a corresponding motorcycle type 
	double speed;		//meters it can move in one clock tick (in one timestep)
	REGION	region;	    //region of the motorcycle
	STATUS	status;	    //idle or in-service
	Order* AssignedOrd;	//to hold the assigned order untill it is delivered then the order info can be printed,
						//also implicitly has the service time of the motorcycle by dividing the distance over speed
	int ArrivalTime;	//will be used for priority, when will the motorcycle arrive 
	int priority;

public:
	Motorcycle();
	Motorcycle(int ID, double Speed, STATUS Status, ORD_TYPE Type);
	
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
	void SetAssignedOrd(Order*);

	
	//overloads for the priority checking
	bool operator <(Motorcycle M);
	bool operator >(Motorcycle M);
	bool operator ==(Motorcycle M);
	

	//the priority changes if the motor is idle or serving
	void ChangePriority(int timestp);

	virtual ~Motorcycle();
};

#endif