//
//#include <vector>
//#include "DirectX.h"
//#include "Utils.h"
//#include "Box.h"
//#include <algorithm> 
//
//class CQuadNode
//{
//public:
//	CQuadNode();
//	//CQuadNode(int id, D3DXVECTOR2 position, D3DXVECTOR2 size, std::vector<CObject*> listObjects);
//	~CQuadNode();
//
//	///void GetObjectsIn(RECT viewport, std::vector<CObject*>* objects);
//	void AddNode(CQuadNode* node);
//	CBox GetBox();
//
//private:
//	CQuadNode* _nodeLT;		// left - top
//	CQuadNode* _nodeRT;		// rigtht - top
//	CQuadNode* _nodeLB;		// left - bottom
//	CQuadNode* _nodeRB;		// right - bottom
//
//	//std::vector<CObject*> _list_objects;		// danh sách đối tượng trong node
//	int		_id;		// node id
//	D3DXVECTOR2 _position;		// vị trí
//	D3DXVECTOR2 _size;		// khung kích thước
//};
//
