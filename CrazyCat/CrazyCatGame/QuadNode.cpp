//
//#include "QuadNode.h"
//
//bool IDGreater(CObject *lx, CObject *rx) {
//	return lx->_id < rx->_id;
//}
//
//CQuadNode::CQuadNode()
//{
//	_nodeLT = NULL;
//	_nodeRT = NULL;
//	_nodeLB = NULL;
//	_nodeRB = NULL;
//}
//
//CQuadNode::CQuadNode(int id, D3DXVECTOR2 position, D3DXVECTOR2 size, std::vector<CObject*> listObjects)
//{
//	_nodeLT = NULL;
//	_nodeRT = NULL;
//	_nodeLB = NULL;
//	_nodeRB = NULL;
//	_id = id;
//	_position = position;
//	_size = size;
//	for (int i = 0; i < listObjects.size(); i++)
//	{
//		_list_objects.push_back(listObjects[i]);
//	}
//}
//
//CQuadNode::~CQuadNode()
//{
//	SAFE_DELETE(_nodeLT);
//	SAFE_DELETE(_nodeRT);
//	SAFE_DELETE(_nodeLB);
//	SAFE_DELETE(_nodeRB);
//}
//
//void CQuadNode::GetObjectsIn(RECT viewport, std::vector<CObject*>* objects)
//{
//	CCBox thisBox = GetBox();
//	CCBox objBox;
//	objBox._position.x = viewport.left;
//	objBox._position.y = viewport.top;
//	objBox._size.x = viewport.right - viewport.left;
//	objBox._size.y = viewport.top - viewport.bottom;
//	objBox._velocity.x = objBox._velocity.y = 0.0f;
//
//	if (thisBox.IsIntersectedWith(objBox))
//	{
//		if (!_nodeLT && !_nodeRT && !_nodeLB && !_nodeRB)
//		{
//			if (_list_objects.size() > 0)
//			{
//				for (int i = 0; i < _list_objects.size(); i++)
//					if (objBox.IsIntersectedWith(_list_objects[i]->GetPartition()))
//						(*objects).push_back(_list_objects[i]);
//				std::sort(objects->begin(), objects->end(), IDGreater);		// Sắp xếp lại các đối tượng
//				objects->erase(std::unique(objects->begin(), objects->end()), objects->end());		// Xóa  các phần tử giống nhau trong danh sách
//			}
//		}
//		else
//		{
//			_nodeLT->GetObjectsIn(viewport, objects);
//			_nodeRT->GetObjectsIn(viewport, objects);
//			_nodeLB->GetObjectsIn(viewport, objects);
//			_nodeRB->GetObjectsIn(viewport, objects);
//		}
//	}
//}
//
//void CQuadNode::AddNode(CQuadNode* node)
//{
//	if (_id * 4 + 1 == node->_id)
//	{
//		_nodeRT = node;
//		return;
//	}
//	if (_id * 4 + 2 == node->_id)
//	{
//		_nodeLT = node;
//		return;
//	}
//	if (_id * 4 + 3 == node->_id)
//	{
//		_nodeLB = node;
//		return;
//	}
//	if (_id * 4 + 4 == node->_id)
//	{
//		_nodeRB = node;
//		return;
//	}
//	if (_nodeRT != NULL)
//		_nodeRT->AddNode(node);
//
//	if (_nodeRT != NULL)
//		_nodeLT->AddNode(node);
//
//	if (_nodeRB != NULL)
//		_nodeRB->AddNode(node);
//
//	if (_nodeLB != NULL)
//		_nodeLB->AddNode(node);
//}
//
//CCBox CQuadNode::GetBox()
//{
//	return CCBox(_position, _size, D3DXVECTOR2(0.0f, 0.0f));
//}