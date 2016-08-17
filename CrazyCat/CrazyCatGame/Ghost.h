#pragma once
#include "Sprite.h"
#include "Camera.h"
#include "Collision.h"
#include "CONST.h"
#include "DynamicGameObject.h"


class Ghost : public CDynamicGameObject
{
public:
	DWORD _last_time;
	int _mapWidth;
	int _mapHeight;

	Move_States _now_states;
	Move_States _last_states;

	// sprite 
	CSprite *_walking_right;
	CSprite *_walking_left;
	CSprite *_walking_front;
	CSprite *_walking_behind;

	int ** _g_road_matrix;			// ma trận cho khung hoạt động của ghost 
									// sử dụng để tìm đường đi đến character
	int _current_row;
	int _current_column;

	int _des_row;
	int _des_column;

public:
	Ghost(int start_x, int start_y, int mapWidth, int mapHeight);
	~Ghost();

	virtual CBox getBounding();
	virtual void inital(LPD3DXSPRITE spriteHandler);
	virtual void draw(D3DXVECTOR2 view_port);
	virtual void update(int deltaTime);

private:
	void UpdatePosition(int deltaTime);
	void WalkingRight();
	void WalkingLeft();
	void WalkingFront();
	void WalkingBehind();
	void MoveNone();
};

