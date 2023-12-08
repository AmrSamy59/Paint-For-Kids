#ifndef _SWITCH_H
#define _SWITCH_H
#include "Actions/Action.h"

class Switch : public Action
{
	int switch1;
public:
	Switch(ApplicationManager* pApp);

	
	virtual void ReadActionParameters();

	
	virtual void Execute();

};


#endif // !_SWITCH_H

