#include "QuadTree.h"

bool IDGreater(CQuadNode *lx, CQuadNode *rx) {
	return lx->getId() < rx->getId();
}

CQuadTree::CQuadTree()
{
	this->_q_root = NULL;
}

CQuadTree::CQuadTree(std::vector<CQuadNode*>* allNodes){

	this->_q_root = NULL;
	SetQuadTreeData(allNodes);
}


CQuadTree::~CQuadTree()
{
	SAFE_DELETE(this->_q_root);
}

void CQuadTree::addNode(CQuadNode* node){
	this->_q_root->AddNode(node);
}

void CQuadTree::SetQuadTreeData(std::vector<CQuadNode*>* allNodes)
{
	std::sort(allNodes->begin(), allNodes->end(), IDGreater);
	
	for (int i = 0; i < allNodes->size(); i++){
		if (i == 0){
			this->_q_root = (*allNodes).at(i);
			continue;
		}
		this->addNode((*allNodes).at(i));
	}
}

void CQuadTree::addObject(CGameObject* object){
	this->_q_root->AddObject(object);
}

std::vector<CGameObject*> CQuadTree::getObjectList(CBox viewBox){
	std::vector<CGameObject*> objects;
	this->_q_root->GetObjectsIn(viewBox, objects);
	return (objects);
}
