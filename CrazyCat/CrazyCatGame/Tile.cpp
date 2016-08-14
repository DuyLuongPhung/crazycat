#include "Tile.h"


Tile::Tile()
{
}


Tile::~Tile()
{
}

void Tile::inital(LPD3DXSPRITE SpriteHandler, LPWSTR FilePath, int Width, int Height){
	this->_tileImage = new CSprite(SpriteHandler, FilePath, Width, Height, 1, 1);
	this->_tileImage->Next();
}

void Tile::draw(D3DXVECTOR2 viewPort, int x, int y){
	this->_tileImage->Render(viewPort, x, y);
}
