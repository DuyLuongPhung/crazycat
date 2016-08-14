
#include <windows.h>
#include <d3d9.h>
#include <dinput.h>
#include "DirectX.h"
#include "Keyboard.h"
#include "Utils.h"
#include "Camera.h"

//
// Screen resolution
//
#define GAME_SCREEN_RESOLUTION_24   0
#define GAME_SCREEN_RESOLUTION_32   1

class CGame
{
protected:
	
	// directx divice
	CDirectX *_directXDivice;
	CKeyboard *_keyboardDevice;

	// camera
	CCamera *_Camera;

	// game information
	DWORD _deltaTime;		// Time between the last frame and current frame
	int _mode;				// Screen mode 
	int _isFullScreen;		// Is running in fullscreen mode?
	int _frameRate;			// frame rate
	int _screenWidth;
	int _screenHeight;
	int _depth;
	D3DFORMAT _backBufferFormat;
	int _mapMaxHeight;		// real position
	int _mapMaxWidth;		// real position

	// game window information 
	HINSTANCE _hInstance;	// Handle of the game instance
	HWND _hWnd;				// Handle of the Game Window
	LPWSTR _name;			// Name of game will be used as Window Class Name


	// Place holder for sub classes
	virtual void RenderFrame(LPDIRECT3DDEVICE9 d3ddv, int Delta);
	virtual void LoadResources(LPDIRECT3DDEVICE9 d3ddv);
	virtual void ProcessInput(LPDIRECT3DDEVICE9 d3ddv, int Delta);
	virtual void Update(int Delta);
	virtual void OnKeyDown(int KeyCode);
	virtual void OnKeyUp(int KeyCode);
private:
	void _InitWindow();		// Init game window
	void _RenderFrame();	// Render a single frame
	void _ProcessKeyBoard();
	void _SetScreenDimension(int Mode);
	void _Update();
public:
	CGame(HINSTANCE hInstance, LPWSTR Name, int Mode, int IsFullscreen, int FrameRate);
	~CGame();

	static LRESULT CALLBACK _WinProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

	void Init();
	void Run();
};