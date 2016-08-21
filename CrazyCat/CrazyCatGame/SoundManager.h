#pragma once

#include "SoundResource.h"
#include <vector>
#include "DirectX.h"

class SoundManager
{
private:
	std::vector<SoundResource*> _list_sound_resource;
	static SoundManager *_instance;
public:
	SoundManager();
	~SoundManager();

	static SoundManager* GetInstance();
	void				 inital(CDirectX * directx);
	Sound*				 getSoundWithID(int id);

	void				 Release();
};

