#include "SoundResource.h"


SoundResource::SoundResource(int id, LPDIRECTSOUND8 lpDSound, LPWSTR path)
{
	this->_id_sound = id;
	this->_sound_data = new Sound(lpDSound, path);
}


SoundResource::~SoundResource()
{
	SAFE_DELETE(this->_sound_data);
}
