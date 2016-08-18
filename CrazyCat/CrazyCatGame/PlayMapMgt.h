#pragma once

#include "CONST.h"
#include "Game.h"
#include "Sprite.h"
#include "Character.h"
#include "QuadNode.h"
#include "Camera.h"
#include "Map.h"
#include "Text.h"
#include "Collision.h"
#include <time.h>
#include <d3dx9.h>
#include "GameMenu.h"
#include "FireBang.h"
#include "HelpMgt.h"
#include "GameBar.h"

class PlayMapMgt
{
private:
	// Thông tin về character - bomber man
	float			_b_live;					// mạng còn lại
	int				_b_gold;					// số vàng đang có ~ số điểm
	DWORD			_b_map_times;				// thời gian còn lại để hoàn thành map
	int				_b_keys;					// số chìa khóa đã lấy được
	CCharacter *	_b_bomber_man;				// nhân vật: bomber man

	// Thông tin game
	//LPDIRECT3DSURFACE9	_background;				// Màn hình game 
	CCamera *		_b_camera;
	int				_screen_width;		
	int				_screen_height;

	// Thông tin về map
	CCollision*			_collision;					// dùng để xét va chạm
	std::vector<Map*>	_list_map;
	int					_current_map;
	std::vector<GameBar*> _list_gamebar;
	// 
public:
	PlayMapMgt();
	~PlayMapMgt();

	void			resetCurrentMap();
	void			nextMap();
	void			inital(CDirectX * directX, int screenWidth, int screenHeight);
	void			update(int deltaTime, CDirectX * directX);
	void			draw(CDirectX * directX);


	void			addBomb(LPD3DXSPRITE spriteHandler);
	void			bomberRunRight();
	void			bomberRunLeft();
	void			bomberRunFront();
	void			bomberRunBehind();
	void			bomberMoveNone();
};

