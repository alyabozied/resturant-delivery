#include "InOutFile.h"

InOutFile::InOutFile(Restaurant* R, GUI* G):pRest(R), pGUI(G)
{

}

InOutFile::~InOutFile()
{

}

bool InOutFile::Write()
{
	//modified later to output in a file
	return false;
}

bool InOutFile::Read()
{
	pGUI->PrintMessage("Enter the file name: ");
	FileName = pGUI->GetString();
	InputFile.open(FileName + ".txt");
	if(!InputFile.is_open())
	{
		pGUI->PrintMessage("an error occured loading the file there may not exist a file with this name");
		return false; 
	}
	//speed of differnet types of motors
	int SpeedN, SpeedF, SpeedV;
	// number of different types of motors
	int	Norm, Frzn, VIP;
	//time of auto promotion and number of events
	int	AutoS, NumEvnts;
	// the timestep,ID, Distance of different orders
	int	TimeStp, ID, DST;
	double MON = 0, EXMON = 0;
	char  EVNT, TYP, REG;
	Order* pOrd = nullptr;
	Event* pEv = nullptr;
	
	InputFile >> SpeedN >> SpeedF >> SpeedV;
	//array of motors to store them
	Motorcycle**NMotors, **FMotors, **VMotors; 
	for (int i = 0; i < REG_CNT; i++)
	{
		InputFile >> Norm >> Frzn >> VIP;
			NMotors = new Motorcycle*[Norm];
			FMotors = new Motorcycle*[Frzn];
			VMotors = new Motorcycle*[VIP];
		//creating normal motorcycles
		for (int j = 0; j < Norm; j++)
		{
			NMotors[j] = new Motorcycle(j, SpeedN, IDLE, TYPE_NRM);
		}
		//creating frozen motorcycles 
		for (int k = 0; k < Frzn; k++)
		{
			FMotors[k]=new Motorcycle(k+Norm, SpeedF, IDLE, TYPE_FROZ);
		}
		//creating VIP motocycles
		for (int l = 0; l < VIP; l++)
		{
			VMotors[l]=new Motorcycle(Norm+TYPE_FROZ+l, SpeedV, IDLE, TYPE_VIP);
		}
		//setting the motorcycles for the specified region
		pRest->GetRegion(i)->FillMotors(Norm,VIP,Frzn,NMotors,VMotors,FMotors);
		delete []NMotors;
		delete []FMotors;
		delete []VMotors;
	}
	

	InputFile >> AutoS;
	InputFile >> NumEvnts;
	
	pRest->SetAutoProm(AutoS);
	//reads the different types of events
	while (!InputFile.eof())
	{
		// reads the first character in the line to know the type of the event to take the convinient action
		InputFile >> EVNT;
		if(toupper(EVNT) == 'R')
		{
			InputFile >> TimeStp >> TYP >> ID >> DST >> MON >> REG;
			
			// modifies the entered data for ordertype to be of desired datatype
			if(toupper(TYP) == 'N')
				TYP = TYPE_NRM;
			if(toupper(TYP) == 'V')
				TYP = TYPE_VIP;
			if(toupper(TYP) == 'F')
				TYP = TYPE_FROZ;
			
			// modifies the entered data for region to be of desired datatype
			REG = toupper(REG) - 'A';

			if(REG >= 0 && REG <= 3)
			{
				pEv = new ArrivalEvent(TimeStp, ID,(ORD_TYPE) TYP, (REGION)REG, DST, MON);
				pRest->AddEvent(pEv);
			}

		}
		else if(toupper(EVNT) == 'X')
		{
			InputFile >> TimeStp >> ID;
			pEv = new CancelationEvent(TimeStp, ID);
			pRest->AddEvent(pEv);

		}
		else if(toupper(EVNT) == 'P')
		{
			InputFile >> TimeStp >> ID >> EXMON;
			pEv = new PromotionEvent(TimeStp, ID, EXMON);
			pRest->AddEvent(pEv);
		}
		else 
		{
			pGUI->PrintMessage("wrong file format");
			return false;
		}

	}
	return true;
}


