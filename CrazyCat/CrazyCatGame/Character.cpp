#include "Character.h"


CCharacter::CCharacter(LPD3DXSPRITE SpriteHandler, int start_x, int start_y, int mapWidth, int mapHeight)
{
	this->_position_x = start_x;		
	this->_position_y = 500;// start_y;
	this->_velocity_x = 0;
	this->_velocity_y = 0;
	this->_last_velocity_x = 1;
	this->_mode = Character_Mode::Walk;
	this->_width_body = 61;
	this->_height_body = 91;
	this->_mapHeight = mapHeight;
	this->_mapWidth = mapWidth;
	this->_allow_jump = false;
	this->_now_states = Move_States::None;
	//this->_last_states = _now_states;
	this->_last_mode = Character_Mode::Run;
	this->_is_double_jump = false;
	this->_is_jumping = false;
	this->_allowSlide = true;

	this->_walking_right = NULL;
	this->_slide_right = NULL;
	this->_run_right = NULL;
	this->_dead_right = NULL;
	this->_hurt_right = NULL;
	this->_fall_right = NULL;
	this->_jump_right = NULL;
	LoadResource(SpriteHandler);
}

CCharacter::~CCharacter()
{
	delete(this->_walking_right);
	delete(this->_slide_right);
	delete(this->_run_right);
	delete(this->_hurt_right);
}

void CCharacter::LoadResource(LPD3DXSPRITE SpriteHandler)
{
	_walking_right = new CSprite(SpriteHandler, WALK_RIGHT_IMG, WALK_IDLE_WIDTH, WALK_IDLE_HEIGHT, 10, 10);
	_slide_right = new CSprite(SpriteHandler, SLIDE_RIGHT_IMG, SLIDE_WIDTH, SLIDE_HEIGHT, 10, 10);
	_run_right = new CSprite(SpriteHandler, RUN_RIGHT_IMG, RUN_JUMP_FALL_WIDTH, RUN_JUMP_FALL_HEIGHT, 8, 8);
	_dead_right = new CSprite(SpriteHandler, DEAD_RIGHT_IMG, DEAD_HURT_WIDTH, DEAD_HURT_HEIGHT, 10, 10);
	_hurt_right = new CSprite(SpriteHandler, HURT_RIGHT_IMG, DEAD_HURT_WIDTH, DEAD_HURT_HEIGHT, 10, 10);
	_fall_right = new CSprite(SpriteHandler, FALL_RIGHT_IMG, RUN_JUMP_FALL_WIDTH, RUN_JUMP_FALL_HEIGHT, 8, 8);
	_jump_right = new CSprite(SpriteHandler, JUMP_RIGHT_IMG, RUN_JUMP_FALL_WIDTH, RUN_JUMP_FALL_HEIGHT, 8, 8);
}

void CCharacter::Jumping(int deltaTime)
{
	if (!_allow_jump)
		return;
	_start_jump_y = this->_position_y;
	if (_is_jumping){	// đang nhảy lên
		if (_is_double_jump){	// đang nhảy lên với double-jump
			// không thể nhảy lên được nữa
			return;
		}
		else{	// đang nhảy lên single-jump
			_velocity_y = MAX_VELOCITY_Y;
			_jump_right->Reset();
			_jump_sprite = 0;
			_is_double_jump = true;
			_allow_jump = false;
			_is_falling = false;
			return;
		}
	}
	else{	// hiện tại chưa nhảy lên
		_velocity_y = MAX_VELOCITY_Y;
		_is_jumping = true;
		_jump_sprite = 0;
		_is_double_jump = false;
		_is_falling = false;
		//_jump_right->Reset();
	}
}

void CCharacter::Walking(int deltaTime)
{
	_position_x += deltaTime*_velocity_x;
	if (_position_x < 0)
		_position_x = 1;
	if (_position_x > (_mapWidth-_width_body))
		_position_x = (_mapWidth - _width_body) - 1;
	/*if (_position_x > 2000)
		this->_mode = Character_Mode::Dead;*/
}

void CCharacter::UpdatePosition(int deltaTime)
{
	if (_is_dead || _is_hurt){
		return;
	}
	if (_isFall){

	}
	//_position_y -= 2;
	//UpdatePosition_X(deltaTime);
	UpdatePosition_Y(deltaTime);
}

void CCharacter::UpdatePosition_Y(int deltaTime)
{
	
		_velocity_y -= (GRAVITY_Y*deltaTime);
		_position_y += _velocity_y*deltaTime;

	if (_velocity_y <= 0 && !_is_falling)
	{
		_fall_right->Reset();
		_is_falling = true;
		_is_jumping = false;
		_is_double_jump = false;
		_allow_jump = false;
		_fall_sprite = 0;
	}

	if (_position_y < GROUND_Y)
	{
		_position_y = _height_body + GROUND_Y;
		_allow_jump = true;
		_is_jumping = false;
		_is_double_jump = false;
		if (this->_now_states = Move_States::None)
		this->_now_states = Move_States::Walking_Right;
		this->_mode = Character_Mode::Run;
		_jump_right->Reset();
		_jump_sprite = 0;
		_fall_sprite = 0;
	}
}

