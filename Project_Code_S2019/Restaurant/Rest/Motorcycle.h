#ifndef __MOTORCYCLE_H_
#define __MOTORCYCLE_H_


#include "..\Defs.h"

#pragma once
class Motorcycle	
{
	int ID;
	ORD_TYPE type;	    //for each order type there is a corresponding motorcycle type 
	double speed;		//meters it can move in one clock tick (in one timestep)
	REGION	region;	    //region of the motorcycle
	STATUS	status;	    //idle or in-service
	int ArrivalTime;	//will be used for priority
public:
	Motorcycle();
	Motorcycle(int ID, double Speed, STATUS Status, ORD_TYPE Type);
	
	//Setters and Getters for All Date Members

	int GetID()const;
	double GetSpeed()const;
	ORD_TYPE GetType()const;
	STATUS GetStatus()const;

	void SetID(int);
	void SetSpeed(double);
	void SetType(ORD_TYPE);
	void SetStatus(STATUS);
	
	//overloads for the priority checking
	bool operator <(Motorcycle M);
	bool operator >(Motorcycle M);
	bool operator ==(Motorcycle M);
	
	virtual ~Motorcycle();
};

#endif