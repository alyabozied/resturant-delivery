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
	pGUI->PrintMessage("Enter file name to save the output");
	FileName = pGUI->GetString();
	FileName = FileName + ".txt";
	FileOutput.open("../Restaurant/Simulation Results/"+FileName);
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
	int totalporders = 0;
	int totalnearorders = 0;
	int totalnmotors = 0;
	int totalfmotors = 0;
	int totalvmotors = 0;
	int totaldelivery = 0;

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
		int PO = R->GetWholePOrdCount();
		int NEO = R->GetWholeNearOrdCount();
		int NM = R->Get_NMotorCnt();
		int FM = R->Get_FMotorCnt();
		int VM = R->Get_VMotorCnt();
		int D = R->Get_NearMotorCnt();
		FileOutput << "\tOrders: " << NO+FO+VO+PO+NEO << " [Norm: " << NO;
		FileOutput << ", Froz: " << FO << ", VIP: " << VO << ", PARTY: " << PO << ", NEAR: " << NEO <<  "]\n";
		FileOutput << "\tMotorC: " << NM+FM+VM << " [Norm: " << NM;
		FileOutput << ", Froz: " << FM << ", VIP: " << VM << "]\n";
		FileOutput << "\tDeliveryC: " << D <<"\n";
		if((NO+FO+VO+PO+NEO)!= 0)
		{
		RegionWait[i] /= NO+FO+VO+PO+NEO;
		RegionServ[i] /= NO+FO+VO+PO+NEO;
		}
		else
		{
		RegionWait[i] = NO+FO+VO+PO+NEO;
		RegionServ[i] = NO+FO+VO+PO+NEO;
		}
		FileOutput<< "\tAverage Wait = " << RegionWait[i] << ",\t Avg Serv = "<< RegionServ[i] << "\n\n";
		totalnorders +=  NO;
		totalforders +=  FO;
		totalvorders +=  VO;
		totalporders +=  PO;
		totalnearorders +=  NEO;
		totalnmotors += NM;
		totalfmotors += FM;
		totalvmotors += VM;
		totalvmotors += VM;
		totaldelivery += D;
	}

	RestServ /= totalnorders + totalforders + totalvorders + totalporders + totalnearorders ;
	RestWait /= totalnorders + totalforders + totalvorders + totalporders + totalnearorders;
	FileOutput <<"........................................................\n";
	FileOutput <<"........................................................\n";
	FileOutput <<"Whole Restaurant:\n";
	FileOutput << "\tOrders: " << totalnorders + totalforders + totalvorders + totalporders + totalnearorders << " [Norm: " << totalnorders;
	FileOutput << ", Froz: " << totalforders << ", VIP: " << totalvorders << ", PARTY: " << totalporders << ", Near: " << totalnearorders << "]\n";
	FileOutput << "\tMotorC: " << totalnmotors + totalfmotors + totalvmotors << " [Norm: " << totalnmotors;
	FileOutput << ", Froz: " << totalfmotors << ", VIP: " << totalvmotors << "]\n";
	FileOutput << "DeliveryC: " << totaldelivery <<"\n";
	FileOutput<< "\tAverage Wait = " << RestWait << ",\t Avg Serv = "<< RestServ << "\n\n";

}