void CCharacter::UpdatePosition_X(int deltaTime)
{
	switch (this->_mode){
	case Character_Mode::Walk:case Character_Mode::Run:
		_velocity_x += deltaTime*GRAVITY_X;
		if (_velocity_x > MAX_VELOCITY_X_WALK && this->_mode != Character_Mode::Run)
			UpdateCharacterMode(Character_Mode::Run);
		if (_velocity_x > MAX_VELOCITY_X_WALK && !_allowSlide)
			_allowSlide = true;

		break;
	case Character_Mode::Slide:
		_velocity_x -= deltaTime*GRAVITY_X;
		if (_velocity_x < (MAX_VELOCITY_X_WALK/2)){
			_velocity_x = (MAX_VELOCITY_X_WALK / 2);
			UpdateCharacterMode(Character_Mode::Walk);
		}

		break;
	case Character_Mode::Jump: case Character_Mode::Fall:
		break;
	
	default:
		break;
	}

	if (_velocity_x > MAX_VELOCITY_X_RUN)
	{
		_velocity_x = MAX_VELOCITY_X_RUN;
	}

	if (_velocity_x < 0)
		_velocity_x = 0;


	if (_is_dead || _is_hurt){
		return;
	}

	
	
	int deltaS = _velocity_x*deltaTime;
	_position_x += deltaS;
	_position_x += deltaTime*_velocity_x;
	if (_position_x < 0)
		_position_x = 1;
	if (_position_x >(_mapWidth - _width_body))
		_position_x = (_mapWidth - _width_body) - 1;
	Sliding(100, _velocity_x);
	
}

void CCharacter::UpdateCharacterMode(Character_Mode mode)
{
	if (mode == Character_Mode::Jump)
	{
		//if (this->_mode == Character_Mode::Run || this->)
	}

	if (mode == Character_Mode::Slide){
		if (!_allowSlide)
		{
			return;
		}
	}
	this->_mode = mode;
	switch (_mode)
	{
	case Character_Mode::Slide:
		_width_body = SLIDE_HEIGHT;
		_height_body = SLIDE_HEIGHT;
		break;
	default:
		_width_body = WALK_IDLE_WIDTH;
		_height_body = WALK_IDLE_HEIGHT;
		break;
	}
}

void CCharacter::ChangingDirection(Move_States states)
{
	////_last_states = _now_states;
	//_now_states = states;
	//if (_last_states != _now_states)
	//{
	//	if (_velocity_x != 0)
	//		_last_velocity_x = _velocity_x;
	//	_velocity_x = 0;
	//}
}

void CCharacter::Sliding(int deltaTime, float velocity_x){
	if (_isSlide){
		if (_allowSlide)
			_allowSlide = false;
		_slideTime += deltaTime;
		if (_slideTime > 5000)
		{
			_isSlide = false;
			_slideDelay = 0;
			this->_mode = _last_mode;
			_isDelaySlide = true;
			_slideTime = 0;
			_velocity_x = MAX_VELOCITY_X_WALK/2;
		}
		return;
	}
	else {
		_slideDelay += deltaTime;
		if (_slideDelay > 1000)
			_slideDelay = 1000;
		if (_slideDelay >= 1000 && _velocity_x > MAX_VELOCITY_X_WALK)
		{
			_allowSlide = true;
		}
		if (this->_mode == Character_Mode::Slide && !_isSlide){
			_isSlide = true;
			_allowSlide = false;
			_slideTime = 0;
			_isDelaySlide = false;
			_slideDelay = 0;
		}
	}
}

