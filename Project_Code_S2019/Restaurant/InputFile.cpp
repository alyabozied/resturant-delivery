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
	FileName = FileName + ".txt";
	FileInput.open("../Samples/"+FileName);
	if(!FileInput.is_open())
	{
		pGUI->PrintMessage("an error occured loading the file there may not exist a file with this name");
		return false; 
	}
	//speed of differnet types of motors
	int Speed;
	// number of different types of motors
	int	Norm[REG_CNT], Frzn[REG_CNT], VIP[REG_CNT],DEl[REG_CNT];
	//time of auto promotion and number of events
	int	AutoS, NumEvnts,
		timeT,timeD;  // The time a motor takes to recover when it is tired and when it is damaged
	
	// the timestep,ID, Distance of different orders
	int	TimeStp, ID;
	double MON = 0, EXMON = 0, DST;
	char  EVNT, TYP, REG,COM;   // COM if a char to detect the complexity of the order (Hard or easy)
	Order* pOrd = nullptr;
	Event* pEv = nullptr;
	
	for (int i = 0; i < REG_CNT; i++)
	{
		FileInput >> Norm[i] >> Frzn[i] >> VIP[i] >> DEl[i];
	}
	for (int i = 0; i < REG_CNT; i++)
	{
		Region* R = pRest->GetRegion(i);
		char MotoReg, MotoType;
		char DELReg, DELType;
		int MotoID;
		int DELID;
		//creating normal motorcycles
		for (int j = 0; j < Norm[i]; j++)
		{
			FileInput >> MotoReg >> MotoType >> MotoID >> Speed; 
			R->InsertNMotor(MotoID, Speed, IDLE, TYPE_NRM,(REGION)(MotoReg - 'A'));
		}
		//creating frozen motorcycles 
		for (int k = 0; k < Frzn[i]; k++)
		{
			FileInput >> MotoReg >> MotoType >> MotoID >> Speed; 
			R->InsertFMotor(MotoID, Speed, IDLE, TYPE_FROZ,(REGION)(MotoReg - 'A'));
		}
		//creating VIP motocycles
		for (int l = 0; l < VIP[i]; l++)
		{

			FileInput >> MotoReg >> MotoType >> MotoID >> Speed; 
			R->InsertVMotor(MotoID, Speed, IDLE, TYPE_VIP,(REGION)(MotoReg - 'A'));
		}
		//creating delivery 
		for (int N = 0; N < DEl[i]; N++)
		{

			FileInput >> DELReg >> DELType >> DELID >> Speed; 
			R->Insertrdelivery(DELID, Speed, IDLE, TYPE_NEAR,(REGION)(DELReg - 'A'));
		}

	}
	

	FileInput >> NumEvnts;
	FileInput >> AutoS;
	FileInput >> timeT;
	FileInput >> timeD;
	pRest->SetAutoProm(AutoS);
	pRest->SetTimeDam(timeD);
	pRest->SetTimeTir(timeT);
	//reads the different types of events
	while (!FileInput.eof())
	{
		// reads the first character in the line to know the type of the event to take the convinient action
		FileInput >> EVNT;
		if(toupper(EVNT) == 'R')
		{
			FileInput >> TimeStp >> TYP >> ID >> DST >> MON >> REG >>COM ;
			
			// modifies the entered data for ordertype to be of desired datatype
			if(toupper(TYP) == 'N')
				TYP = TYPE_NRM;
			if(toupper(TYP) == 'V')
				TYP = TYPE_VIP;
			if(toupper(TYP) == 'F')
				TYP = TYPE_FROZ;
			if(toupper(TYP) == 'Y')
				TYP = TYPE_PARTY;	
				if(toupper(TYP) == 'L')
				TYP = TYPE_NEAR;
			// modifies the entered data for region to be of desired datatype
			REG = toupper(REG) - 'A';
			if(toupper(COM) == 'H')
				COM = 1;
			else 
				COM = 0;

			if(REG >= 0 && REG <= 3)
			{
				pEv = new ArrivalEvent(TimeStp, ID,(ORD_TYPE) TYP, (REGION)REG, DST, MON,(bool)COM);
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


