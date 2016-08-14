#include "Map.h"


Map::Map(){
	_listObject = new CBox[300];
	for (int i = 0; i < 300; i++)
	{
		_listObject[i] = CBox(32 * i, 32, 32, 32, 0, 0);
	}
}

Map::Map(int scrWidth, int scrHeight, int maxWidth, int maxHeight)
{
	_listObject = new CBox[300];
	for (int i = 0; i < 300; i++)
	{
		_listObject[i] = CBox(32 * i, 32, 32, 32, 0, 0);
	}

	this->_screenHeight = scrHeight; 
	this->_screenWidth = scrWidth;
	this->_maxWidth = maxWidth;
	this->_maxHeight = maxHeight;
}


Map::~Map()
{
	
}

void Map::inital(LPDIRECT3DDEVICE9 d3ddv){
	this->_image = LoadSurfaceFromFile(d3ddv, L"Map1.png", D3DCOLOR_XRGB(255, 0, 255));
}


void Map::draw(CDirectX *directXDivice, D3DXVECTOR2 viewPort){

	RECT desRect;
	RECT srcRect;


	srcRect.top = 0;
	srcRect.bottom = this->_screenHeight;
	srcRect.left = viewPort.x;
	srcRect.right = srcRect.left + this->_screenWidth;

	desRect.top = 0;
	desRect.bottom = this->_screenHeight;
	desRect.left = 0;
	desRect.right = desRect.left + this->_screenWidth;

	directXDivice->getDevice()->StretchRect(_image,
		&srcRect,
		directXDivice->getBackBuffer(),
		&desRect,
		D3DTEXF_LINEAR);

}
