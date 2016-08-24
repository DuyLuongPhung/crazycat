
#ifndef CHARACTER_H
#define CHARACTER_H

#include "Sprite.h"
#include "Camera.h"
#include "Collision.h"
#include "CONST.h"
#include "DynamicGameObject.h"
#include "Bomb.h"


class CCharacter : public CDynamicGameObject
{
private:
	DWORD _last_time;	

	bool _is_dead;			// đã chết
	DWORD _dead_start_time;
	Move_States _now_states;
	Move_States _last_states;

	// sprite 
	CSprite *_walking_right;
	CSprite *_walking_left;
	CSprite *_walking_front;
	CSprite *_walking_behind;
	CSprite * _deading_sprite;

	float _boot_velocity;

	bool _is_deading;
	bool _allow_add_bomb;
	int _bomb_added;
	DWORD _add_bomb_last_time;


public:
	CCharacter(int start_x, int start_y);
	~CCharacter();

	// các hành động của bomber
	void WalkingRight();
	void WalkingLeft();
	void WalkingFront();
	void WalkingBehind();
	void MoveNone();

	bool isDeading(){ return this->_is_deading; }
	bool isAllowAddBomb(){ return this->_allow_add_bomb; }

	void Dead();
	void AddBomb();
	void BootVelocity(){ this->_boot_velocity = BOMBER_BOOT_VELOCITY;}

	virtual CBox getBounding();
	virtual void inital(LPD3DXSPRITE spriteHandler);
	virtual void draw(D3DXVECTOR2 view_port);
	virtual void update(int deltaTime);

private:
	void UpdatePosition(int deltaTime);
};

#endif
