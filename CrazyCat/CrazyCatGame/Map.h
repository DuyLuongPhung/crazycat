#pragma once

#include <d3dx9.h>
#include "DirectX.h"
#include "Collision.h"

class Map
{
public:
	LPDIRECT3DSURFACE9 _image;		// tile
	int _screenHeight;
	int _screenWidth;
	int _maxWidth;
	int _maxHeight;
	CBox* _listObject;
	
public:
	Map();
	Map(int scrWidth, int scrHeight,int maxWidth, int maxHeight);
	~Map();
	void inital(LPDIRECT3DDEVICE9);
	void draw(CDirectX*, D3DXVECTOR2);
};

