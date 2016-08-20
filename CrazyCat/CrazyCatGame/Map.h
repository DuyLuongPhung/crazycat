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
#include "ResourceManager.h"

#include "Brick.h"
#include "TileBox.h"
#include "GiftBox.h"
#include "DoorObject.h"


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
private:
	LPDIRECT3DSURFACE9 _m_background;			// màn hình nền

	char *		_m_title;						// Tiêu đề map
	int			_m_width;						// chiều rộng của map 
	int			_m_height;						// chiều cao của map
	DWORD		_m_maximum_times;				// thời gian tối đa cho map này

	// Thông tin sẽ map được dùng để khởi tạo 
	LPWSTR		_m_tile_img;					// file ảnh nền gốc			
	LPWSTR		_m_tile_txt;					// file thông tin ma trận để load ảnh nền
	LPWSTR		_m_object_info;					// file thông tin map: thông tin cơ bản, quadtree, objects

	int			_m_keys_need;
public:
	std::vector<CGameObject*> _list_objects;	// danh sách các objects trong map

public:
	Map(char* mapTitle, LPWSTR tilePathImg, LPWSTR tilePathTxt, LPWSTR objectPath, DWORD mapTimes, int needkeys);
	~Map();

	int				getNeedKeys(){ return this->_m_keys_need; }
	DWORD			getMaximumTimes(){ return this->_m_maximum_times; }
	int				getMapWidth(){ return this->_m_width; }
	int				getMapHeight(){ return this->_m_height; }
	char*			getMapTitle(){ return this->_m_title; }
	void			addNewObjects(CGameObject * insertObject);

	void			inital(LPDIRECT3DDEVICE9 d3ddev, ResourceManager * resourMgt);
	void			update(int deltaTime, D3DXVECTOR2 nextViewPort);
	void			draw(CDirectX * directX, D3DXVECTOR2 viewPort, int gamesceneWidth, int gamesceneHeight);

private:
	void			readMapTileBackground(LPDIRECT3DDEVICE9 d3ddev, LPWSTR tilePathImg, LPWSTR tilePathTxt,
					int &mapWidth, int &mapHeight);
	void			readMapObjects(LPWSTR mapInfoPath, ResourceManager * resourMgt);

};

