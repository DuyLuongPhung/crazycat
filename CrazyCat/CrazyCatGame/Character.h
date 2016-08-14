
#include "Sprite.h"
#include "Camera.h"
#include "Collision.h"
#include "CONST.h"
#include "DynamicGameObject.h"

enum Character_Mode{
	Walk,
	Run,
	Slide,
	Jump,
	Dead,
	Fall,
	Hurt,
	Idle
};

enum Move_States{
	Walking_Left,
	Walking_Right,
	None
};

class CCharacter : public CDynamicGameObject
{
public:
	//int _position_x;		// tọa độ x
	//int _position_y;		// tọa độ y
	//float _velocity_x;		// vận tốc di chuyển theo phương x
	//float _velocity_y;		// vận tốc di chuyển theo phương y
	float _last_velocity_x;		// vận tốc di chuyển theo phương x ở frame trước - hướng di chuyển theo phương x
	Character_Mode _mode;		// kiểu nhân vật hiện tại
	int _width_body;		// chiều rộng khung cơ thể 
	int _height_body;		// chiều dài khung cơ thể	
	DWORD _last_time;		
	int _mapWidth;
	int _mapHeight;

	bool _is_dead;			// đã chết
	int _deadDrawCount;		// đếm số lần vẽ sprite khi chết
	bool _is_hurt;			// đang bị thương
	int _hurtDrawCount;		// đếm số lần vẽ sprite khi bị thương
	bool _isFall;			// đang rơi
	bool _isSlide;			// xác định đang trượt hay ko
	int _slideTime;			// khoảng thời gian đã trượt
	bool _allowSlide;		// xác định xem có cho trượt hay không
	int _slideDelay;		// thời gian giữa 2 lần trượt
	bool _isDelaySlide;		// kiểm tra xem thời điểm tính thời gian delay


	Move_States _now_states;
	Character_Mode _last_mode;

	// sprite 
	CSprite *_walking_right;
	CSprite *_slide_right;
	CSprite *_run_right;
	CSprite *_dead_right;
	CSprite *_hurt_right;
	CSprite *_fall_right;
	CSprite *_jump_right;

	// Nhảy
	bool _allow_jump;		// cho phép nhảy hay không
	bool _is_jumping;
	bool _is_double_jump;
	bool _is_falling;	// đang rơi xuống
	int _start_jump_y;	// vị trí bắt đầu nhảy - y
	int _jump_sprite;
	int _fall_sprite;

	

public:
	CCharacter(LPD3DXSPRITE SpriteHandler, int start_x, int start_y, int mapWidth, int mapHeight);
	~CCharacter();
	void LoadResource(LPD3DXSPRITE SpriteHandler);

	// các hành động của mario
	void Jumping(int deltaTime);
	void Walking(int deltaTime);
	void Sliding(int deltaTime, float velocity_x);
	void ChangingDirection(Move_States states);		// Thay đổi hướng di chuyển: trái - phải

	void WalkingLeft();
	void UpdatePosition(int deltaTime);
	void UpdatePosition_X(int deltaTime);
	void UpdatePosition_Y(int deltaTime);

	
	void RenderCharacter(D3DXVECTOR2 viewPort);

	void dead();
	CBox getPartion();

	virtual void		inital();
	virtual void		draw(D3DXVECTOR2 view_port);
	virtual void		update();

private:
	void UpdateCharacterMode(Character_Mode mode);
};

