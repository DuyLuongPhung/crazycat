#include <windows.h>
#include "CrazyCat.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	CrazyCat rec(hInstance, L"Crazy Cat", GAME_SCREEN_RESOLUTION_24, 0, 120);
	rec.Init();
	rec.Run();

	return 0;
}
