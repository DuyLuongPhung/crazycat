
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
public:
	DWORD _last_time;	

	bool _is_dead;			// đã chết
	int _deadDrawCount;		// đếm số lần vẽ sprite khi chết

	Move_States _now_states;
	Move_States _last_states;

	// sprite 
	CSprite *_walking_right;
	CSprite *_walking_left;
	CSprite *_walking_front;
	CSprite *_walking_behind;

	


public:
	CCharacter(int start_x, int start_y);
	~CCharacter();

	// các hành động của bomber
	void WalkingRight();
	void WalkingLeft();
	void WalkingFront();
	void WalkingBehind();
	void MoveNone();

	void Dead();
	void AddBomb();

	virtual CBox getBounding();
	virtual void inital(LPD3DXSPRITE spriteHandler);
	virtual void draw(D3DXVECTOR2 view_port);
	virtual void update(int deltaTime);

private:
	void UpdatePosition(int deltaTime);
};

#endif
