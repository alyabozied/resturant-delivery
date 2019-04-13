#include "GUI.h"

//////////////////////////////////////////////////////////////////////////////////////////
GUI::GUI()
{
	pWind = new window(WindWidth +15,WindHeight,0,0); 
	pWind->ChangeTitle("The Restautant");

	OrderCount = 0;

	//Set color for each order type
	OrdersClrs[TYPE_NRM] = 	PTHALOWBLUE;	//normal-order color
	OrdersClrs[TYPE_FROZ] = MAGENTA;		//Frozen-order color
	OrdersClrs[TYPE_VIP] = 	RED;	//VIP-order color					

	ClearStatusBar();
	ClearDrawingArea();
	CreateDrawToolBar();
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
void GUI::ClearToolBar() const
{
	//Clear Status bar by drawing a filled rectangle
	pWind->SetPen(VIOLETYELL, 2);
	pWind->SetBrush(VIOLETYELL);
	pWind->DrawRectangle(0, 0, WindWidth, MenuBarHeight);
}

//////////////////////////////////////////////////////////////////////////////////////////
// ================================== MENUITEMBAR CREATION =============================//
//////////////////////////////////////////////////////////////////////////////////////////

void GUI::CreateDrawToolBar()const
{

	ClearToolBar();
	string MenuItemImages[MODE_CNT];
	MenuItemImages[MODE_INTR] = "MENUEBAR//INTER_MODE.jpg";     //icon for first mode 
  	MenuItemImages[MODE_STEP]="MENUEBAR//SLEEP_MODE.jpg";         //icon for second mode 
	MenuItemImages[MODE_SLNT]="MENUEBAR//SILENT_MODE.jpg";        //icon for third mode 
	MenuItemImages[MODE_EXIT]="MENUEBAR//EXIT.jpg";        //icon for phase one mode 
	// Prepare images for each menu item and add it to the list (DONE)
	//Draw menu item one image at a time
	pWind->SetPen(ROYALYELLOW,2);
	for(int i=0; i<MODE_CNT; i++)
	{
		pWind->DrawImage(MenuItemImages[i], i*MenuItemWidth, 0, MenuItemWidth, MenuBarHeight);
		//pWind->DrawLine((i+1)*MenuItemWidth - 1, 0, (i+1)*MenuItemWidth - 1, MenuBarHeight);	 //draw a line between each element in the toolbar
	}
	
	
	//Draw a line under the toolbar
	//pWind->DrawLine(0, MenuBarHeight + 2.5, WindWidth, MenuBarHeight + 2.5);
}





//////////////////////////////////////////////////////////////////////////////////////////
// ================================== GET USER ACTION  ==========================//
//////////////////////////////////////////////////////////////////////////////////////////


PROG_MODE GUI::GetUserAction() const
{	
	int x,y;
	pWind->WaitMouseClick(x, y);	//Get the coordinates of the user click

		//[1] If user clicks on the Toolbar
	if ( y >= 0 && y < MenuBarHeight)
		{	
			//Check whick Menu item was clicked
			//==> This assumes that menu items are lined up horizontally <==
			int ClickedItemOrder = (x / MenuItemWidth);
			//Divide x coord of the point clicked by the menu item width (int division)
			//if division result is 0 ==> first item is clicked, if 1 ==> 2nd item and so on

			switch (ClickedItemOrder)
			{
			case MODE_INTR: return MODE_INTR; 
			case MODE_STEP: return MODE_STEP;
			case MODE_SLNT: return MODE_SLNT;
			case MODE_EXIT: return MODE_EXIT;	
			default: return MODE_EMPYT;	//A click on empty place in desgin toolbar
			}
		}

	return MODE_EMPYT;

}



//////////////////////////////////////////////////////////////////////////////////////////
// ================================== OUTPUT FUNCTIONS =================================//
//////////////////////////////////////////////////////////////////////////////////////////

void GUI::PrintMessage(string msg,string msg1,string msg2,string msg3) const	//Prints a message on status bar
{
	ClearStatusBar();	//First clear the status bar
	pWind->SetPen(ETSHAWY);
	pWind->SetFont(25, BOLD, BY_NAME, "SWISS");   
	pWind->DrawString(10, WindHeight - (int) (StatusBarHeight/1.1), msg); 

	if(msg1 == "")
		return;
	pWind->SetPen(LIGHTYELLOW);
	pWind->DrawLine(0, WindHeight - (int) (StatusBarHeight/1.1) + 25, WindWidth, WindHeight - (int) (StatusBarHeight/1.1) + 25);


	pWind->SetPen(ETSHAWY);
	pWind->DrawString(10, WindHeight - (int) (StatusBarHeight/1.1)+30, msg1); 
	pWind->SetPen(LIGHTYELLOW);
	pWind->DrawLine(0, WindHeight - (int) (StatusBarHeight/1.1) + 55, WindWidth, WindHeight - (int) (StatusBarHeight/1.1) + 55);

	pWind->SetPen(ETSHAWY);
	pWind->DrawString(10, WindHeight - (int) (StatusBarHeight/1.1)+60, msg2); 
	pWind->SetPen(LIGHTYELLOW);
	pWind->DrawLine(0, WindHeight - (int) (StatusBarHeight/1.1) + 85, WindWidth, WindHeight - (int) (StatusBarHeight/1.1) + 85);


	pWind->SetPen(ETSHAWY);
	pWind->DrawString(10, WindHeight - (int) (StatusBarHeight/1.1)+90, msg3);  
	                                                  
}
//////////////////////////////////////////////////////////////////////////////////////////
void GUI::DrawString(const int iX, const int iY, const string Text)
{
	pWind->SetPen(DARKRED);
	pWind->SetFont(18, BOLD , BY_NAME, "ROMAN");   
	pWind->DrawString(iX, iY, Text);
}

//////////////////////////////////////////////////////////////////////////////////////////
void GUI::ClearStatusBar() const
{
	pWind->SetPen(VIOLETYELL, 2);
	pWind->SetBrush(VIOLETYELL);
	pWind->DrawRectangle(0, WindHeight - StatusBarHeight , WindWidth, WindHeight);	

	pWind->SetPen(ROYALYELLOW, 1);
	pWind->DrawLine(0, WindHeight - StatusBarHeight , WindWidth, WindHeight - StatusBarHeight);	
}
///////////////////////////////////////////////////////////////////////////////////
void GUI::ClearDrawingArea() const
{
	//    DARKOLIVEGREEN  DARKRED  DARKSALMON   DARKSEAGREEN   DARKTURQUOISE
	// Clearing the Drawing area

	//up left 
	pWind->SetPen(ROYALYELLOW, 1);
	pWind->SetBrush(ROYALYELLOW);
	pWind->DrawRectangle(0, MenuBarHeight , WindWidth/2, (WindHeight-100)/2);

	//up right 
	pWind->SetPen(ROYALYELLOW, 1);
	pWind->SetBrush(ROYALYELLOW);
	pWind->DrawRectangle(WindWidth/2, MenuBarHeight , WindWidth, (WindHeight-100)/2 );	

	//down left 
	pWind->SetPen(ROYALYELLOW, 1);
	pWind->SetBrush(ROYALYELLOW);	
	pWind->DrawRectangle(0, WindHeight-StatusBarHeight, WindWidth/2,  (WindHeight-100)/2 );
	
	//down right  
	pWind->SetPen(ROYALYELLOW, 1);
	pWind->SetBrush(ROYALYELLOW);
	pWind->DrawRectangle(WindWidth/2, WindHeight-StatusBarHeight, WindWidth,  (WindHeight-100)/2 );

}
///////////////////////////////////////////////////////////////////////////////////
void GUI::DrawRestArea() const
{
	int L = RestWidth / 2;
	// drawing a line after the menu bar
	pWind->SetPen(ROYALYELLOW, 2);
	pWind->DrawLine(0,MenuBarHeight, WindWidth, MenuBarHeight);
	// 1- Drawing the Circle of the Rest
	pWind->SetPen(DARKBLUE, 3);
	pWind->SetBrush(ETSHAWY);
	pWind->DrawCircle(WindWidth/2, (WindHeight-100)/2,RegionCircle);

	// 2- Drawing the 2 crossed lines (for making 4 regions)

	pWind->SetPen(DARKBLUE, 3);
	pWind->DrawLine(0, YHalfDrawingArea, WindWidth, YHalfDrawingArea);
	pWind->DrawLine(WindWidth/2, MenuBarHeight, WindWidth/2, WindHeight-StatusBarHeight);

	
	

	// 3- Writing the letter of each region (A, B, C, D)
	pWind->SetPen(VIOLETYELL);
	pWind->SetFont(50, BOLD , BY_NAME, "SWISS");
	pWind->DrawString(WindWidth/2 - (int)(0.44*L)-20,  RestStartY + 5*L/12, "A");
	pWind->DrawString(WindWidth/2 - (int)(0.44*L)-20 , YHalfDrawingArea + 5*L/12, "D");
	pWind->DrawString(WindWidth/2 + (int)(0.44*L), RestStartY + 5*L/12, "B");
	pWind->DrawString(WindWidth/2 + (int)(0.44*L), YHalfDrawingArea + 5*L/12, "C"); 

	// 4- Drawing circle to count the current step
	pWind->SetPen(DARKBLUE, 3);
	pWind->SetBrush(YELLOW);
	pWind->DrawCircle(WindWidth/2,(WindHeight-100)/2,TimestepCircleRaidus);

}
//////////////////////////////////////////////////////////////////////////////////////////
void GUI::DrawSingleOrder(Order* pO, int RegionCount) const       // It is a private function
{
	if (RegionCount > MaxRegionOrderCount) 
		return; //no more orders can be drawn in this region

	int DrawDistance = RegionCount * (OrderWidth + 13);
	int YPos = 1;
	if( RegionCount >= MaxHorizOrders)	//max no. of orders to draw in one line
	{
		DrawDistance = ((RegionCount) % MaxHorizOrders ) * (OrderWidth + 13) ;
		DrawDistance = (DrawDistance == 0) ? MaxHorizOrders * (OrderWidth + 13) :DrawDistance;
		YPos = (RegionCount - 1) / MaxHorizOrders + 1; 
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
		x = refX - DrawDistance ; //(Distance)
		y = refY - YPos*OrderHeight ; // YPos
		break;
	case B_REG:
		refX = (WindWidth/2 + 150);
		refY = YHalfDrawingArea - OrderHeight; //
		x = refX + DrawDistance; //(Distance)
		y = refY - YPos*OrderHeight - YPos; // YPos
		break;
	case C_REG:
		refX = (WindWidth/2 + 150);
		refY = YHalfDrawingArea + OrderHeight; //
		x = refX + DrawDistance; //(Distance)
		y = refY + (YPos-1)*OrderHeight + YPos; // YPos
		break;
	case D_REG:
		refX = (WindWidth/2 - 200);
		refY = YHalfDrawingArea + OrderHeight; //
		x = refX - DrawDistance; //(Distance)
		y = refY + (YPos-1)*OrderHeight + YPos; // YPos
		break;
	default:
		break;
	}

	// Drawing the Order
	pWind->SetPen(clr);
	pWind->SetBrush(clr);
	pWind->SetFont(30,BOLD, ROMAN);
	int temp = pO->GetID();
	if(temp < 99)
	{
		temp += 100;
		char c[4];
		_itoa_s(temp,c,10);
		c[0] = '0';
		pWind->DrawString(x,y,c);
	}
	else 
		pWind->DrawInteger(x, y, temp);
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
	int twodigit[REG_CNT] = {0};
	int onedigit[REG_CNT] = {0};
	int tempone = 1;
	int temptwo = 0;
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
		PrintMessage("Please select one of the menu bar icons ");
		Mode = GetUserAction();

	}
	while(Mode< 0 || Mode >= MODE_CNT);
	
	return Mode;
}
///////////////////////////////////////////////////////////////
void GUI::DrawTimeStepCenter(string TS)
{
	string s = "00";
	string min = "00";
	min[1] = (stoi(TS) / 60) + '0';
	if(stoi(TS) % 60 < 10)
		s = "0" + to_string(stoi(TS) % 60);
	else
		s = to_string(stoi(TS) % 60);
	// Drawing current step
	pWind->SetPen(DARKBLUE);
	pWind->SetFont(40,BOLD, ROMAN);
	pWind->DrawString(WindWidth/2-40, (WindHeight-100)/2-20,min + ":" + s);

}
