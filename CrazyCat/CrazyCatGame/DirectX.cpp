
#include "DirectX.h"

CDirectX::CDirectX(HWND hWnd, int isFullScreen, int screenWidth, int screenHeight, int depth, D3DFORMAT backBufferFormat)
{
	this->_d3d = NULL;
	this->_d3ddev = NULL;
	this->_backBuffer = NULL;
	this->_spriteHandler = NULL;
	this->_hWnd = hWnd;
	this->_isFullScreen = isFullScreen;
	this->_screenWidth = screenWidth;
	this->_screenHeight = screenHeight;
	this->_depth = depth;
	this->_backBufferFormat = backBufferFormat;
	
}

CDirectX::~CDirectX(void)
{
	if (_d3ddev != NULL)
		_d3ddev->Release();

	if (_d3d != NULL)
		_d3d->Release();
}

int CDirectX::InitDirectX()
{
	InitDirect3D();
	//InitDirectInput();
	//InitDirectSound();
	return 1;
}

int CDirectX::InitDirect3D()
{
	//Initialize the Direct3D
	_d3d = Direct3DCreate9(D3D_SDK_VERSION);

	if (_d3d == NULL)
	{
		MessageBox(NULL, L"Error Initialize Direct3D", L"Error", MB_OK);
		return 0;
	}

	D3DPRESENT_PARAMETERS d3dpp;

	ZeroMemory(&d3dpp, sizeof(d3dpp));
	d3dpp.Windowed = !false;
	d3dpp.SwapEffect = D3DSWAPEFFECT_COPY;
	d3dpp.BackBufferFormat = D3DFMT_X8R8G8B8;
	d3dpp.hDeviceWindow = _hWnd;
	d3dpp.BackBufferCount = 1;
	d3dpp.BackBufferWidth = _screenWidth;
	d3dpp.BackBufferHeight = _screenHeight;

	_d3d->CreateDevice(
		D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		_hWnd,
		D3DCREATE_SOFTWARE_VERTEXPROCESSING,
		&d3dpp,
		&_d3ddev);

	if (_d3ddev == NULL)
	{
		MessageBox(NULL, L"Error Creating D3Ddevice", L"Error", MB_OK);
		return 0;
	}
	_backBuffer = NULL;
	_d3ddev->GetBackBuffer(0, 0, D3DBACKBUFFER_TYPE_MONO, &_backBuffer);

	//Initialize Sprite Handler
	HRESULT result = D3DXCreateSprite(_d3ddev, &_spriteHandler);
	if (result != D3D_OK)
	{
		MessageBox(NULL, L"Error Creating D3DXSprite!", L"Error", MB_OK);
		return 0;
	}
	D3DXCreateFont(_d3ddev, 50, 0, FW_BOLD, 1, 0, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, 
		DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, L"Arial", &_pFont);
	return 1;
}

void CDirectX::DrawString(int x, int y, DWORD color, LPCWSTR text)
{
	RECT FontPos = { x, y, x + 120, y + 16 };
	_pFont->DrawText(NULL, text, -1, &FontPos, DT_NOCLIP, color);
}

LPDIRECT3DSURFACE9 CDirectX::getBackBuffer()
{
	return _backBuffer;
}

LPDIRECT3DDEVICE9 CDirectX::getDevice()
{
	return _d3ddev;
}

LPD3DXSPRITE CDirectX::getSpriteHandler()
{
	return _spriteHandler;
}

LPDIRECT3DSURFACE9 LoadSurfaceFromFile(LPDIRECT3DDEVICE9 d3ddev, LPWSTR filePath, D3DCOLOR transparentColor)
{
	HRESULT result;
	LPDIRECT3DSURFACE9 surface = NULL;
	D3DXIMAGE_INFO info;

	result = D3DXGetImageInfoFromFile(filePath, &info);
	if (result != D3D_OK)
		return NULL;

	result = d3ddev->CreateOffscreenPlainSurface(info.Width, info.Height, D3DFMT_X8R8G8B8, D3DPOOL_DEFAULT, &surface, NULL);
	if (result != D3D_OK)
		return NULL;
	result = D3DXLoadSurfaceFromFile(surface, NULL, NULL, filePath, NULL, D3DX_DEFAULT, transparentColor, &info);
	if (result != D3D_OK)
		return NULL;

	return surface;
}

LPDIRECT3DTEXTURE9 LoadTextureFromFile(LPDIRECT3DDEVICE9 d3ddev, LPWSTR filePath, D3DCOLOR transparentColor)
{
	LPDIRECT3DTEXTURE9 texture = NULL;
	D3DXIMAGE_INFO info;
	HRESULT result;

	result = D3DXGetImageInfoFromFile(filePath, &info);
	if (result != D3D_OK)
	{
		MessageBox(NULL, L"Can not get image Info!", L"Error", MB_OK);
		return NULL;
	}

	result = D3DXCreateTextureFromFileEx(d3ddev,
		filePath,
		info.Width,
		info.Height,
		1,
		D3DPOOL_DEFAULT,
		D3DFMT_UNKNOWN,
		D3DPOOL_DEFAULT,
		D3DX_DEFAULT,
		D3DX_DEFAULT,
		transparentColor,
		&info,
		NULL,
		&texture);
	if (result != D3D_OK)
	{
		MessageBox(NULL, L"Load texture error!", L"Error", MB_OK);
		return NULL;
	}
	return texture;
}

void CDirectX::RenderSurface(LPDIRECT3DSURFACE9 surface)
{
	_d3ddev->GetBackBuffer(0, 0, D3DBACKBUFFER_TYPE_MONO, &_backBuffer);
	_d3ddev->StretchRect(surface, NULL, this->_backBuffer, NULL, D3DTEXF_NONE);
}
