#pragma once
#include "Rest\Restaurant.h"
#include "Events\ArrivalEvent.h"
#include "Events\CancelationEvent.h"
#include "Events\PromotionEvent.h"
#include "GUI\GUI.h"
#include <fstream>
#include <iostream>
#include <string>

class OutputFile
{
	string FileName;
	ofstream FileOutput;
	Restaurant* pRest;
	GUI* pGUI;

public:
	OutputFile(Restaurant*, GUI*);
	void OpenFileOut();
	~OutputFile();
	bool Write();
private:

};
