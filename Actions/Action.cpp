#include "Action.h"

void Action::PlayActionVoice()
{
	if (voice != "")
	{
		PlaySoundA(voice.c_str(), NULL, SND_FILENAME| SND_ASYNC);
	}
}
