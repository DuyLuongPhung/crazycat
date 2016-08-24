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

void CQuadTree::SetQuadTreeData(std::vector<CQuadNode*>* allNodes)
{
	int widthLeft, heightTop, widthRight, heightBottom;
	CQuadNode nodeRT, nodeLT, nodeLB, nodeRB;

	std::sort(allNodes->begin(), allNodes->end(), IDGreater);
	
	for (int i = 0; i < allNodes->size(); i++){
		if (i == 0){
			this->_q_root = allNodes->at(0);
			continue;
		}
		this->_q_root->AddNode(allNodes->at(i));
	}

	
}