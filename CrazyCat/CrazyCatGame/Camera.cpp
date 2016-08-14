
#include "Camera.h"

CCamera::CCamera(int screenWidth, int screenHeight)
{
	_screenHeight = screenHeight;
	_screenWidth = screenWidth;
	SetPositionCamera(D3DXVECTOR2(0.0f, screenHeight));
}

CCamera::~CCamera()
{

}

void CCamera::SetPositionCamera(D3DXVECTOR2 position)
{
	_position = position;
}

void CCamera::Transform(D3DXVECTOR2 viewPort, D3DXVECTOR2* position)
{
	D3DXMATRIX	transformMatrix;
	D3DXMatrixIdentity(&transformMatrix);
	transformMatrix._22 = -1.0f;
	transformMatrix._41 = -viewPort.x;
	transformMatrix._42 = viewPort.y;

	D3DXVECTOR4 outTransform;
	D3DXVec3Transform(&outTransform, &D3DXVECTOR3(position->x, position->y, 0.0f), &transformMatrix);

	position->x = floor(outTransform.x);
	position->y = floor(outTransform.y);
}

void CCamera::InTransform(D3DXVECTOR2 viewPort, D3DXVECTOR2* inPosition)
{
	D3DXMATRIX	inTransformMatrix;
	D3DXMatrixIdentity(&inTransformMatrix);
	inTransformMatrix._22 = -1.0f;
	inTransformMatrix._41 = viewPort.x;
	inTransformMatrix._42 = viewPort.y;

	D3DXVECTOR4 outInTransform;
	D3DXVec3Transform(&outInTransform, &D3DXVECTOR3(inPosition->x, inPosition->y, 0.0f), &inTransformMatrix);

	inPosition->x = floor(outInTransform.x);
	inPosition->y = floor(outInTransform.y);
}

D3DXVECTOR2 CCamera::GetPositionCamera()
{
	return _position;
}

RECT CCamera::GetViewport()
{
	RECT rect;
	rect.left = _position.x;
	rect.top = _position.y;
	rect.right = rect.left + _screenWidth;
	rect.bottom = rect.top - _screenHeight;

	return rect;
}