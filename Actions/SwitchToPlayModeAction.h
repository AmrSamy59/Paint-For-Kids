#ifndef _SWITCH_TO_PLAY_MODE_H
#define _SWITCH_TO_PLAY_MODE_H
#include "../Actions/Action.h"

class SwitchToPlayMode : public Action
{
public:
	SwitchToPlayMode(ApplicationManager* pApp);

	virtual void UndoAction();
	virtual void ReadActionParameters();

	virtual void RedoAction();
	virtual void Execute();

};


#endif // !_SWITCH_TO_PLAY_MODE_H

