#include "Character.h"


CCharacter::CCharacter(int start_x, int start_y)
{
	this->_position_x = start_x;
	this->_position_y = start_y;
	this->_velocity_x = 0;
	this->_velocity_y = 0;
	this->_width = BOMBER_WIDTH;
	this->_height = BOMBER_HEIGHT;
	this->_now_states = Move_States::Walking_Left;
	this->_last_states = this->_now_states;

	this->_walking_right = NULL;
	this->_walking_left = NULL;
	this->_walking_front = NULL;
	this->_walking_behind = NULL;
}

CCharacter::~CCharacter()
{
	SAFE_DELETE(this->_walking_right);
	SAFE_DELETE(this->_walking_left);
	SAFE_DELETE(this->_walking_front);
	SAFE_DELETE(this->_walking_behind);
}

void CCharacter::inital(LPD3DXSPRITE spriteHandler)
{
	this->_walking_right = new CSprite(spriteHandler, WALK_RIGHT_IMG, BOMBER_WIDTH, BOMBER_HEIGHT_REAL, 3, 3);
	this->_walking_left = new CSprite(spriteHandler, WALK_LEFT_IMG, BOMBER_WIDTH, BOMBER_HEIGHT_REAL, 3, 3);
	this->_walking_front = new CSprite(spriteHandler, WALK_FRONT_IMG, BOMBER_WIDTH, BOMBER_HEIGHT_REAL, 3, 3);
	this->_walking_behind = new CSprite(spriteHandler, WALK_BEHIND_IMG, BOMBER_WIDTH, BOMBER_HEIGHT_REAL, 3, 3);
	

	this->_last_time = GetTickCount();
}

void CCharacter::update(int deltaTime)
{
	UpdatePosition(deltaTime);
}

void CCharacter::draw(D3DXVECTOR2 view_port)
{
	DWORD now = GetTickCount();
	if ((now - this->_last_time) > (1000 / ANIMATE_RATE))
	{
		switch (this->_now_states)
		{
		case Move_States::Walking_Right:
			this->_walking_right->Next();
			break;
		case Move_States::Walking_Left:
			this->_walking_left->Next();
			break;
		case Move_States::Walking_Front:
			this->_walking_front->Next();
			break;
		case Move_States::Walking_Behind:
			this->_walking_behind->Next();
			break;
		default:
			switch (this->_last_states)
			{
			case Move_States::Walking_Right:
				this->_walking_right->Reset();
				break;
			case Move_States::Walking_Left:
				this->_walking_left->Reset();
				break;
			case Move_States::Walking_Front:
				this->_walking_front->Reset();
				break;
			case Move_States::Walking_Behind:
				this->_walking_behind->Reset();
				break;
			default:
				this->_walking_right->Reset();
				break;
			}
			break;
		}
		_last_time = now;
	}

	switch (this->_now_states)
	{
	case Move_States::Walking_Right:
		this->_walking_right->Render(view_port, this->_position_x, this->_position_y + BOMBER_HEIGHT_HEAD);
		break;
	case Move_States::Walking_Left:
		this->_walking_left->Render(view_port, this->_position_x, this->_position_y + BOMBER_HEIGHT_HEAD);
		break;
	case Move_States::Walking_Front:
		this->_walking_front->Render(view_port, this->_position_x, this->_position_y + BOMBER_HEIGHT_HEAD);
		break;
	case Move_States::Walking_Behind:
		this->_walking_behind->Render(view_port, this->_position_x, this->_position_y + BOMBER_HEIGHT_HEAD);
		break;
	default:
		switch (this->_last_states)
		{
		case Move_States::Walking_Right:
			this->_walking_right->Render(view_port, this->_position_x, this->_position_y + BOMBER_HEIGHT_HEAD);
			break;
		case Move_States::Walking_Left:
			this->_walking_left->Render(view_port, this->_position_x, this->_position_y + BOMBER_HEIGHT_HEAD);
			break;
		case Move_States::Walking_Front:
			this->_walking_front->Render(view_port, this->_position_x, this->_position_y + BOMBER_HEIGHT_HEAD);
			break;
		case Move_States::Walking_Behind:
			this->_walking_behind->Render(view_port, this->_position_x, this->_position_y + BOMBER_HEIGHT_HEAD);
			break;
		default:
			this->_walking_right->Render(view_port, this->_position_x, this->_position_y + BOMBER_HEIGHT_HEAD);
			break;
		}
		break;
	}
	
}

void CCharacter::WalkingRight(){
	if (this->_now_states == Move_States::None)this->_last_states = Move_States::Walking_Right;
	else this->_last_states = this->_now_states;
	this->_now_states = Move_States::Walking_Right;

}

void CCharacter::WalkingLeft(){
	if (this->_now_states == Move_States::None)this->_last_states = Move_States::Walking_Left;
	else this->_last_states = this->_now_states;
	this->_now_states = Move_States::Walking_Left;
}

void CCharacter::WalkingFront(){
	if (this->_now_states == Move_States::None)this->_last_states = Move_States::Walking_Front;
	else this->_last_states = this->_now_states;
	this->_now_states = Move_States::Walking_Front;
}

void CCharacter::WalkingBehind(){
	if (this->_now_states == Move_States::None)this->_last_states = Move_States::Walking_Behind;
	else this->_last_states = this->_now_states;
	this->_now_states = Move_States::Walking_Behind;
}

void CCharacter::MoveNone(){
	if (this->_now_states != Move_States::None)this->_last_states = this->_now_states;
	this->_now_states = Move_States::None;
}

CBox CCharacter::getBounding()
{
	return CBox(this->_position_x, this->_position_y, this->_width, this->_height, this->_velocity_x, this->_velocity_y);
}

void CCharacter::Dead(){
	this->_is_dead = true;
	this->_deadDrawCount = 0;
}

void CCharacter::AddBomb(){
	this->_is_dead = true;
	this->_deadDrawCount = 0;
}

void CCharacter::UpdatePosition(int deltaTime)
{
	if (this->_now_states == Move_States::Walking_Left)
	{
		this->_velocity_x = -VELOCITY_X*deltaTime;
		this->_velocity_y = 0.0f;
	}
	else if (this->_now_states == Move_States::Walking_Right)
	{
		this->_velocity_x = VELOCITY_X*deltaTime;
		this->_velocity_y = 0.0f;
	}
	else if (this->_now_states == Move_States::Walking_Front)
	{
		this->_velocity_x = 0.0f;
		this->_velocity_y = -VELOCITY_Y*deltaTime;
	}
	else if (this->_now_states == Move_States::Walking_Behind)
	{
		this->_velocity_x = 0.0f;
		this->_velocity_y = VELOCITY_Y*deltaTime;
	}
	else{
		return;
	}
	_position_x += _velocity_x;
	_position_y += _velocity_y;
}

