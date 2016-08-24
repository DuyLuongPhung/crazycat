#pragma once

/** 
* Dùng cho những sprite có khả năng phải load lại nhiều lần
* Các đối tượng box
*  Bom, đạn
* Các đối tượng khác trong game trừ: nhân vật, map
*/

#include "DirectX.h"
#include "CONST.h"
#include "SpriteResource.h"
#include  <vector>

class ResourceManager
{
private:
	std::vector<SpriteResource*> _list_sprites;
public:
	ResourceManager();
	~ResourceManager();

	void					inital(CDirectX * directx);
	CSprite*				getSpriteWithID(int id);
};

