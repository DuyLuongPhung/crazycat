#pragma once
#ifndef CTEXT_H
#define CTEXT_H
#include<Windows.h>
#include <stdio.h>
#include <stdlib.h>
#include<d3d9.h>
#include<d3dx9core.h>


// Font alignment
enum FONTALIGNMENT { FA_LEFT, FA_CENTER, FA_RIGHT, FA_TOPRIGHT, FA_TOPLEFT, FA_BOTTOMRIGHT, FA_BOTTOMLEFT };

#define SAFE_RELEASE(x) if( x ) { (x)->Release(); (x) = NULL; }
#define SAFE_DELETE(x) if( x ) { delete(x); (x) = NULL; }
#define SAFE_DELETE_ARRAY(x) if( x ) { delete [] (x); (x) = NULL; }

class CText
{
public:
	CText();
	~CText() { Release(); }

	BOOL Initialize(LPDIRECT3DDEVICE9 pd3ddev, LPWSTR fontName, int size, BOOL bold = FALSE,
		BOOL italic = FALSE);
	void Print(LPSTR text, int xPosition, int yPosition, DWORD color, LPD3DXSPRITE sprite = NULL,
		int textBoxWidth = 0, int textBoxHeight = 0, FONTALIGNMENT alignment = FA_LEFT);
	void OnLostDevice();
	void OnResetDevice();
	void Release();
private:
	LPD3DXFONT m_pFont;
};

#endif