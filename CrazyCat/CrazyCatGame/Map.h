#pragma once

#include <d3dx9.h>
#include "DirectX.h"
#include "Sprite.h"
#include "Box.h"
#include <signal.h>
#include <string.h>
#include <stdio.h>
#include <stdarg.h>
#include <time.h>
#include <stdlib.h>
#include <windows.h>

#include <iostream>
#include <fstream>
#include <string>
#include "QuadTree.h"
#include "Brick.h"


struct TileMap{
	int id;
	int x;
	int y;
	int w;
	int h;

	TileMap(int id, int x, int y, int w, int h){
		this->id = id;
		this->x = x;
		this->y = y;
		this->w = w;
		this->h = h;
	}
	TileMap(){}
};

struct QNodeItem{
	int index;
	int typeId;
	std::string  source_image;
	int w;
	int h;
	int count_sprites;
	int sprite_per_row;

};

struct QNodeObjects{
	int index;
	int node_id;
	int x;
	int y;
};



class Map
{
public:
	LPDIRECT3DSURFACE9 _m_background;			// màn hình nền
	LPDIRECT3DSURFACE9  _m_tile_background;		// màn hình với các đối tượng tĩnh
	//CSprite * _map_sprite;

	int _screen_height;							// chiều cao màn hình hiện tại
	int _screen_width;							// chiều rộng màn hình hiện tại
	int _m_width;								// chiều rộng của map 
	int _m_height;								// chiều cao của map
	CBox* _listObject;							// Các đối tượng trong map
	CQuadTree * _m_quad_object;					// quad tree
	
public:
	Map();
	~Map();

	void inital(LPDIRECT3DDEVICE9 d3ddev, LPWSTR backgroundPath,LPWSTR tilePathImg, LPWSTR tilePathTxt, 
		LPWSTR objectPath, int scrWidth, int scrHeight);
	void render(CDirectX * directX, D3DXVECTOR2 viewPort);
private:
	void readMapTileBackground(LPDIRECT3DDEVICE9 d3ddev, LPWSTR tilePathImg, LPWSTR tilePathTxt,
		int &mapWidth, int &mapHeight);
	void readMapObjects(LPWSTR mapInfoPath);
	
};

