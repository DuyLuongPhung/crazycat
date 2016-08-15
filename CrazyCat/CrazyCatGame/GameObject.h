#pragma once

#ifndef CGAMEOBJECT_H
#define CGAMEOBJECT_H

#include "Sprite.h"
#include "Box.h"
#include "CONST.h"

class CGameObject
{
protected:
	int _id;			// ID
	float _width;		// chiều rộng
	float _height;		// chiều cao
	float _position_x;	// tọa độ x - top-left
	float _position_y;	// tọa độ y - top-left
	float _velocity_x;	// vận tốc di chuyển theo chiều x
	float _velocity_y;	// vận tốc di chuyển theo chiều y
public:
	CGameObject();
	CGameObject(int id, float x, float y, float width, float height, float vx, float vy);
	~CGameObject();

	int					getId(){ return this->_id; }

	void				setPosition(float x, float y);
	D3DXVECTOR2			getPosition(){ return D3DXVECTOR2(this->_position_x,this->_position_y); }

	void				setVelocity(float vx, float vy);
	D3DXVECTOR2			getVelocity(){ return D3DXVECTOR2(this->_velocity_x, this->_velocity_y); }

	int					getWidth(){ return this->_width; }
	int					getHeight(){ return this->_height; }

	CBox				getBounding();

	virtual void		inital();
	virtual void		draw(D3DXVECTOR2 view_port);
	virtual void		update();
};

#endif

