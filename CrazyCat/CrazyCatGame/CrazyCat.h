﻿#pragma once

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

class CrazyCat : public CGame
{
public:
	CCharacter *_character;				// nhân vật: main cat
	LPDIRECT3DSURFACE9 _background;		// background
	RECT _background_partition;			// khung background ứng với viewport hiện tại
	Map *_map;
	CText *_textPrint;
	CCollision * _collision;
	CDynamicGameObject * _tile_object;


	char * lalbelTest;

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
};

#endif