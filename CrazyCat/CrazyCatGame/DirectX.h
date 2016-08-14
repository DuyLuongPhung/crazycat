#ifndef DirectX_H
#define DirectX_H

#include <d3dx9.h>
#include <d3d9.h>

class CDirectX
{
private:
	HWND _hWnd;
	LPDIRECT3D9 _d3d;
	LPDIRECT3DDEVICE9 _d3ddev;
	LPDIRECT3DSURFACE9 _backBuffer;
	int _isFullScreen;
	int _screenWidth;
	int _screenHeight;
	int _depth;
	D3DFORMAT _backBufferFormat;
	LPD3DXSPRITE _spriteHandler;
	LPD3DXFONT _pFont;

public:
	CDirectX(HWND hWnd, int isFullScreen, int screenWidth, int screenHeight, int depth, D3DFORMAT backBufferFormat);
	~CDirectX();
	int InitDirectX();
	int InitDirect3D();
	//int InitDirectSound();
	//int InitDirectInput();

	LPDIRECT3DSURFACE9 getBackBuffer();
	LPDIRECT3DDEVICE9 getDevice();
	LPD3DXSPRITE getSpriteHandler();

	//Utilities
	void DrawString(int x, int y, DWORD color, LPCWSTR text);
	void RenderSurface(LPDIRECT3DSURFACE9 surface);
};

LPDIRECT3DSURFACE9 LoadSurfaceFromFile(LPDIRECT3DDEVICE9 d3ddev, LPWSTR filePath, D3DCOLOR transparentColor);
LPDIRECT3DTEXTURE9 LoadTextureFromFile(LPDIRECT3DDEVICE9 d3ddev, LPWSTR filePath, D3DCOLOR transparentColor);

#endif