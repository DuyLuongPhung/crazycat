
#ifndef CQUADNODE_H
#define CQUADNODE_H

#include <vector>
#include "DirectX.h"
#include "Utils.h"
#include "Box.h"
#include <algorithm> 
#include "GameObject.h"

class CQuadNode
{
public:
	CQuadNode();
	CQuadNode(int id, D3DXVECTOR2 position, D3DXVECTOR2 size, std::vector<CGameObject*> listObjects);
	~CQuadNode();

	void GetObjectsIn(RECT viewport, std::vector<CGameObject*>* objects);
	void AddNode(CQuadNode* node);
	CBox GetBox();
	int getId(){ return this->_id; }

private:
	CQuadNode* _nodeLT;		// left - top		- %1
	CQuadNode* _nodeRT;		// rigtht - top		- %2
	CQuadNode* _nodeLB;		// left - bottom	- %3	
	CQuadNode* _nodeRB;		// right - bottom	- %4

	std::vector<CGameObject*> _list_objects;		// danh sách đối tượng trong node
	int		_id;									// node id
	D3DXVECTOR2 _position;							// vị trí
	D3DXVECTOR2 _size;								// khung kích thước
};


#endif
