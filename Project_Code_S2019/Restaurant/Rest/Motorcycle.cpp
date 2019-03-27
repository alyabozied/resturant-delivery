#include "Motorcycle.h"

Motorcycle::Motorcycle()
{
	speed = 0;
	status = IDLE;
}

Motorcycle::Motorcycle(int ID, double Speed, STATUS Status, ORD_TYPE Type)
{
	SetID(ID);
	SetSpeed(Speed);
	SetStatus(Status);
	SetType(Type);
}


int Motorcycle::GetID()const
{
	return ID;
}

double Motorcycle::GetSpeed()const
{
	return speed;
}

STATUS Motorcycle::GetStatus()const
{
	return status;
}
ORD_TYPE Motorcycle::GetType()const
{
	return type;
}
void Motorcycle::SetID(int I)
{
	ID = I > 0 ? I : 0;
}

void Motorcycle::SetSpeed(double S)
{
	speed = S > 0 ? S : 0;
}

void Motorcycle::SetStatus(STATUS St)
{
	status = (St == IDLE || St == SERV) ? St : IDLE;
}

void Motorcycle::SetType(ORD_TYPE T)
{
	type = (T >-1 && T < TYPE_CNT) ? T : TYPE_NRM;
}



Motorcycle::~Motorcycle()
{

}
bool Motorcycle:: operator <(Motorcycle M)
{
	if(speed < M.speed)
		return true;
	return false;
}

bool Motorcycle:: operator >(Motorcycle M)
{
	if(speed > M.speed)
		return true;
	return false;
}

bool Motorcycle:: operator ==(Motorcycle M)
{
	if(ID == M.ID)
		return true;
	return false;
}

	