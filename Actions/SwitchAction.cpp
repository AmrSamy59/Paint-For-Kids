#include "SwitchAction.h"
#include "..\ApplicationManager.h"
#include "../GUI/Output.h"

Switch::Switch(ApplicationManager* pApp) :Action(pApp)
{}

void Switch::ReadActionParameters()
{
	if (UI.InterfaceMode == MODE_PLAY)
		switch1 = 0;
	if (UI.InterfaceMode == MODE_DRAW)
		switch1 = 1;
}
void Switch::UndoAction()
{

}
void Switch::RedoAction()
{
}
void Switch::Execute()
{
	ReadActionParameters();
	Output* pOut = pManager->GetOutput();
	if (switch1 == 1)
	{
		pOut->CreatePlayToolBar();
		pOut->ClearStatusBar();
	}
	if (switch1 == 0)    //has to be completed in (Switch to draw mode task)
	{
		pManager->PlayModeClear();
		pOut->CreateDrawToolBar();
		pOut->ClearStatusBar();
	}
}