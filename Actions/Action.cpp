#include "Action.h"

void Action::PlayActionVoice()
{
		if (voice != "" &&UI.SoundEnabled)
		{
			PlaySoundA(voice.c_str(), NULL, SND_FILENAME | SND_ASYNC);
		}
}

Action::~Action()
{

}
