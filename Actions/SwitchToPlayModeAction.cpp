#include "SwitchToPlayModeAction.h"
#include "..\ApplicationManager.h"
#include "../GUI/Output.h"

SwitchToPlayMode::SwitchToPlayMode(ApplicationManager* pApp) :Action(pApp)
{}

void SwitchToPlayMode::ReadActionParameters()
{
}
void SwitchToPlayMode::UndoAction()
{

}
void SwitchToPlayMode::RedoAction()
{
}
void SwitchToPlayMode::Execute()
{
	Output* pOut = pManager->GetOutput();
	if (!pManager->CheckRecording())
	{
			voice = "Sound\\Switching To Play Mode.wav";
			pOut->CreatePlayToolBar();
			pOut->ClearStatusBar();
			pManager->PlayModeClearSelection();	
	/*	if (switch1 == 0)
		{
			voice = "Sound\\Switching To Draw Mode.wav";
			pManager->PlayModeClear();
			pOut->CreateDrawToolBar();
			pOut->ClearStatusBar();
			pManager->DrawModeOriginal();
		} */
	}
	else
	{
		pOut->PrintMessage("You can't switch to play mode while recording!");
	}
}