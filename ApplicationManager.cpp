#include "ApplicationManager.h"
#include "Actions\AddRectAction.h"
#include"AddSquareAction.h"
#include"AddTriangleAction.h"
#include "Select.h"
#include"AddHexagonAction.h"
#include"AddCircleAction.h"
#include "AddClearAllAction.h"
#include "AddDeleteAction.h"
#include "Move.h"
#include "UndoAction.h"
#include "Switch.h"

#include <iostream>

//Constructor
ApplicationManager::ApplicationManager()
{
	//Create Input and output
	pOut = new Output;
	pIn = pOut->CreateInput();
	
	FigCount = 0;
		
	//Create an array of figure pointers and set them to NULL		
	for (int i = 0; i < MaxFigCount; i++)
	{
		FigList[i] = NULL;
		ActionList[i] = NULL;
	}
}

//==================================================================================//
//								Actions Related Functions							//
//==================================================================================//
ActionType ApplicationManager::GetUserAction() const
{
	//Ask the input to get the action from the user.
	return pIn->GetUserAction();		
}
////////////////////////////////////////////////////////////////////////////////////
//Creates an action and executes it
void ApplicationManager::ExecuteAction(ActionType ActType) 
{
	Action* pAct = NULL;
	
	//According to Action Type, create the corresponding action object
	switch (ActType)
	{
		case DRAW_RECT:
			pAct = new AddRectAction(this);
			break;
		case DRAW_SQUARE:
			pAct = new AddSquareAction(this);
			break;
		case DRAW_TRIANGLE:
			pAct = new AddTriangleAction(this);
			break;
		case DRAW_HEXAGON:
			pAct = new AddHexagonAction(this);
			break;
		case DRAW_CIRC :
			pAct = new AddCircleAction(this);
			break;
		case DRAW_DELETE:
			pAct = new AddDeleteAction(this);// Delete Selected Figure
			break;
		case DRAW_CLEARALL:
		//	pAct = new AddClearAllAction(this); // Delete all Figures
			break;

		case DRAW_SAVEGRAPH:
			Save_All();
			break;
		case DRAW_SELECT:
			pAct = new Select(this);
			break;
		case DRAW_MOVE:
			pAct = new Move(this);
			break;
		case DRAW_UNDO:
			ExecuteUndoAction();
			break;

		case TO_PLAY:
			pAct = new Switch(this);
			break;
		case DRAW_ITM_DRAWMODE:
			pAct = new Switch(this);   
			break;
		
		case EXIT:
			///create ExitAction here
			
			break;
		
		case STATUS:	//a click on the status bar ==> no action
			return;
	}
	
	//Execute the created action
	if(pAct != NULL)
	{
		pAct->Execute();//Execute
		AddAction(pAct);//You may need to change this line depending to your implementation
	}
}
void ApplicationManager::AddAction(Action *pAction)
{
	if (FigCount < MaxFigCount)
		ActionList[FigCount++] = pAction;
}
CFigure* ApplicationManager::GetTheLastDrawnObject() const
{
	static unsigned short i;
	static unsigned short PrevPassedFigCount = 0;
	if (PrevPassedFigCount != FigCount)
	{
		PrevPassedFigCount = FigCount;
		i = 1;
	}
	while (1) {
		if (ActionList[FigCount - i])
		{
			return FigList[FigCount - i++];
		}
		else
			i++;
	}
}
void ApplicationManager::ExecuteUndoAction()
{
	static unsigned short i;
	static unsigned short PrevPassedFigCount = 0;
	if (PrevPassedFigCount != FigCount)
	{
		PrevPassedFigCount = FigCount;
		i = 1;
	}
	while (1)
	{
		if (ActionList[FigCount - i])
		{
			ActionList[FigCount - i]->UndoAction();
			if (dynamic_cast<AddRectAction*>(ActionList[FigCount - i]) != NULL || dynamic_cast<AddSquareAction*>(ActionList[FigCount - i]) != NULL
				|| dynamic_cast<AddHexagonAction*>(ActionList[FigCount - i]) != NULL || dynamic_cast<AddCircleAction*>(ActionList[FigCount - i]) != NULL
				|| dynamic_cast<AddTriangleAction*>(ActionList[FigCount - i]) != NULL)
				FigList[FigCount - i] = NULL;
			ActionList[FigCount - i++] = NULL;
			break;
		}
		else
			i++;
	}
}
void ApplicationManager::Save_All() const
{
	ofstream Fout;
	Fout.open("test.txt");
	for (int i = 0; i < FigCount; i++)
		FigList[i]->Save(Fout);
	pOut->PrintMessage("Graph has been saved succesfully");
	Fout.close();
}
//==================================================================================//
//						Figures Management Functions								//
//==================================================================================//

//Add a figure to the list of figures
void ApplicationManager::AddFigure(CFigure* pFig)
{
	if (FigCount < MaxFigCount)
		FigList[FigCount] = pFig;
}
////////////////////////////////////////////////////////////////////////////////////
CFigure *ApplicationManager::GetFigure(int x, int y) const
{
	//If a figure is found return a pointer to it.
	//if this point (x,y) does not belong to any figure return NULL


	//Add your code here to search for a figure given a point x,y	
	//Remember that ApplicationManager only calls functions do NOT implement it.

	
	for (int i = FigCount - 1; i >= 0; i--) // Prioritize last added items
	{
		if (FigList[i]->CheckSelection(x, y) && FigList[i] != NULL)
		{
			int j = 0;
			while(j < FigCount)
			{
				FigList[j]->SetSelected(false);
				j++;
			}
			return FigList[i];
		}
	}

	for (int j = 0; j < FigCount; j++)
	{
		FigList[j]->SetSelected(false);
	}

	return NULL;
}
CFigure* ApplicationManager::GetSelectedFigure() const
{
	int j = 0;
	while (j < FigCount)
	{
		if (FigList[j] != NULL && FigList[j]->IsSelected() == true && FigList[j]->GetFigureAbilityToBeDrawn() == true)
		{
			return FigList[j];
		}
		j++;
	}
	return NULL;
}
//==================================================================================//
//							Interface Management Functions							//
//==================================================================================//

//Draw all figures on the user interface
void ApplicationManager::UpdateInterface() const
{	
	pOut->ClearDrawArea();
	for(int i=0; i<FigCount; i++)
		if(FigList[i] != NULL && FigList[i]->GetFigureAbilityToBeDrawn() == true )
			FigList[i]->Draw(pOut);		//Call Draw function (virtual member fn)
}

////////////////////////////////////////////////////////////////////////////////////
//Return a pointer to the input
Input *ApplicationManager::GetInput() const
{	return pIn; }
//Return a pointer to the output
Output *ApplicationManager::GetOutput() const
{	return pOut; }
////////////////////////////////////////////////////////////////////////////////////
//Destructor
ApplicationManager::~ApplicationManager()
{
	for (int i = 0; i < FigCount; i++)
	{
		delete FigList[i];
		delete ActionList[i];
	}
	delete pIn;
	delete pOut;
}
