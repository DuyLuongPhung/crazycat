#include <dinput.h>

#define KEYBOARD_BUFFER_SIZE	1024
#define KEY_DOWN(code) ( IsKeyDown(code) )

class CKeyboard
{
public:
	HINSTANCE _hInstance;
	HWND _hWnd;				// Handle of the Game Window
	LPDIRECTINPUT8       _di;		// The DirectInput object         
	LPDIRECTINPUTDEVICE8 _Keyboard;	// The keyboard device 

	BYTE  _KeyStates[256];			// DirectInput keyboard state buffer 

	// Buffered keyboard data
	DIDEVICEOBJECTDATA _KeyEvents[KEYBOARD_BUFFER_SIZE];
public:
	CKeyboard(HWND hWnd, HINSTANCE hInstance);
	~CKeyboard();
	void InitKeyboard();
	int IsKeyDown(int KeyCode);
};

