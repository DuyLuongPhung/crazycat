#include "Sprite.h"
//#include "trace.h"
#include <d3dx9.h>
#include "Camera.h"

CSprite::CSprite(LPD3DXSPRITE SpriteHandler, LPWSTR FilePath, int Width, int Height, int Count, int SpritePerRow)
{
	D3DXIMAGE_INFO info;
	HRESULT result;

	_Image = NULL;
	_SpriteHandler = SpriteHandler;

	_Width = Width;
	_Height = Height;
	_Count = Count;
	_SpritePerRow = SpritePerRow;
	_Index = 0;

	result = D3DXGetImageInfoFromFile(FilePath, &info);
	if (result != D3D_OK)
	{
		//trace(L"[ERROR] Failed to get information from image file '%s'", FilePath);
		return;
	}

	LPDIRECT3DDEVICE9 d3ddv;
	SpriteHandler->GetDevice(&d3ddv);

	result = D3DXCreateTextureFromFileEx(
		d3ddv,
		FilePath,
		info.Width,
		info.Height,
		1,
		D3DUSAGE_DYNAMIC,
		D3DFMT_UNKNOWN,
		D3DPOOL_DEFAULT,
		D3DX_DEFAULT,
		D3DX_DEFAULT,
		D3DCOLOR_XRGB(255, 255, 255),
		&info,
		NULL,
		&_Image);

	if (result != D3D_OK)
	{
		//trace(L"[ERROR] Failed to create texture from file '%s'", FilePath);
		return;
	}
}

CSprite::CSprite(LPD3DXSPRITE SpriteHandler, LPWSTR FilePath, int Width, int Height, int Count, int SpritePerRow, D3DCOLOR transparentColor)
{
	D3DXIMAGE_INFO info;
	HRESULT result;

	_Image = NULL;
	_SpriteHandler = SpriteHandler;

	_Width = Width;
	_Height = Height;
	_Count = Count;
	_SpritePerRow = SpritePerRow;
	_Index = 0;

	result = D3DXGetImageInfoFromFile(FilePath, &info);
	if (result != D3D_OK)
	{
		//trace(L"[ERROR] Failed to get information from image file '%s'", FilePath);
		return;
	}

	LPDIRECT3DDEVICE9 d3ddv;
	SpriteHandler->GetDevice(&d3ddv);

	result = D3DXCreateTextureFromFileEx(
		d3ddv,
		FilePath,
		info.Width,
		info.Height,
		1,
		D3DUSAGE_DYNAMIC,
		D3DFMT_UNKNOWN,
		D3DPOOL_DEFAULT,
		D3DX_DEFAULT,
		D3DX_DEFAULT,
		transparentColor,
		&info,
		NULL,
		&_Image);

	if (result != D3D_OK)
	{
		//trace(L"[ERROR] Failed to create texture from file '%s'", FilePath);
		return;
	}
}

void CSprite::Render(D3DXVECTOR2 viewPort, int X, int Y)
{
	RECT srect;

	D3DXVECTOR2 point(X, Y);

	CCamera::Transform(viewPort, &point);

	srect.left = (_Index % _SpritePerRow)*(_Width);
	srect.top = (_Index / _SpritePerRow)*(_Height);
	srect.right = srect.left + _Width;
	srect.bottom = srect.top + _Height;

	D3DXVECTOR3 position((float)point.x, (float)point.y, 0);

	_SpriteHandler->Draw(
		_Image,
		&srect,
		NULL,
		&position,
		D3DCOLOR_XRGB(255, 255, 255)
		);
}

void CSprite::Render(int X, int Y)
{
	RECT srect;

	D3DXVECTOR2 point(X, Y);

	srect.left = (_Index % _SpritePerRow)*(_Width);
	srect.top = (_Index / _SpritePerRow)*(_Height);
	srect.right = srect.left + _Width;
	srect.bottom = srect.top + _Height;

	D3DXVECTOR3 position((float)point.x, (float)point.y, 0);

	_SpriteHandler->Draw(
		_Image,
		&srect,
		NULL,
		&position,
		D3DCOLOR_XRGB(255, 255, 255)
		);
}

void CSprite::Next()
{
	_Index = (_Index + 1) % _Count;
}

void CSprite::Reset()
{
	_Index = 0;
}

void CSprite::Index(int index)
{
	if (index >= 0 && index <= _Count)
		_Index = index;
}

int CSprite::getWidth(){
	return this->_Width;
}

int CSprite::getHeight(){
	return this->_Height;
}


CSprite::~CSprite()
{
	_Image->Release();
}
