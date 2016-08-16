
#include "Sprite.h"
#include "Camera.h"
#include "Collision.h"
#include "CONST.h"
#include "DynamicGameObject.h"



enum Move_States{
	Walking_Left = 0,
	Walking_Right = 1,
	Walking_Front = 2,
	Walking_Behind = 3,
	None = 4
};

class CCharacter : public CDynamicGameObject
{
public:
	DWORD _last_time;		
	int _mapWidth;
	int _mapHeight;

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
	CCharacter(int start_x, int start_y, int mapWidth, int mapHeight);
	~CCharacter();

	// các hành động của bomber
	void WalkingRight();
	void WalkingLeft();
	void WalkingFront();
	void WalkingBehind();
	void MoveNone();

	void dead();

	virtual CBox getBounding();
	virtual void inital(LPD3DXSPRITE spriteHandler);
	virtual void draw(D3DXVECTOR2 view_port);
	virtual void update(int deltaTime);

private:
	void UpdatePosition(int deltaTime);
};

