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
	Output* pOut = pManager->GetOutput();
	if (!pManager->CheckRecording())
	{
		ReadActionParameters();
		if (switch1 == 1)
		{
			voice = "Sound\\Switching To Play Mode.wav";
			pOut->CreatePlayToolBar();
			pOut->ClearStatusBar();
			pManager->PlayModeClearSelection();
		}
		if (switch1 == 0)    //has to be completed in (Switch to draw mode task)
		{
			voice = "Sound\\Switching To Draw Mode.wav";
			pManager->PlayModeClear();
			pOut->CreateDrawToolBar();
			pOut->ClearStatusBar();
			pManager->DrawModeOriginal();
		}
	}
	else
	{
		pOut->PrintMessage("You can't switch to play mode while recording!");
	}
}