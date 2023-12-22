#include "Action.h"

void Action::PlayActionVoice()
{
	if (voice != "novoice")
	{
		cout << 1 << endl;
		PlaySoundA(voice.c_str(), NULL, SND_FILENAME| SND_ASYNC);
	}
}
