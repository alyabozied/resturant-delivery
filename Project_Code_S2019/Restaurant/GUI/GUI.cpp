#include "GUI.h"

//////////////////////////////////////////////////////////////////////////////////////////
GUI::GUI()
{
	pWind = new window(WindWidth+15,WindHeight,0,0); 
	pWind->ChangeTitle("The Restautant");

	OrderCount = 0;

	//Set color for each order type
	OrdersClrs[TYPE_NRM] = 	DARKBLUE;	//normal-order color
	OrdersClrs[TYPE_FROZ] = VIOLET;		//Frozen-order color
	OrdersClrs[TYPE_VIP] = 	RED;		//VIP-order color					

	ClearStatusBar();
	ClearDrawingArea(); 
	DrawRestArea();  
	
}
//////////////////////////////////////////////////////////////////////////////////////////
GUI::~GUI()
{
	delete pWind;
}

//////////////////////////////////////////////////////////////////////////////////////////
// ================================== INPUT FUNCTIONS ====================================
//////////////////////////////////////////////////////////////////////////////////////////

void GUI::waitForClick() const
{
	int x,y;
	pWind->WaitMouseClick(x, y);	//Wait for mouse click
}
//////////////////////////////////////////////////////////////////////////////////////////
string GUI::GetString() const 
{
	string Label;
	char Key;
	while(1)
	{
		pWind->WaitKeyPress(Key);
		if(Key == 27 )	//ESCAPE key is pressed
			return "";	//returns nothing as user has cancelled label
		if(Key == 13 )	//ENTER key is pressed
			return Label;
		if((Key == 8) && (Label.size() >= 1))	//BackSpace is pressed
			Label.resize(Label.size() -1 );			
		else
			Label += Key;
		
		PrintMessage(Label);
	}
}

//////////////////////////////////////////////////////////////////////////////////////////
// ================================== OUTPUT FUNCTIONS ===================================
//////////////////////////////////////////////////////////////////////////////////////////

void GUI::PrintMessage(string msg,string msg1,string msg2,string msg3,string msg4,string msg5) const	//Prints a message on status bar
{
	ClearStatusBar();	//First clear the status bar
	
	pWind->SetPen(DARKRED);
	pWind->SetFont(18, BOLD , BY_NAME, "Arial");   
	pWind->DrawString(10, WindHeight - (int) (StatusBarHeight/1.1), msg); // You may need to change these coordinates later 
	pWind->DrawString(10, WindHeight - (int) (StatusBarHeight/1.1)+20, msg1); // You may need to change these coordinates later 
	pWind->DrawString(10, WindHeight - (int) (StatusBarHeight/1.1)+40, msg2); // You may need to change these coordinates later 
	pWind->DrawString(10, WindHeight - (int) (StatusBarHeight/1.1)+60, msg3); // You may need to change these coordinates later 
	pWind->DrawString(10, WindHeight - (int) (StatusBarHeight/1.1)+80, msg4); // You may need to change these coordinates later 
	pWind->DrawString(10, WindHeight - (int) (StatusBarHeight/1.1)+100, msg5); // You may need to change these coordinates later 
	                                                  // to be able to write multi-line
}
//////////////////////////////////////////////////////////////////////////////////////////
void GUI::DrawString(const int iX, const int iY, const string Text)
{
	pWind->SetPen(DARKRED);
	pWind->SetFont(18, BOLD , BY_NAME, "Arial");   
	pWind->DrawString(iX, iY, Text);
}

