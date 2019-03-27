#ifndef __MOTORCYCLE_H_
#define __MOTORCYCLE_H_


#include "..\Defs.h"

#pragma once
class Motorcycle	
{
	int ID;
	ORD_TYPE type;	//for each order type there is a corresponding motorcycle type 
	double speed;		//meters it can move in one clock tick (in one timestep)
	REGION	region;	//region of the motorcycle
	STATUS	status;	//idle or in-service
	int ArrivalTime;
public:
	Motorcycle();
	Motorcycle(int ID, double Speed, STATUS Status, ORD_TYPE Type);
	//Setters and Getters for All Date Members
	STATUS GetStatus()const;
	void SetStatus(STATUS);

	int GetID()const;
	void SetID(int);

	double GetSpeed()const;
	void SetSpeed(double);

	ORD_TYPE GetType()const;
	void SetType(ORD_TYPE);
	bool operator <(Motorcycle M);
	bool operator >(Motorcycle M);
	bool operator ==(Motorcycle M);
	
	virtual ~Motorcycle();
};

#endif