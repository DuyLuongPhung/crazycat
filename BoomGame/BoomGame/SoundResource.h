#pragma once
#include "Sound.h"
#include "CONST.h"

class SoundResource
{
private:
	int		_id_sound;
	Sound*	_sound_data;
public:
	SoundResource(int id, LPDIRECTSOUND8 lpDSound, LPWSTR path);
	~SoundResource();

	int		getId(){ return this->_id_sound; }
	Sound*	getSound(){ return this->_sound_data; }
};

