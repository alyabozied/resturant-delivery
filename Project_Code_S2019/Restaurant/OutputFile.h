#pragma once
#include "Rest\Restaurant.h"
#include "Events\ArrivalEvent.h"
#include "Events\CancelationEvent.h"
#include "Events\PromotionEvent.h"
#include "GUI\GUI.h"
#include <fstream>
#include <iostream>
#include <string>
#include"Region.h"

class OutputFile
{
	string FileName;
	ofstream FileOutput;
	Restaurant* pRest;
	GUI* pGUI;

public:
	OutputFile(Restaurant*, GUI*&);
	void OpenFileOut();
	void PrintFirstLine();
	void PrintStatstics(Region &R, REGION);
	~OutputFile();
	bool Write(Order* O);
private:

};
