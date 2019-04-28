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
	float RegionWait[REG_CNT];
	float RegionServ[REG_CNT];
	float RestWait;
	float RestServ;

public:
	OutputFile(Restaurant*, GUI*&);
	void OpenFileOut();
	void PrintStatstics();
	~OutputFile();
	void Write(Order* O);


};
