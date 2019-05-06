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
	float RegionWait[4];  // to store the avg wait time for all regions
	float RegionServ[4];  // to store the avg serice time for  all regions
	float RestWait;		  // to store the avg wait time for the whole restaurant
	float RestServ;		  // to store the avg service time for the whole restaurant

public:
	OutputFile(Restaurant*, GUI*&);
	void OpenFileOut();
	void PrintStatstics();
	~OutputFile();
	void Write(Order* O);


};
