#include "InputFile.h"

InputFile::InputFile(Restaurant* R, GUI* G):pRest(R), pGUI(G)
{

}

InputFile::~InputFile()
{

}


bool InputFile::Read()
{
	pGUI->PrintMessage("Enter the file name: ");
	FileName = pGUI->GetString();
	FileInput.open(FileName + ".txt");
	if(!FileInput.is_open())
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
	int	TimeStp, ID;
	double MON = 0, EXMON = 0, DST;
	char  EVNT, TYP, REG;
	Order* pOrd = nullptr;
	Event* pEv = nullptr;
	
	FileInput >> SpeedN >> SpeedF >> SpeedV;

	for (int i = 0; i < REG_CNT; i++)
	{
		Region* R = pRest->GetRegion(i);
		FileInput >> Norm >> Frzn >> VIP;
		//creating normal motorcycles
		for (int j = 0; j < Norm; j++)
		{
			R->InsertNMotor(j, SpeedN, IDLE, TYPE_NRM);
		}
		//creating frozen motorcycles 
		for (int k = 0; k < Frzn; k++)
		{
			R->InsertFMotor(k+Norm, SpeedF, IDLE, TYPE_FROZ);
		}
		//creating VIP motocycles
		for (int l = 0; l < VIP; l++)
		{
			R->InsertVMotor(Norm+TYPE_FROZ+l, SpeedV, IDLE, TYPE_VIP);
		}
	}
	

	FileInput >> AutoS;
	FileInput >> NumEvnts;
	
	pRest->SetAutoProm(AutoS);
	//reads the different types of events
	while (!FileInput.eof())
	{
		// reads the first character in the line to know the type of the event to take the convinient action
		FileInput >> EVNT;
		if(toupper(EVNT) == 'R')
		{
			FileInput >> TimeStp >> TYP >> ID >> DST >> MON >> REG;
			
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
			FileInput >> TimeStp >> ID;
			pEv = new CancelationEvent(TimeStp, ID);
			pRest->AddEvent(pEv);

		}
		else if(toupper(EVNT) == 'P')
		{
			FileInput >> TimeStp >> ID >> EXMON;
			pEv = new PromotionEvent(TimeStp, ID, EXMON);
			pRest->AddEvent(pEv);
		}
		else 
		{
			pGUI->PrintMessage("wrong file format");
			return false;
		}

	}
	FileInput.close();
	return true;
}


