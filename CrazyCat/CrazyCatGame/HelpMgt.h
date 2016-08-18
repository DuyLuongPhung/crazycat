#pragma once
#include "Sprite.h"
#include "DirectX.h"
class HelpMgt
{
private:
	LPDIRECT3DSURFACE9 _m_background;			// màn hình nền
public:
	HelpMgt(LPDIRECT3DDEVICE9 d3ddev, LPWSTR pathImg);
	~HelpMgt();

	void draw(CDirectX *d3ddev);

};

