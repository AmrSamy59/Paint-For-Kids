#include "SwitchToDrawModeAction.h"
#include "..\ApplicationManager.h"
#include "../GUI/Output.h"

SwitchToDrawMode::SwitchToDrawMode(ApplicationManager* pApp) :Action(pApp)
{}

void SwitchToDrawMode::ReadActionParameters()
{
}
void SwitchToDrawMode::UndoAction()
{

}
void SwitchToDrawMode::RedoAction()
{
}
void SwitchToDrawMode::Execute()
{
	Output* pOut = pManager->GetOutput();
	voice = "Sound\\Switching To Draw Mode.wav";
	pManager->PlayModeClear();
	pOut->CreateDrawToolBar();
	pOut->ClearStatusBar();
	pManager->DrawModeOriginal();
}