#pragma once
#include "Rest\Restaurant.h"
#include "Events\ArrivalEvent.h"
#include "Events\CancelationEvent.h"
#include "Events\PromotionEvent.h"
#include <fstream>
#include <iostream>
#include <string>

class InOutFile
{
	string FileName;
	ifstream InputFile;
	ifstream OutputFile;
	Restaurant* pRest;
	GUI* pGUI;

public:
	InOutFile(Restaurant*, GUI*);
	~InOutFile();
	bool Read();
	bool Write();
private:

};

