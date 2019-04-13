#include "OutputFile.h"

OutputFile::OutputFile(Restaurant* R, GUI*& G):pRest(R), pGUI(G)
{

}


void OutputFile::OpenFileOut()
{
	pGUI->PrintMessage("enter file name to save the output");
	FileName = pGUI->GetString();
	FileOutput.open(FileName+".txt");
}


OutputFile::~OutputFile()
{
	FileOutput.close();
}
void OutputFile::PrintFirstLine()
{
	FileOutput<<"FT\tID\tAT\tWT\tST\n";
}


bool OutputFile::Write(Order* O)
{
	//modified later to output in a file
	char tmp[4];
	FileOutput<<string(itoa(O->GetFinishTime(),tmp,10))<<"\t"<<string(itoa(O->GetID(),tmp,10))<<"\t"<<string(itoa(O->GetArrTime(),tmp,10))<<"\t"<<string(itoa(O->GetWaitingTime(),tmp,10))<<"\t"<<string(itoa(O->GetServTime(),tmp,10))<<"\n";
	return false;
}

void OutputFile::PrintStatstics(Region& R, REGION reg)
{
	if(reg == 0)
	FileOutput<<"Region A:\n";
	else if(reg == 1)
	FileOutput<<"Region B:\n";
	else if(reg == 2)
	FileOutput<<"Region C:\n";
	else if(reg == 3)
	FileOutput<<"Region D:\n";

	int NO = R.GetWholeNOrdCount();
	int FO = R.GetWholeFOrdCount();
	int VO = R.GetWholeVOrdCount();

	char tmp [10];
	FileOutput<<"Orders: "<<string(itoa(NO+FO+VO,tmp,10))<<" [Norm:"<<string(itoa(NO,tmp,10))<<", Froz:"<<string(itoa(FO,tmp,10))<<", VIP:"<<string(itoa(VO,tmp,10))<<"]\n";
	
	int NM = R.Get_NMotorCnt();
	int FM = R.Get_FMotorCnt();
	int VM = R.Get_VMotorCnt();
	
	FileOutput<<"MotorC: "<<string(itoa(NM+FM+VM,tmp,10))<<" [Norm:"<<string(itoa(NM,tmp,10))<<", Froz:"<<string(itoa(FM,tmp,10))<<", VIP:"<<string(itoa(VM,tmp,10))<<"]\n";
	

}


