#pragma once
#include"Generic_DS\priorityQueue.h"
#include"Rest\Motorcycle.h"
#include"Rest\Order.h"
#include"Generic_DS\Queue.h"
#include"Generic_DS\List.h"

class Region
{
protected:
	//List of Motocylyes REgion
	priorityQueue<Motorcycle*>idelFMotorQ;
	priorityQueue<Motorcycle*>idelNMotorQ;
	priorityQueue<Motorcycle*>idelVMotorQ;
	priorityQueue<Motorcycle*>servMotorQ;	// A queue for serving motorcycles
	priorityQueue<Motorcycle*>Damaged;		// A queue for damaged motorcycles
	
	int wholeNorders,wholeForders,wholeVoreders;
	//Number of MotorCycle in Region
	int N_MotorsCnt,V_MotorsCnt,F_MotorsCnt;
	//Order in Region
	LinkedList<Order*>NOrderQueue;
	priorityQueue<Order*>VOrderQueue;
	Queue<Order*>FOrderQueue;
	Queue<Order*>DeletedOrderQueue;
	//whole number of orders of different types 
	int NOrderCount, FOrderCount, VOrderCount;
public:
	Region(void);
	void InsertFMotor(int, double, STATUS, ORD_TYPE, REGION);	//function to insert frozen motorcycle
	void InsertVMotor(int, double, STATUS, ORD_TYPE, REGION);	//function to insert fast motorcycle
	void InsertNMotor(int, double, STATUS, ORD_TYPE, REGION);   //function to insert normal motorcycle
	void InsertFOrder(Order*);							//a Functions to insert Frozen orders
	void InsertVOrder(Order*);						    //a funtion to inset VIP orders 
	void InsertNOrder(Order*);							//a function to insert normal orders 
	int Get_NMotorCnt()const;							//function to get the number of normal motors
	int Get_VMotorCnt()const;							//function to get the number of fast motors
	int Get_FMotorCnt()const;							//function to get the number of frozen motors
	int GetWholeNOrdCount()const;						//will be used at the end of the program to be written in the file
	int GetWholeVOrdCount()const;						//will be used at the end of the program to be written in the file
	int GetWholeFOrdCount()const;						//will be used at the end of the program to be written in the file

	// Getters for the number of orders currently(at the time step) in the restaurant 
	int GetVOrdCnt();
	int GetNOrdCnt();
	int GetFOrdCnt();
	bool FOrdisEmpty();
	//function to increase counters for each type of orders
	void inccounter(char c);
	// Functions used to dequeue the orders
	Order* GetNOrder(int );
	Order* dequeueV();
	Order* dequeueF();
	void DeleteMotors();
	Order*const* GetArrNOrd();
	Order*const* GetArrVOrd();
	Order*const* GetArrFOrd();
	
	// Moves the recovered motorcycles from the damaged queue to the idle list
	void recovered(int);    

	//Assign orders to motorcycle
	bool AssignOrdNMotor(int,int ,int, priorityQueue<Order*>*);
	bool AssignOrdFMotor(int,int ,int, priorityQueue<Order*>*);
	bool AssignOrdVMotor(int,int ,int, priorityQueue<Order*>*);
	//unassign motorcylces
	bool UnAssignMotors(int);
	//auto promotion function
	void Promote(int, int);
	~Region(void);
};

