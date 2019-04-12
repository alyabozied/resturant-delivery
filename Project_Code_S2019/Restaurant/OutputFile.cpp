#include "OutputFile.h"

OutputFile::OutputFile(Restaurant* R, GUI* G):pRest(R), pGUI(G)
{
	G->PrintMessage("enter file name to save the output");
	FileName = G->GetString();
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




