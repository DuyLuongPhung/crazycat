#pragma once

#ifndef CRAZYCAT_H
#define CRAZYCAT_H

#include "CONST.h"
#include "Game.h"
#include "Sprite.h"
#include "Character.h"
#include "QuadNode.h"
#include "Camera.h"
#include "Map.h"
#include "Text.h"
#include "Collision.h"
#include <time.h>
#include <d3dx9.h>
#include "GameMenu.h"
#include "FireBang.h"


class CrazyCat : public CGame
{
public:

	// các thông tin logic của nhân vật
	float	_b_live;					// mạng còn lại
	int		_b_gold;					// số vàng đang có ~ số điểm
	float	_b_map_times;				// thời gian còn lại để hoàn thành map

	CCharacter *_character;				// nhân vật: main cat
	LPDIRECT3DSURFACE9 _background;		// background
	LPDIRECT3DSURFACE9 _game_bar;		// background
	RECT _background_partition;			// khung background ứng với viewport hiện tại
	Map *_map;
	CText *_textPrint;
	CCollision * _collision;
	CDynamicGameObject * _tile_object;


	char * lalbelTest;
	std::vector<Bomb*> _list_bombs;
	std::vector<FireBang*> _list_fireBang;

	GameMenu * _menu;

public:
	CrazyCat(HINSTANCE hInstance, LPWSTR name, int mode, int is_fullscreen, int frame_rate);
	~CrazyCat();

protected:
	virtual void RenderFrame(LPDIRECT3DDEVICE9 d3ddv, int Delta);
	virtual void ProcessInput(LPDIRECT3DDEVICE9 d3ddv, int Delta);
	virtual void LoadResources(LPDIRECT3DDEVICE9 d3ddv);
	virtual void Update(int Delta);

	virtual void OnKeyDown(int KeyCode);
	virtual void OnKeyUp(int KeyCode);

private:
	int LoadBackground(LPWSTR fileText, LPWSTR fileImage, int rows, int columns, int tiles, int tileWidth, int tileHeight);
	void UpdateCharacter(int Delta);
	void UpdateMap();
	void AddBomb();
};

#endif
