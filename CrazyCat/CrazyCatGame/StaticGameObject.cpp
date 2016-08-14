#include "StaticGameObject.h"


CStaticGameObject::CStaticGameObject() : CGameObject()
{
}



CStaticGameObject::CStaticGameObject(int id, float x, float y, float width, float height, float vx, float vy)
	: CGameObject(id,x,y,width,height,vx,vy)
{
}


CStaticGameObject::~CStaticGameObject()
{
}

void CStaticGameObject::inital()
{

}

void CStaticGameObject::update()
{

}

void CStaticGameObject::draw(D3DXVECTOR2 view_port)
{
	//m_Sprite->Render(m_Position.x, m_Position.y);
}
