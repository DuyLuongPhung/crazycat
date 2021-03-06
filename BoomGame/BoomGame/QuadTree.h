#pragma once

#include "QuadNode.h"
#include "CONST.h"

class CQuadTree
{
private:
	CQuadNode * _q_root;
public:
	CQuadTree();
	CQuadTree(std::vector<CQuadNode*>* allNodes);

	~CQuadTree();

	void getObjectsIn(RECT viewport, std::vector<CGameObject*> objects);
	void addNode(CQuadNode* node);
	void SetQuadTreeData(std::vector<CQuadNode*>* allNodes);
};

