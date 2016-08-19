#pragma once

#include "DynamicGameObject.h"

class TileBox : public CDynamicGameObject
{
public:
	TileBox(int id, float x, float y, float width, float height, LPD3DXSPRITE spriteHandler, LPWSTR filePath);
	~TileBox();
};

