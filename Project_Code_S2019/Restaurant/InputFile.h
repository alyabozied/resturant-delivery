#pragma once
#include "Rest\Restaurant.h"
#include "Events\ArrivalEvent.h"
#include "Events\CancelationEvent.h"
#include "Events\PromotionEvent.h"
#include "GUI\GUI.h"
#include <fstream>
#include <iostream>
#include <string>

class InputFile
{
	string FileName;
	ifstream FileInput;
	Restaurant* pRest;
	GUI* pGUI;

public:
	InputFile(Restaurant*, GUI*);
	~InputFile();
	bool Read();


};

