#pragma once
#define _CRT_SECURE_NO_WARNINGS
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
#include "FireBang.h"
#include "HelpMgt.h"
#include "GameBar.h"
#include "ResourceManager.h"
#include "TimeGameBar.h"
#include "KeyGameBar.h"
#include "SoundManager.h"

class PlayMapMgt
{
private:
	// Thông tin về character - bomber man
	float			_b_live;					// mạng còn lại
	int				_b_gold;					// số vàng đang có ~ số điểm
	long			_b_map_times;				// thời gian còn lại để hoàn thành map
	int				_b_keys;					// số chìa khóa đã lấy được
	CCharacter *	_b_bomber_man;				// nhân vật: bomber man
	bool			_super_boom;
	int				_super_bomb_count;

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
	ResourceManager * _resourceMgt;

	// bắt đầu map và game over
	CText	* _gb_text_mgt;
	LPDIRECT3DSURFACE9	_game_over_background;				// Màn hình game 
	LPDIRECT3DSURFACE9	_start_map_background;				// Màn hình game 
	bool _is_game_over;
	bool _is_game_starting;
	DWORD _time_waiting_start;
	DWORD _time_waiting_gameover;

	bool _return_menu;
	bool _play_sound_bg;
	bool _fisrt_update_map;
	// 
public:
	PlayMapMgt(ResourceManager * resourceMgt);
	~PlayMapMgt();

	void			setPlayBackground(bool isPlay){ this->_play_sound_bg = isPlay; }

	void			resetCurrentMap();
	bool			isWaiting(){ return (this->_is_game_starting || this->_is_game_over); }
	void			nextMap();
	void			defaultMap();
	void			gameOver();
	bool			isReturnMenu(){ return this->_return_menu; }

	void			inital(CDirectX * directX, int screenWidth, int screenHeight);
	void			update(int deltaTime, CDirectX * directX);
	void			draw(CDirectX * directX);


	void			addBomb(LPD3DXSPRITE spriteHandler);
	void			bomberRunRight();
	void			bomberRunLeft();
	void			bomberRunFront();
	void			bomberRunBehind();
	void			bomberMoveNone();

	

private:
	void			activedNormalBomb(int index);
	void			activedSuperBomb(int index);

	void			startMap();
	void			bomberDied();
};

