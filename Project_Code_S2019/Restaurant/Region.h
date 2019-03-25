#pragma once
#include"Generic_DS\PriorityQueue.h"
#include"Rest\Motorcycle.h"
#include"Rest\Order.h"
#include"Generic_DS\Queue.h"
class Region
{
protected:
	//List of Motocylyes REgion
	priorityQueue<Motorcycle*>FMotorQueue;
	priorityQueue<Motorcycle*>NMotorQueue;
	priorityQueue<Motorcycle*>VMotorQueue;

	//Number of MotorCycle in Region
	int N_Motors,V_Motors,F_Motors;

	//Order in Region
	priorityQueue<Order*>NOrderQueue;
	priorityQueue<Order*>VOrderQueue;
	Queue<Order*>FOrderQueue;
public:
	Region(void);
	//Function to Fill the Number of MotorCycles and the Lists of the MotorCycles by taking the Number and take 
	//an array of Pointers to each Type (Pirority Doesn't matter in this array because the Fill will handle it) 
	void FillMotors(int ,int , int, Motorcycle**, Motorcycle**, Motorcycle** );
	void InsertFOrder(Order*); //a Functions to insert Frozen orders
	void InsertVOrder(Order*); // a funtion to inset VIP orders 
	void InsertNOrder(Order*);  // a function to insert normal orders 

	// Getters for the counters
	int getVcount();
	int getNcount();
	bool Fisempty();

	// Functions used to dequeue the orders
	Order* dequeueN();
	Order* dequeueV();
	Order* dequeueF();


	~Region(void);
};