void CCharacter::RenderCharacter(D3DXVECTOR2 viewPort)
{
	if (_is_hurt && _hurtDrawCount >= 10){
		_is_hurt = false;
		_velocity_x = 0;
		this->_mode = Character_Mode::Walk;
	}
	DWORD now = GetTickCount();
	if (now - _last_time > 1000 / ANIMATE_RATE)
	{
		switch (_mode)
		{
		case Character_Mode::Walk:


			if (_velocity_x > 0)
			{
				if (_is_jumping)
					_walking_right->Index(1);
				else
					_walking_right->Next();
			}
			else if (_velocity_x < 0)
			{
				if (_is_jumping)
					_walking_right->Index(1);
				else
					_walking_right->Next();
			}
			else
			{
				if (_last_velocity_x > 0)
				{
					if (_is_jumping)
						_walking_right->Index(1);
					else
						_walking_right->Reset();
				}
				if (_last_velocity_x < 0)
				{
					if (_is_jumping)
						_walking_right->Index(1);
					else
						_walking_right->Next();
				}
			}
			break;
		case Character_Mode::Slide:
			if (_velocity_x > 0)
			{
				if (_is_jumping)
					_slide_right->Index(2);
				else
					_slide_right->Next();
			}
			else if (_velocity_x < 0)
			{
				if (_is_jumping)
					_slide_right->Index(2);
				else
					_slide_right->Next();
			}
			else
			{
				if (_last_velocity_x > 0)
				{
					if (_is_jumping)
						_slide_right->Index(2);
					else
						_slide_right->Reset();
				}
				if (_last_velocity_x < 0)
				{
					if (_is_jumping)
						_slide_right->Index(2);
					else
						_slide_right->Reset();
				}
			}
			break;
		case Character_Mode::Run:
			if (_velocity_x > 0)
			{
				if (_is_jumping)
					_run_right->Index(2);
				else
					_run_right->Next();
			}
			else if (_velocity_x < 0)
			{
				if (_is_jumping)
					_run_right->Index(2);
				else
					_run_right->Next();
			}
			else
			{
				if (_last_velocity_x > 0)
				{
					if (_is_jumping)
						_run_right->Index(2);
					else
						_run_right->Reset();
				}
				if (_last_velocity_x < 0)
				{
					if (_is_jumping)
						_run_right->Index(2);
					else
						_run_right->Reset();
				}
			}
			break;
		case Character_Mode::Dead:
			if (_deadDrawCount < 10)
				_dead_right->Index((this->_deadDrawCount)++);
			break;
		case Character_Mode::Hurt:
			if (_hurtDrawCount < 10)
				_hurt_right->Index((this->_hurtDrawCount)++);
			break;
		case Character_Mode::Fall:
			//_fall_right->Next();
			break;
		case Character_Mode::Jump:
			if (_is_falling){
				if (_fall_sprite++ < 7){
					_fall_right->Next();
				}
			}
			else //if (_is_jumping || _is_double_jump)
			{
				if (_jump_sprite++ < 7){
					_jump_right->Next();
				}
			}



			break;
		default:
			break;
		}

		_last_time = now;
	}
	switch (_mode)
	{
	case Character_Mode::Walk:
		if (_velocity_x > 0)
		{
			_walking_right->Render(viewPort,_position_x, _position_y);
		}
		else if (_velocity_x < 0)
		{
			_walking_right->Render(viewPort, _position_x, _position_y);
		}
		else 
		{
			if (_last_velocity_x > 0)
				_walking_right->Render(viewPort, _position_x, _position_y);
			if (_last_velocity_x < 0)
				_walking_right->Render(viewPort, _position_x, _position_y);
		}
		break;
	case Character_Mode::Slide:
		if (_velocity_x > 0)
		{
			_slide_right->Render(viewPort, _position_x, _position_y);
		}
		else if (_velocity_x < 0)
		{
			_slide_right->Render(viewPort, _position_x, _position_y);
		}
		else 
		{
			if (_last_velocity_x > 0)
				_slide_right->Render(viewPort, _position_x, _position_y);
			if (_last_velocity_x < 0)
				_slide_right->Render(viewPort, _position_x, _position_y);
		}
		break;
	case Character_Mode::Run:
		if (_velocity_x > 0)
		{
			_run_right->Render(viewPort, _position_x, _position_y);
		}
		else if (_velocity_x < 0)
		{
			_run_right->Render(viewPort, _position_x, _position_y);
		}
		else
		{
			if (_last_velocity_x > 0)
				_run_right->Render(viewPort, _position_x, _position_y);
			if (_last_velocity_x < 0)
				_run_right->Render(viewPort, _position_x, _position_y);
		}
		break;
	case Character_Mode::Dead:
			_dead_right->Render(viewPort, _position_x, _position_y);
			break;
	case Character_Mode::Hurt:
		_hurt_right->Render(viewPort, _position_x, _position_y);
		
		break;
	case Character_Mode::Fall:
		//_fall_right->Render(viewPort, _position_x, _position_y);

		break;
	case Character_Mode::Jump:

		if (_is_falling){
			_fall_right->Render(viewPort, _position_x, _position_y);
		}
		else //if (_is_jumping || _is_double_jump)
		{
			_jump_right->Render(viewPort, _position_x, _position_y);
		}

		
		break;
	}
}

void CCharacter::dead(){
	this->_is_dead = true;
	this->_deadDrawCount = 0;
	this->_mode = Character_Mode::Dead;
}

void CCharacter::inital()
{

}

void CCharacter::update()
{

}

void CCharacter::draw(D3DXVECTOR2 view_port)
{
	if (this->_sprite_resource != NULL){
		this->_sprite_resource->Render(view_port, this->_position_x, this->_position_y);
	}
}

CBox CCharacter::getPartion(){
	return CBox(this->_position_x, this->_position_y, this->_width_body, this->_height_body, this->_velocity_x, this->_velocity_y);
}

