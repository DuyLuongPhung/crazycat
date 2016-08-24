#include "SpriteResource.h"


SpriteResource::SpriteResource(int objectId, LPD3DXSPRITE spriteHandler, LPWSTR filePath, int width, int height, int count,
	int spritePerRow, D3DCOLOR transparentColor)
{
	this->_object_id = objectId;
	this->_data_resource = new CSprite(spriteHandler, filePath, width, height, count, spritePerRow,transparentColor);
}


SpriteResource::~SpriteResource()
{
	if (this->_data_resource)
		delete(this->_data_resource);
}
