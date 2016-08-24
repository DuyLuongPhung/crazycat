#include "Ghost.h"


Ghost::Ghost(int start_x, int start_y, int mapWidth, int mapHeight)
{
	this->_position_x = start_x;
	this->_position_y = start_y;
	this->_velocity_x = 0;
	this->_velocity_y = 0;
	this->_width = BOMBER_WIDTH;
	this->_height = BOMBER_HEIGHT;
	this->_mapHeight = mapHeight;
	this->_mapWidth = mapWidth;
	this->_now_states = Move_States::Walking_Left;
	this->_last_states = this->_now_states;

	this->_walking_right = NULL;
	this->_walking_left = NULL;
	this->_walking_front = NULL;
	this->_walking_behind = NULL;

	this->_g_road_matrix = new int*[12];
	for (int i = 0; i < 12; i++){
		this->_g_road_matrix[i] = new int[12];
	}
	this->_g_road_matrix[0] = new int[]{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
	this->_g_road_matrix[1] = new int[]{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
	this->_g_road_matrix[2] = new int[]{0, 0, 1, 1, 1, 0, 1, 1, 1, 1, 0, 0};
	this->_g_road_matrix[3] = new int[]{0, 0, 1, 0, 1, 1, 1, 0, 1, 1, 0, 0};
	this->_g_road_matrix[4] = new int[]{0, 0, 1, 1, 1, 0, 1, 1, 1, 0, 0, 0};
	this->_g_road_matrix[5] = new int[]{0, 0, 1, 0, 1, 1, 1, 0, 1, 1, 0, 0};
	this->_g_road_matrix[6] = new int[]{0, 0, 1, 1, 1, 0, 1, 1, 1, 0, 0, 0};
	this->_g_road_matrix[7] = new int[]{0, 0, 1, 0, 1, 1, 1, 0, 1, 1, 0, 0};
	this->_g_road_matrix[8] = new int[]{0, 0, 1, 1, 1, 0, 1, 1, 1, 0, 0, 0};
	this->_g_road_matrix[9] = new int[]{0, 0, 1, 0, 1, 1, 1, 0, 1, 1, 0, 0};
	this->_g_road_matrix[10] = new int[]{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
	this->_g_road_matrix[11] = new int[]{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
	this->_current_row = 9;
	this->_current_column = 9;

	this->_des_row = 2;
	this->_des_column = 2;
}

Ghost::~Ghost()
{
	/*SAFE_DELETE(this->_walking_right);
	SAFE_DELETE(this->_walking_left);
	SAFE_DELETE(this->_walking_front);
	SAFE_DELETE(this->_walking_behind);*/
}

void Ghost::inital(LPD3DXSPRITE spriteHandler)
{
	/*this->_walking_right = new CSprite(spriteHandler, WALK_RIGHT_IMG, BOMBER_WIDTH, BOMBER_HEIGHT_REAL, 3, 3);
	this->_walking_left = new CSprite(spriteHandler, WALK_LEFT_IMG, BOMBER_WIDTH, BOMBER_HEIGHT_REAL, 3, 3);
	this->_walking_front = new CSprite(spriteHandler, WALK_FRONT_IMG, BOMBER_WIDTH, BOMBER_HEIGHT_REAL, 3, 3);
	this->_walking_behind = new CSprite(spriteHandler, WALK_BEHIND_IMG, BOMBER_WIDTH, BOMBER_HEIGHT_REAL, 3, 3);*/


	this->_last_time = GetTickCount();
}

void Ghost::update(int deltaTime)
{
	UpdatePosition(deltaTime);
}

void Ghost::draw(D3DXVECTOR2 view_port)
{
	/*DWORD now = GetTickCount();
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
*/
}

void Ghost::WalkingRight(){
	if (this->_now_states == Move_States::None)this->_last_states = Move_States::Walking_Right;
	else this->_last_states = this->_now_states;
	this->_now_states = Move_States::Walking_Right;

}

void Ghost::WalkingLeft(){
	if (this->_now_states == Move_States::None)this->_last_states = Move_States::Walking_Left;
	else this->_last_states = this->_now_states;
	this->_now_states = Move_States::Walking_Left;
}

void Ghost::WalkingFront(){
	if (this->_now_states == Move_States::None)this->_last_states = Move_States::Walking_Front;
	else this->_last_states = this->_now_states;
	this->_now_states = Move_States::Walking_Front;
}

void Ghost::WalkingBehind(){
	if (this->_now_states == Move_States::None)this->_last_states = Move_States::Walking_Behind;
	else this->_last_states = this->_now_states;
	this->_now_states = Move_States::Walking_Behind;
}

void Ghost::MoveNone(){
	if (this->_now_states != Move_States::None)this->_last_states = this->_now_states;
	this->_now_states = Move_States::None;
}

CBox Ghost::getBounding()
{
	return CBox(this->_position_x, this->_position_y, this->_width, this->_height, this->_velocity_x, this->_velocity_y);
}

void Ghost::UpdatePosition(int deltaTime)
{
	/*if (this->_now_states == Move_States::Walking_Left)
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
	_position_y += _velocity_y;*/
}

