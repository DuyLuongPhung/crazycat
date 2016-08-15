#include "Brick.h"


Brick::Brick()
{
	this->_id = BRICK_ID;
}

Brick::Brick(float x, float y, float width, float height, float vx, float vy)
	: CStaticGameObject(BRICK_ID, x, y, width, height, vx, vy)
{
}


Brick::~Brick()
{
}
