#include "Brick.h"


Brick::Brick()
{
	this->_id = ID_BRICK;
}

Brick::Brick(float x, float y, float width, float height, float vx, float vy)
	: CStaticGameObject(ID_BRICK, x, y, width, height, vx, vy)
{
}


Brick::~Brick()
{
}
