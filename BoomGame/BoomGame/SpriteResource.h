#pragma once

#include "Sprite.h"

class SpriteResource
{
private:
	int			_object_id;
	CSprite *	_data_resource;
public:
	SpriteResource(int objectId, LPD3DXSPRITE SpriteHandler, LPWSTR FilePath, int Width, int Height,
		int Count, int SpritePerRow, D3DCOLOR transparentColor = NULL);
	~SpriteResource();

	int getId(){ return this->_object_id; }
	CSprite* getData(){ if (this->_data_resource)return this->_data_resource; return NULL; }
};

