#ifndef __ORDER_H_
#define __ORDER_H_

#include "..\Defs.h"
#include "Motorcycle.h"
class Motorcycle;
class Order
{

protected:
	int ID;                     //Each order has a unique ID (from 1 --> 999 )
	ORD_TYPE type;	            //order type: Normal, Frozen, VIP
	REGION Region;              //Region of this order
	double Distance;	        //The distance (in meters) between the order location and the resturant 
	double totalMoney;	        //Total order money
	int ArrTime, ServTime, FinishTime, WaitingTime;	    //arrival, service start, finish, and waiting times
	double priority;
	Motorcycle* AssignedMotor; //to calculate the serving and finish time
	
	
public:
	Order(int Arrivaltime ,int ID, ORD_TYPE r_Type, REGION r_region, double dist, double mon);
	Order(int);
	virtual ~Order();

	//setters and getters
	
	int GetID() const;
	REGION GetRegion() const;
	ORD_TYPE GetType() const;
	double GetDistance() const;
	double GetMoney() const;
	int GetArrTime() const;
	int GetServTime() const;
	int GetFinishTime() const;
	int GetWaitingTime() const;
	double Getpriority() const;
	Motorcycle* GetMotor() const;

	void SetID(int);
	void SetRegion(REGION);
	void SetType(ORD_TYPE);
	void SetDistance(double);
	void SetMoney(double);
	void SetArrTime(int);
	void SetServTime(int);
	void SetFinishTime(int);
	void SetWaitingTime(int);


	//overloads for checking the priority

	bool operator <(Order &v);
	bool operator >(Order& v);
	bool operator ==(Order& v);
	
	void Changepriority(int timestp);
	void AssignMotor(Motorcycle*);

};

#endif