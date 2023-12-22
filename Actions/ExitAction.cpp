#include "ExitAction.h"
#include "../ApplicationManager.h"


Exit::Exit(ApplicationManager* pApp) : Action(pApp)
{
	voice = "Sound\\EXIT.wav";
}

void Exit::ReadActionParameters() {}
void Exit::RedoAction()
{
}
void Exit::Execute()
{
	PlayActionVoice();
	Sleep(6000);
	exit(0);
}

void Exit::UndoAction()
{}
