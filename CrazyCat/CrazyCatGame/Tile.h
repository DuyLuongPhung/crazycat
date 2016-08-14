#pragma once

#include "Sprite.h"

class Tile
{
public:
	CSprite *_tileImage;
public:
	Tile();
	~Tile();

	void inital(LPD3DXSPRITE SpriteHandler, LPWSTR FilePath, int Width, int Height);
	void draw(D3DXVECTOR2 viewPort, int X, int Y);
};

