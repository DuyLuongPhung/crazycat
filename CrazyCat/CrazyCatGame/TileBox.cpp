#include "TileBox.h"


TileBox::TileBox(int id, float x, float y, float width, float height, LPD3DXSPRITE spriteHandler, LPWSTR filePath)
	: CDynamicGameObject(id, x, y, width, height, 0.0f, 0.0f, spriteHandler, filePath, 1, 1)
{
}

TileBox::~TileBox()
{
}
