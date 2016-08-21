
#include "QuadNode.h"

bool IDGreater(CGameObject *lx, CGameObject *rx) {
	return lx->getId() < rx->getId();
}

CQuadNode::CQuadNode()
{
	_nodeLT = NULL;
	_nodeRT = NULL;
	_nodeLB = NULL;
	_nodeRB = NULL;
}

CQuadNode::CQuadNode(int id, D3DXVECTOR2 position, D3DXVECTOR2 size, std::vector<CGameObject*> listObjects)
{
	_nodeLT = NULL;
	_nodeRT = NULL;
	_nodeLB = NULL;
	_nodeRB = NULL;
	_id = id;
	_position = position;
	_size = size;
	for (int i = 0; i < listObjects.size(); i++)
	{
		_list_objects.push_back(listObjects[i]);
	}
}

CQuadNode::~CQuadNode()
{
	SAFE_DELETE(_nodeLT);
	SAFE_DELETE(_nodeRT);
	SAFE_DELETE(_nodeLB);
	SAFE_DELETE(_nodeRB);
}

void CQuadNode::GetObjectsIn(CBox objBox, std::vector<CGameObject*>* objects)
{
	CBox thisBox = GetBox();
	if (thisBox.IsIntersectedWith(objBox))
	{
		if (this->isLeaf())
		{
			if (_list_objects.size() > 0)
			{
				for (int i = 0; i < _list_objects.size(); i++)
					if (objBox.IsIntersectedWith(_list_objects[i]->getBounding()))
						(*objects).push_back(_list_objects[i]);						
				std::sort(objects->begin(), objects->end(), IDGreater);								// Sắp xếp lại các đối tượng
				objects->erase(std::unique(objects->begin(), objects->end()), objects->end());		// Xóa  các phần tử giống nhau trong danh sách
			}
		}
		else
		{
			_nodeLT->GetObjectsIn(objBox, objects);
			_nodeRT->GetObjectsIn(objBox, objects);
			_nodeLB->GetObjectsIn(objBox, objects);
			_nodeRB->GetObjectsIn(objBox, objects);
		}
	}
}

bool CQuadNode::isLeaf(){
	return (!this->_nodeLB && !this->_nodeLT && !this->_nodeRB && !this->_nodeRT);
}

void CQuadNode::AddNode(CQuadNode* node)
{
	if (_id * 4 + 1 == node->_id)
	{
		_nodeRT = node;
		return;
	}
	if (_id * 4 + 2 == node->_id)
	{
		_nodeLT = node;
		return;
	}
	if (_id * 4 + 3 == node->_id)
	{
		_nodeLB = node;
		return;
	}
	if (_id * 4 + 4 == node->_id)
	{
		_nodeRB = node;
		return;
	}
	if (_nodeRT != NULL)
		_nodeRT->AddNode(node);

	if (_nodeRT != NULL)
		_nodeLT->AddNode(node);

	if (_nodeRB != NULL)
		_nodeRB->AddNode(node);

	if (_nodeLB != NULL)
		_nodeLB->AddNode(node);
}

void CQuadNode::AddObject(CGameObject* object)
{
	if (this->isLeaf())
	{
		CBox box1 = this->GetBox();
		CBox box2 = object->getBounding();
		if (box1.IsIntersectedWith(box2))
			this->_list_objects.push_back(object);
	}
	if (_nodeRT != NULL)
		_nodeRT->AddObject(object);

	if (_nodeRT != NULL)
		_nodeRT->AddObject(object);

	if (_nodeRB != NULL)
		_nodeRT->AddObject(object);

	if (_nodeLB != NULL)
		_nodeRT->AddObject(object);
}


CBox CQuadNode::GetBox()
{
	return CBox(_position.x, _position.y, _size.x,_size.y, 0.0f, 0.0f);
}