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
	this->_deading_sprite = NULL;

	this->_is_deading = false;
}

CCharacter::~CCharacter()
{
	SAFE_DELETE(this->_walking_right);
	SAFE_DELETE(this->_walking_left);
	SAFE_DELETE(this->_walking_front);
	SAFE_DELETE(this->_walking_behind);
	SAFE_DELETE(this->_deading_sprite);
}

void CCharacter::inital(LPD3DXSPRITE spriteHandler)
{
	this->_walking_right = new CSprite(spriteHandler, BOMBER_RIGHT_IMG, BOMBER_WIDTH, BOMBER_HEIGHT_REAL, 3, 3);
	this->_walking_left = new CSprite(spriteHandler, BOMBER_LEFT_IMG, BOMBER_WIDTH, BOMBER_HEIGHT_REAL, 3, 3);
	this->_walking_front = new CSprite(spriteHandler, BOMBER_FRONT_IMG, BOMBER_WIDTH, BOMBER_HEIGHT_REAL, 3, 3);
	this->_walking_behind = new CSprite(spriteHandler, BOMBER_BEHIND_IMG, BOMBER_WIDTH, BOMBER_HEIGHT_REAL, 3, 3);
	this->_deading_sprite = new CSprite(spriteHandler, BOMBER_DEAD_IMG, BOMBER_WIDTH, BOMBER_HEIGHT_REAL, 5, 5);

	this->_last_time = GetTickCount();
	this->_allow_add_bomb = true;
	this->_bomb_added = 0;
}

void CCharacter::update(int deltaTime)
{
	DWORD now = GetTickCount();
	if ((now - this->_add_bomb_last_time) > BOMBER_ADD_BOMB_TIME){
		this->_allow_add_bomb = true;
		this->_bomb_added = 0;
	}

	UpdatePosition(deltaTime);
}

void CCharacter::draw(D3DXVECTOR2 view_port)
{
	DWORD now = GetTickCount();
	if ((now - this->_last_time) > (1000 / BOMBER_ANIMATE_RATE))
	{
		if (this->_is_deading){
			this->_deading_sprite->Next();
		}
		else{
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
		}
		_last_time = now;
	}

	if (this->_is_deading){
		this->_deading_sprite->Render(view_port, this->_position_x, this->_position_y + BOMBER_HEIGHT_HEAD);
	}
	else{
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
	this->_is_deading = true;
	this->_dead_start_time = GetTickCount();
}

void CCharacter::AddBomb(){
	if (this->_bomb_added <= 0){
		this->_bomb_added = 1;
		this->_allow_add_bomb = true;
		this->_add_bomb_last_time = GetTickCount();
		return;
	}
	if (this->_bomb_added > 0 && this->_bomb_added < 2){
		this->_bomb_added = 1;
		this->_allow_add_bomb = false;
		this->_add_bomb_last_time = GetTickCount();
		return;
	}

}

void CCharacter::UpdatePosition(int deltaTime)
{
	if (this->_is_deading || this->_is_dead)
	{
		DWORD now = GetTickCount();
		if (now - this->_dead_start_time > BOMBER_DEAD_TIME){
			this->_is_dead = false;
			this->_is_deading = false;
			this->setPosition(BOMBER_START_X, BOMBER_START_Y);
		}
		return;
	}

	if (this->_now_states == Move_States::Walking_Left)
	{
		this->_velocity_x = -(BOMBER_VELOCITY_X*deltaTime + BOMBER_VELOCITY_X*this->_boot_velocity);
		this->_velocity_y = 0.0f;
	}
	else if (this->_now_states == Move_States::Walking_Right)
	{
		this->_velocity_x = (BOMBER_VELOCITY_X*deltaTime + BOMBER_VELOCITY_X*this->_boot_velocity);
		this->_velocity_y = 0.0f;
	}
	else if (this->_now_states == Move_States::Walking_Front)
	{
		this->_velocity_x = 0.0f;
		this->_velocity_y = -(BOMBER_VELOCITY_Y*deltaTime + BOMBER_VELOCITY_Y*this->_boot_velocity);
	}
	else if (this->_now_states == Move_States::Walking_Behind)
	{
		this->_velocity_x = 0.0f;
		this->_velocity_y = (BOMBER_VELOCITY_Y*deltaTime + BOMBER_VELOCITY_Y*this->_boot_velocity);
	}
	else{
		//this->_velocity_x = 0.0f;
		//this->_velocity_y = 0.0f;
		return;
	}
	_position_x += _velocity_x;
	_position_y += _velocity_y;
	this->_boot_velocity -= deltaTime* BOMBER_BOOT_VELOCITY_TIME;
	if (this->_boot_velocity < 0.0f)
		this->_boot_velocity = 0.0f;
}

