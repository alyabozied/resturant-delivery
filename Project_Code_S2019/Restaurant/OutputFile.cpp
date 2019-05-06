#include "OutputFile.h"

OutputFile::OutputFile(Restaurant* R, GUI*& G):pRest(R), pGUI(G)
{
	for (int i = 0; i < REG_CNT; i++)
	{
		RegionServ[i] = 0;
		RegionWait[i] = 0;
	}
	RestServ = RestWait = 0;
	OpenFileOut();
	FileOutput<<"FT\tID\tAT\tWT\tST\n";
}


void OutputFile::OpenFileOut()
{
	string temp [4] = {"","","",""};
	pGUI->PrintMessage("Enter file name to save the output","","","",temp,"");
	FileName = pGUI->GetString();
	FileName = FileName + ".txt";
	FileOutput.open("../Simulation Results/"+FileName);
}


OutputFile::~OutputFile()
{
	FileOutput.close();
}


void OutputFile::Write(Order* O)
{
	//modified later to output in a file
	FileOutput << O->GetFinishTime() << "\t" << O->GetID() << "\t" << O->GetArrTime() << "\t";
	FileOutput << O->GetWaitingTime() << "\t" << O->GetServTime() << "\n";
	RegionWait[O->GetRegion()] += O->GetWaitingTime();
	RegionServ[O->GetRegion()] += O->GetServTime();
	RestWait += O->GetWaitingTime();
	RestServ += O->GetServTime();
}

void OutputFile::PrintStatstics()
{
	int totalnorders = 0;
	int totalforders = 0;
	int totalvorders = 0;
	int totalnmotors = 0;
	int totalfmotors = 0;
	int totalvmotors = 0;

	char reg = 'A';
	FileOutput << endl << endl << endl;
	for (int i = 0; i < REG_CNT; i++)
	{
		FileOutput <<"........................................................\n";
		FileOutput <<"........................................................\n";
		FileOutput<<"Region "<< reg++ <<":\n";
		Region *R = pRest->GetRegion(i);
		int NO = R->GetWholeNOrdCount();
		int FO = R->GetWholeFOrdCount();
		int VO = R->GetWholeVOrdCount();
		int NM = R->Get_NMotorCnt();
		int FM = R->Get_FMotorCnt();
		int VM = R->Get_VMotorCnt();
		FileOutput << "\tOrders: " << NO+FO+VO << " [Norm: " << NO;
		FileOutput << ", Froz: " << FO << ", VIP: " << VO << "]\n";
		FileOutput << "\tMotorC: " << NM+FM+VM << " [Norm: " << NM;
		FileOutput << ", Froz: " << FM << ", VIP: " << VM << "]\n";
		if (NO+FO+VO != 0)
		{
			RegionWait[i] /= NO+FO+VO;
			RegionServ[i] /= NO+FO+VO;
		}
		else
			RegionWait[i]  = RegionServ[i] = 0;

		FileOutput<< "\tAverage Wait = " << RegionWait[i] << ",\t Avg Serv = "<< RegionServ[i] << "\n\n";
		totalnorders +=  NO;
		totalforders +=  FO;
		totalvorders +=  VO;
		totalnmotors += NM;
		totalfmotors += FM;
		totalvmotors += VM;
	}
	if(totalnorders + totalforders + totalvorders != 0)
	{
		RestServ /= totalnorders + totalforders + totalvorders;
		RestWait /= totalnorders + totalforders + totalvorders;
	}
	else
		RestServ = RestWait = 0;
	
	FileOutput <<"........................................................\n";
	FileOutput <<"........................................................\n";
	FileOutput <<"Whole Restaurant:\n";
	FileOutput << "\tOrders: " << totalnorders + totalforders + totalvorders << " [Norm: " << totalnorders;
	FileOutput << ", Froz: " << totalforders << ", VIP: " << totalvorders << "]\n";
	FileOutput << "\tMotorC: " << totalnmotors + totalfmotors + totalvmotors << " [Norm: " << totalnmotors;
	FileOutput << ", Froz: " << totalfmotors << ", VIP: " << totalvmotors << "]\n";
	FileOutput<< "\tAverage Wait = " << RestWait << ",\t Avg Serv = "<< RestServ << "\n\n";

}


