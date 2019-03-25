#ifndef __MOTORCYCLE_H_
#define __MOTORCYCLE_H_


#include "..\Defs.h"

#pragma once
class Motorcycle	
{
	int ID;
	ORD_TYPE type;	//for each order type there is a corresponding motorcycle type 
	int speed;		//meters it can move in one clock tick (in one timestep)
	REGION	region;	//region of the motorcycle
	STATUS	status;	//idle or in-service
	int ArrivalTime;
public:
	Motorcycle();
	//Setters and Getters for All Date Members
	int GetStatues()const;
	void SetStatus(int);

	int GetID()const;
	void SetID(int);

	int GetSpeed()const;
	void SetSpeed(int);

	int GetType()const;
	void SetType(int);
	bool operator <(Motorcycle M);
	bool operator >(Motorcycle M);
	bool operator ==(Motorcycle M);
	
	virtual ~Motorcycle();
};

#endif