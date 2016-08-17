#include "Box.h"

CBox::CBox(){
	this->x = 0.0f;
	this->y = 0.0f;
	this->w = 0.0f;
	this->h = 0.0f;
	this->vx = 0.0f;
	this->vy = 0.0f;
}

CBox::CBox(float x, float y, float w, float h, float vx, float vy){
	this->x = x;
	this->y = y;
	this->w = w;
	this->h = h;
	this->vx = vx;
	this->vy = vy;
}
CBox::CBox(float x, float y, float w, float h){
	this->x = x;
	this->y = y;
	this->w = w;
	this->h = h;
	this->vx = 0.0f;
	this->vy = 0.0f;
}

bool CBox::IsIntersectedWith(CBox box)
{
	return !(this->x + this->w <= box.x || this->x >= box.x + box.w || this->y - this->h >= box.y || this->y <= box.y - box.h);
}

RECT CBox::ToRect()
{
	RECT result;
	result.left = x;
	result.top = y;
	result.right = result.left + w;
	result.bottom = result.top - h;
	return result;
}

CBox::~CBox()
{
}
