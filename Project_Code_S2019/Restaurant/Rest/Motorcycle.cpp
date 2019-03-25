#include "Motorcycle.h"


Motorcycle::Motorcycle()
{
	speed =0;
	
}


int Motorcycle::GetID()const
{
	return ID;
}

int Motorcycle::GetSpeed()const
{
	return speed;
}

int Motorcycle::GetStatues()const
{
	return status;
}
int Motorcycle::GetType()const
{
	return type;
}
void Motorcycle::SetID(int I)
{
	if(I<0)
		return;
	ID=I;
}

void Motorcycle::SetSpeed(int S)
{
	if(S<0)
		return;
	speed=S;
}

void Motorcycle::SetStatus(int St)
{
	if(St<0)
		return;
	status=(STATUS)St;
}

void Motorcycle::SetType(int T)
{
	if(T<0)
		return;
	type=(ORD_TYPE)T;
}



Motorcycle::~Motorcycle()
{
}
bool Motorcycle:: operator <(Motorcycle M){
	if(speed<M.speed)
		return true;
	return false;
}

bool Motorcycle:: operator >(Motorcycle M){
	if(speed>M.speed)
		return true;
	return false;
}

bool Motorcycle:: operator ==(Motorcycle M){
	if(ID==M.ID)
		return true;
	return false;
}

	