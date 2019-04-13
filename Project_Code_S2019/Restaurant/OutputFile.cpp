#include "OutputFile.h"

OutputFile::OutputFile(Restaurant* R, GUI* G):pRest(R), pGUI(G)
{

}


void OutputFile::OpenFileOut()
{
	pGUI->PrintMessage("enter file name to save the output");
	FileName = pGUI->GetString();
	FileOutput.open(FileName + ".txt");

}


OutputFile::~OutputFile()
{
	FileOutput.close();
}

bool OutputFile::Write()
{
	//modified later to output in a file
	return false;
}



