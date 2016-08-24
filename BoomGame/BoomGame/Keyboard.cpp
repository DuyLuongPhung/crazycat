#include "Keyboard.h"
#include "Utils.h"


CKeyboard::CKeyboard(HWND hWnd, HINSTANCE hInstance)
{
	this->_di = NULL;
	this->_Keyboard = NULL;
	this->_hWnd = hWnd;
	this->_hInstance = hInstance;
}


CKeyboard::~CKeyboard()
{
	if (_Keyboard)
	{
		_Keyboard->Unacquire();
		_Keyboard->Release();
	}
	if (_di) _di->Release();
}

void CKeyboard::InitKeyboard()
{
	HRESULT
		hr = DirectInput8Create
		(
		_hInstance,
		DIRECTINPUT_VERSION,
		IID_IDirectInput8, (VOID**)&_di, NULL
		);

	// TO-DO: put in exception handling
	if (hr != DI_OK) return;

	trace(L"DirectInput has been created");

	hr = _di->CreateDevice(GUID_SysKeyboard, &_Keyboard, NULL);

	// TO-DO: put in exception handling
	if (hr != DI_OK) return;

	trace(L"DirectInput keyboard has been created");

	// Set the data format to "keyboard format" - a predefined data format 
	//
	// A data format specifies which controls on a device we
	// are interested in, and how they should be reported.
	//
	// This tells DirectInput that we will be passing an array
	// of 256 bytes to IDirectInputDevice::GetDeviceState.

	hr = _Keyboard->SetDataFormat(&c_dfDIKeyboard);

	trace(L"SetDataFormat for keyboard successfully");

	hr = _Keyboard->SetCooperativeLevel(_hWnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE);

	trace(L"SetCooperativeLevel for keyboard successfully");

	// IMPORTANT STEP TO USE BUFFERED DEVICE DATA!
	//
	// DirectInput uses unbuffered I/O (buffer size = 0) by default.
	// If you want to read buffered data, you need to set a nonzero
	// buffer size.
	//
	// Set the buffer size to DINPUT_BUFFERSIZE (defined above) elements.
	//
	// The buffer size is a DWORD property associated with the device.
	DIPROPDWORD dipdw;

	dipdw.diph.dwSize = sizeof(DIPROPDWORD);
	dipdw.diph.dwHeaderSize = sizeof(DIPROPHEADER);
	dipdw.diph.dwObj = 0;
	dipdw.diph.dwHow = DIPH_DEVICE;
	dipdw.dwData = KEYBOARD_BUFFER_SIZE; // Arbitary buffer size

	trace(L"SetProperty for keyboard successfully");

	hr = _Keyboard->SetProperty(DIPROP_BUFFERSIZE, &dipdw.diph);
	if (hr != DI_OK) return;

	hr = _Keyboard->Acquire();
	if (hr != DI_OK) return;

	trace(L"Keyboard has been acquired successfully");
}

int CKeyboard::IsKeyDown(int KeyCode)
{
	return (_KeyStates[KeyCode] & 0x80) > 0;
}
