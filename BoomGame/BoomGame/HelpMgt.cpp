#include "HelpMgt.h"


HelpMgt::HelpMgt(LPDIRECT3DDEVICE9 d3ddev, LPWSTR pathImg)
{
	this->_m_background = LoadSurfaceFromFile(d3ddev, pathImg, NULL);
}


HelpMgt::~HelpMgt()
{
}

void HelpMgt::draw(CDirectX *d3ddev){

	d3ddev->getDevice()->ColorFill(d3ddev->getBackBuffer(), NULL, D3DCOLOR_ARGB(0, 245, 245, 245));

	RECT srect;
	srect.left = 0;
	srect.right = 575;
	srect.top = 0;
	srect.bottom = 477;


	d3ddev->getDevice()->StretchRect(this->_m_background, NULL, d3ddev->getBackBuffer(), NULL, D3DTEXF_NONE);
}
