
#include <windows.h>
#include "Game.h"

CGame::CGame(HINSTANCE hInstance, LPWSTR Name, int Mode, int IsFullScreen, int FrameRate)
{
	this->_directXDivice = NULL;
	this->_keyboardDevice = NULL;
	this->_Camera = NULL;
	this->_mode = Mode;
	this->_SetScreenDimension(Mode);
	this->_name = Name;
	this->_isFullScreen = IsFullScreen;
	this->_frameRate = FrameRate;
	this->_hInstance = hInstance;
	this->_hWnd = NULL;
}

void CGame::_SetScreenDimension(int Mode)
{
	switch (Mode)
	{
	case GAME_SCREEN_RESOLUTION_24:
		_screenWidth = 480;
		_screenHeight = 380;
		_depth = 24;
		_backBufferFormat = D3DFMT_X8R8G8B8;
		break;

	case GAME_SCREEN_RESOLUTION_32:
		_screenWidth = 480;
		_screenHeight = 380;
		_depth = 32;
		_backBufferFormat = D3DFMT_X8R8G8B8;
		break;
	default:
		break;
	}
	trace(L"Set screen dimension is completed");
}

void CGame::_InitWindow()
{
	WNDCLASSEX wc;
	wc.cbSize = sizeof(WNDCLASSEX);

	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.hInstance = _hInstance;

	wc.lpfnWndProc = (WNDPROC)CGame::_WinProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hIcon = NULL;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = _name;
	wc.hIconSm = NULL;

	RegisterClassEx(&wc);

	DWORD style;
	if (_isFullScreen)
		style = WS_EX_TOPMOST | WS_VISIBLE | WS_POPUP;
	else
		style = WS_OVERLAPPEDWINDOW;

	_hWnd = CreateWindow(
						_name,
						_name,
						style,
						CW_USEDEFAULT,
						CW_USEDEFAULT,
						_screenWidth,
						_screenHeight,
						NULL,
						NULL,
						_hInstance,
						NULL);

	if (!_hWnd)
	{
		trace(L"[ERROR] Failed to created window!");
		DWORD ErrCode = GetLastError();
	}
	ShowWindow(_hWnd, SW_SHOWNORMAL);
	UpdateWindow(_hWnd);
}

void CGame::Init()
{
	_InitWindow();
	_directXDivice = new CDirectX(_hWnd, _isFullScreen, _screenWidth, _screenHeight, _depth, _backBufferFormat);
	_directXDivice->InitDirectX();
	_keyboardDevice = new CKeyboard(_hWnd, _hInstance);
	_keyboardDevice->InitKeyboard();
	_Camera = new CCamera(_screenWidth, _screenHeight);
	LoadResources(_directXDivice->getDevice());
}

void CGame::_ProcessKeyBoard()
{
	// Collect all key states first
	HRESULT hr =  _keyboardDevice->_Keyboard->GetDeviceState(sizeof(_keyboardDevice->_KeyStates), _keyboardDevice->_KeyStates);
	if (FAILED(hr))
		_keyboardDevice->_Keyboard->Acquire();
	if (_keyboardDevice->IsKeyDown(DIK_ESCAPE))
	{
		trace(L"Escape key pressed!");
		PostMessage(_hWnd, WM_QUIT, 0, 0);
	}
	// Collect all buffered events
	DWORD dwElements = KEYBOARD_BUFFER_SIZE;
	hr = _keyboardDevice->_Keyboard->GetDeviceData(sizeof(DIDEVICEOBJECTDATA), _keyboardDevice->_KeyEvents, &dwElements, 0);
	// Scan through all data, check if the key is pressed or released
	for (DWORD i = 0; i < dwElements; i++)
	{
		int KeyCode = _keyboardDevice->_KeyEvents[i].dwOfs;
		int KeyState = _keyboardDevice->_KeyEvents[i].dwData;
		if ((KeyState & 0x80) > 0)
			OnKeyDown(KeyCode);
		else
			OnKeyUp(KeyCode);
	}
}

void CGame::Update(int Delta)
{
	//
}

void CGame::_Update()
{
	Update(_deltaTime);
}

// Main game message loop
void CGame::Run()
{
	MSG msg;
	int done = 0;
	DWORD frame_start = GetTickCount();;

	DWORD tick_per_frame = 1000 / _frameRate;

	trace(L">>> Main game loop has been started");

	while (!done)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT) done = 1;

			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		DWORD now = GetTickCount();
		_deltaTime = now - frame_start;
		
		if (_deltaTime >= tick_per_frame)
		{
			
			frame_start = now;
			_Update();
			_RenderFrame();
			
		}
		else
			Sleep(tick_per_frame - _deltaTime);
		_ProcessKeyBoard();
		ProcessInput(_directXDivice->getDevice(), _deltaTime);
		
	}

	trace(L"Main game loop has ended");
}

void CGame::_RenderFrame()
{
	if (_directXDivice->getDevice()->BeginScene())
	{
		RenderFrame(_directXDivice->getDevice(), _deltaTime);
		_directXDivice->getDevice()->EndScene();
	}
	_directXDivice->getDevice()->Present(NULL, NULL, NULL, NULL);
}

void CGame::RenderFrame(LPDIRECT3DDEVICE9 d3ddv, int Delta)
{
	d3ddv->ColorFill(_directXDivice->getBackBuffer(), NULL, D3DCOLOR_XRGB(255, 255, 255));
}
void CGame::LoadResources(LPDIRECT3DDEVICE9 d3ddv) { }

void CGame::ProcessInput(LPDIRECT3DDEVICE9 d3ddv, int Delta) { }

CGame::~CGame()
{
	_directXDivice->~CDirectX();

}

void CGame::OnKeyUp(int KeyCode) { }
void CGame::OnKeyDown(int KeyCode) { }

LRESULT CALLBACK CGame::_WinProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}

	return 0;
}