//////////////////////////////////////////////////////////////////////////////////////////
void GUI::ClearStatusBar() const
{
	pWind->SetPen(RED, 2);
	pWind->SetBrush(WHITE);
	pWind->DrawRectangle(0, WindHeight - StatusBarHeight , WindWidth, WindHeight);	

	pWind->SetPen(RED, 1);
	pWind->DrawLine(0, WindHeight - StatusBarHeight , WindWidth, WindHeight - StatusBarHeight);	
}
///////////////////////////////////////////////////////////////////////////////////
void GUI::ClearDrawingArea() const
{
	//    DARKOLIVEGREEN  DARKRED  DARKSALMON   DARKSEAGREEN   DARKTURQUOISE
	// Clearing the Drawing area

	//up left 
	pWind->SetPen(SALMON, 3);
	pWind->SetBrush(SALMON);
	pWind->DrawRectangle(0, MenuBarHeight, WindWidth/2, (WindHeight-100)/2);

	//up right 
	pWind->SetPen(CADETBLUE, 3);
	pWind->SetBrush(CADETBLUE);
	pWind->DrawRectangle(WindWidth/2, (WindHeight-100)/2 , WindWidth, MenuBarHeight );	

	//down left 
	pWind->SetPen(DARKSEAGREEN, 3);
	pWind->SetBrush(DARKTURQUOISE);	
	pWind->DrawRectangle(0, WindHeight-StatusBarHeight, WindWidth/2,  (WindHeight-100)/2 );
	
	//down right  
	pWind->SetPen(DARKRED, 3);
	pWind->SetBrush(DARKRED);
	pWind->DrawRectangle(WindWidth/2, WindHeight-StatusBarHeight, WindWidth,  (WindHeight-100)/2 );
	
}
///////////////////////////////////////////////////////////////////////////////////
void GUI::DrawRestArea() const
{
	int L = RestWidth / 2;

	// 1- Drawing the brown square of the Rest
	pWind->SetPen(DARKBLUE);
	pWind->SetBrush(YELLOW);
	pWind->DrawCircle(WindWidth/2, (WindHeight-100)/2,200);

	// 2- Drawing the 2 brown crossed lines (for making 4 regions)

	pWind->SetPen(BROWN, 3);
	pWind->DrawLine(0, YHalfDrawingArea, WindWidth, YHalfDrawingArea);
	pWind->DrawLine(WindWidth/2, MenuBarHeight, WindWidth/2, WindHeight-StatusBarHeight);

	
	

	// 5- Writing the letter of each region (A, B, C, D)
	pWind->SetPen(FORESTGREEN);
	pWind->SetFont(25, BOLD , BY_NAME, "Arial");
	pWind->DrawString(530 ,  RestStartY + 5*L/12, "A");
	pWind->DrawString(530 , YHalfDrawingArea + 5*L/12, "D");
	pWind->DrawString(WindWidth/2 + (int)(0.44*L), RestStartY + 5*L/12, "B");
	pWind->DrawString(WindWidth/2 + (int)(0.44*L), YHalfDrawingArea + 5*L/12, "C"); 

	// 6- Drawing circle to count the current step
	pWind->SetPen(BLACK);
	pWind->SetBrush(DARKRED);
	pWind->DrawCircle(600,275,50);
}
//////////////////////////////////////////////////////////////////////////////////////////
void GUI::DrawSingleOrder(Order* pO, int RegionCount) const       // It is a private function
{

	if (RegionCount > MaxRegionOrderCount) 
		return; //no more orders can be drawn in this region

	int DrawDistance = RegionCount;
	int YPos = 1;
	if(RegionCount>=MaxHorizOrders )	//max no. of orders to draw in one line
	{
		DrawDistance = (RegionCount-1)%MaxHorizOrders + 1;
		YPos = (RegionCount-1) / MaxHorizOrders + 1; 
	}

	color clr = OrdersClrs[pO->GetType()];
	REGION Region = pO->GetRegion();

	int x, y, refX, refY;
	//First calculate x,y position of the order on the output screen
	//It depends on the region and the order distance
	switch (Region)
	{
	case A_REG:
		refX = (WindWidth/2 - 200);
		refY = YHalfDrawingArea - OrderHeight; //
		x = refX - DrawDistance*OrderWidth - DrawDistance; //(Distance)
		y = refY - YPos*OrderHeight - YPos; // YPos
		break;
	case B_REG:
		refX = (WindWidth/2 + 200);
		refY = YHalfDrawingArea - OrderHeight; //
		x = refX + (DrawDistance-1)*OrderWidth + DrawDistance; //(Distance)
		y = refY - YPos*OrderHeight - YPos; // YPos
		break;
	case C_REG:
		refX = (WindWidth/2 + 200);
		refY = YHalfDrawingArea + OrderHeight; //
		x = refX + (DrawDistance-1)*OrderWidth + DrawDistance; //(Distance)
		y = refY + (YPos-1)*OrderHeight + YPos; // YPos
		break;
	case D_REG:
		refX = (WindWidth/2 - 200);
		refY = YHalfDrawingArea + OrderHeight; //
		x = refX - DrawDistance*OrderWidth - DrawDistance; //(Distance)
		y = refY + (YPos-1)*OrderHeight + YPos; // YPos
		break;
	default:
		break;
	}

	// Drawing the Order
	pWind->SetPen(clr);
	pWind->SetBrush(clr);
	pWind->SetFont(20,BOLD, MODERN);
	pWind->DrawInteger(x,y,pO->GetID());
}


//////////////////////////////////////////////////////////////////////////////////////////
/* A function to draw a list of orders and ensure there is no overflow in the drawing*/
// To use this function, you must prepare its input parameters as specified
// [Input Parameters]:
//    orders [ ] : array of Order pointers (ALL orders from all regions in one array)
//    TotalOrders : the size of the array (total no. of orders)
void GUI::DrawOrders() const
{

	//Prepare counter for each region
	int RegionsCounts[REG_CNT]={0};	//initlaize all counters to zero

	for(int i=0; i<OrderCount; i++)
	{
		int orderRegion = OrdListForDrawing[i]->GetRegion();
		RegionsCounts[orderRegion]++;
		DrawSingleOrder(OrdListForDrawing[i], RegionsCounts[orderRegion]);
	}

}

void GUI::UpdateInterface() 
{
	ClearDrawingArea();
	DrawRestArea();
	DrawOrders();
}

/*
	AddOrderForDrawing: Adds a new order to the drawing list
*/
void GUI::AddOrderForDrawing(Order* ptr)
{
	if (OrderCount < MaxPossibleOrdCnt) 
		OrdListForDrawing[OrderCount++] = ptr;

	// Note that this function doesn't allocate any Order objects
	// It only makes the first free pointer in the array
	// points to the same Order pointed to by "ptr"
}

void GUI::ResetDrawingList()
{
	OrderCount = 0;		//resets the orders count to be ready for next timestep updates
}


PROG_MODE	GUI::getGUIMode() const
{
	PROG_MODE Mode;
	do
	{
		PrintMessage("Please select GUI mode: (1)Interactive, (2)StepByStep, (3)Silent, (4)Phase one ... ");
		string S = GetString();
		Mode = (PROG_MODE) (atoi(S.c_str())-1);
	}
	while(Mode< 0 || Mode >= MODE_CNT);
	
	return Mode;
}
///////////////////////////////////////////////////////////////
void GUI::DrawTimeStepCenter(string TS)
{

	
	// Drawing current step
	pWind->SetPen(DARKMAGENTA);
	pWind->SetFont(20,BOLD, MODERN);
	pWind->DrawString(580,265,"00:"+TS);

}
