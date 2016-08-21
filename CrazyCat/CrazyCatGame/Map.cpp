#include "Map.h"


Map::Map(char* mapTitle, LPWSTR tilePathImg, LPWSTR tilePathTxt, LPWSTR objectPath, DWORD mapTimes, int needkeys){
	this->_m_background = NULL;
	this->_m_width = 0;
	this->_m_height = 0;
	this->_m_tile_img = tilePathImg;
	this->_m_tile_txt = tilePathTxt;
	this->_m_object_info = objectPath;
	this->_m_title = mapTitle;
	this->_m_maximum_times = mapTimes;
	this->_m_keys_need = needkeys;
	this->_quad_tree = NULL;
	this->_list_objects.clear();
}


Map::~Map()
{

}

void Map::inital(LPDIRECT3DDEVICE9 d3ddev, ResourceManager * resourMgt){
	this->_list_objects.clear();
	readMapTileBackground(d3ddev, this->_m_tile_img, this->_m_tile_txt, this->_m_width, this->_m_height);
	readMapObjects(this->_m_object_info, resourMgt);
}

void Map::update(D3DXVECTOR2 viewPort, int scrWidth, int scrHeight){
	CBox viewBox(viewPort.x, viewPort.y, scrWidth, scrHeight);

	this->_list_objects.clear();
	this->_list_objects = this->_quad_tree->getObjectList(viewBox);
}

void Map::addNewObjects(CGameObject * insertObject){
	this->_list_objects.push_back(insertObject);
}

void Map::draw(CDirectX * directX, D3DXVECTOR2 viewPort, int gamesceneWidth, int gamesceneHeight){

#pragma region Background
	// lấy khung hình cho frame hiện tại
	RECT srcRect;
	srcRect.left = viewPort.x;
	srcRect.right = srcRect.left + gamesceneWidth;
	srcRect.top = _m_height - viewPort.y;
	srcRect.bottom = srcRect.top + gamesceneHeight;

	// lấy khung sẽ vẽ trên màn hình
	RECT desRect;
	desRect.left = 0;
	desRect.right = desRect.left + gamesceneWidth;
	desRect.top = 0;
	desRect.bottom = desRect.top + gamesceneHeight;

	// vẽ khung hình lên backbuffer
	directX->getDevice()->StretchRect(this->_m_background, &srcRect, directX->getBackBuffer(), &desRect, D3DTEXF_NONE);
#pragma endregion

#pragma region Object
	for (int i = 0; i < this->_list_objects.size(); i++){
		this->_list_objects.at(i)->draw(viewPort);
	}
#pragma endregion
}

/**********************************************************************************
* Đọc file text và file img thu nhỏ để lấy hình nền map cho các đối tượng tĩnh
* Kết quả: là ảnh nền chứa các đối tượng tĩnh
***********************************************************************************/
void Map::readMapTileBackground(LPDIRECT3DDEVICE9 d3ddev, LPWSTR tilePathImg, LPWSTR tilePathTxt,
	int &mapWidth, int &mapHeight){
	std::ifstream myfile(tilePathTxt);

	if (myfile.is_open())
	{
		std::string line;
		int mode = 0;
		int itemCount = 0;
		int row = -1;
		int col = 0;

		int mRows = 0;
		int mCols = 0;
		int mWidth = 0;
		int mHeight = 0;
		int mTileWidth = 0;
		int mTileHeight = 0;
		int mTilesCount = 0;
		TileMap * mTiles = NULL;
		int currentTile = 0;
		int** mTileMatrix = NULL;
		int currentRows = 0;

#pragma region Đọc file text

		while (std::getline(myfile, line))
		{
			if (line.length() < 1)
			{
				mode++;
				continue;
			}
			if (mode == 1)		// đọc thông tin cơ bản của map
			{
				if (line[0] == ' ')
					line.erase(0, 1);
				size_t pos = 0;
				std::string token;
				int j = 0;
				while ((pos = line.find(" ")) != std::string::npos && j < 6)
				{
					token = line.substr(0, pos);
					if (j == 0) // map width
						mWidth = stoi(token);
					if (j == 1) // map height
						mHeight = stoi(token);
					if (j == 2) // row
						mRows = stoi(token);
					if (j == 3) // column
						mCols = stoi(token);
					if (j == 4) // tile width
						mTileWidth = stoi(token);
					if (j == 5) // tile height
						mTileHeight = stoi(token);
					line.erase(0, pos + 1);
					j++;
				}
			}
			if (mode == 2)		// đọc số lượng tiles
			{
				if (line[0] == ' ')
					line.erase(0, 1);
				row++;
				col = 0;
				size_t pos = 0;
				std::string token;
				int j = 0;
				while ((pos = line.find(" ")) != std::string::npos && j < 1)
				{
					token = line.substr(0, pos);
					mTilesCount = stoi(token);
					mTiles = new TileMap[mTilesCount];
					line.erase(0, pos + 1);
					j++;
				}
			}
			if (mode == 3)		// đọc thông tin tiles
			{
				if (line[0] == ' ')
					line.erase(0, 1);
				row++;
				col = 0;
				size_t pos = 0;
				std::string token;
				int j = 0;
				TileMap tileMap;
				tileMap.w = mTileWidth;
				tileMap.h = mTileHeight;

				while ((pos = line.find(" ")) != std::string::npos && j < 3)
				{
					token = line.substr(0, pos);
					if (j == 0) // tile id
						tileMap.id = stoi(token);
					if (j == 1) // x
						tileMap.x = stoi(token);
					if (j == 2) // y
						tileMap.y = stoi(token);

					line.erase(0, pos + 1);
					j++;
				}
				if (currentTile < mTilesCount)
					mTiles[currentTile++] = tileMap;
			}
			if (mode == 4)		// đọc ma trận tiles
			{
				if (mTileMatrix == NULL)
				{
					mTileMatrix = new int*[mRows];
					for (int i = 0; i < mRows; i++){
						mTileMatrix[i] = new int[mCols];
					}
				}

				if (line[0] == ' ')
					line.erase(0, 1);
				size_t pos = 0;
				std::string token;
				int j = 0;
				TileMap tileMap;
				tileMap.w = mTileWidth;
				tileMap.h = mTileHeight;

				while ((pos = line.find(" ")) != std::string::npos && j < mCols)
				{
					token = line.substr(0, pos);
					mTileMatrix[currentRows][j] = stoi(token);
					line.erase(0, pos + 1);
					j++;
				}
				currentRows++;
			}

		}

#pragma endregion

#pragma region Đọc file ảnh


		LPDIRECT3DSURFACE9 shortImg = LoadSurfaceFromFile(d3ddev, tilePathImg, D3DCOLOR_XRGB(255, 0, 255));
		//CSprite shortImg

		HRESULT hresult;
		hresult = d3ddev->CreateOffscreenPlainSurface(mWidth, mHeight, D3DFMT_X8R8G8B8, D3DPOOL_DEFAULT, &this->_m_background, NULL);

		if (hresult != D3D_OK)
			return;

		for (int i = 0; i < mRows; i++)
		{
			for (int j = 0; j < mCols; j++)
			{
				for (int k = 0; k < mTilesCount; k++){
					if (mTileMatrix[i][j] == mTiles[k].id){
						RECT srcRect, desRect;
						srcRect.left = mTiles[k].x;
						srcRect.right = srcRect.left + mTiles[k].w;
						srcRect.top = mTiles[k].y;
						srcRect.bottom = srcRect.top + mTiles[k].h;

						desRect.left = j*mTileWidth;
						desRect.right = desRect.left + mTileWidth;
						desRect.top = i*mTileHeight;
						desRect.bottom = desRect.top + mTileHeight;

						d3ddev->StretchRect(shortImg, &srcRect, this->_m_background, &desRect, D3DTEXF_NONE);
					}
				}
			}
		}

#pragma endregion

		this->_m_height = mHeight;
		this->_m_width = mWidth;
		myfile.close();
	}
	return;
}

/**********************************************************************************
* Đọc file text chứa các đối tượng object trong game
* Kết quả: danh sách các object được lưu vào quadtree
***********************************************************************************/
void Map::readMapObjects(LPWSTR mapInfoPath, ResourceManager * resourMgt){
	std::ifstream myfile(mapInfoPath);

	if (myfile.is_open())
	{
		std::string line;
		int mode = 0;
		int itemCount = 0;
		int row = -1;
		int col = 0;

		int mRows = 0;
		int mCols = 0;
		int mWidth = 0;
		int mHeight = 0;
		int mTileWidth = 0;
		int mTileHeight = 0;
		int mTilesCount = 0;
		TileMap * mTiles = NULL;
		int currentTile = 0;
		int** mTileMatrix = NULL;
		std::vector<QNodeItem> all_items;
		std::vector<TileMap> all_quadnodes;
		std::vector<QNodeObjects> all_objects;

#pragma region Đọc file text

		while (std::getline(myfile, line))
		{
			if (line.length() < 1)
			{
				mode++;
				continue;
			}
			if (mode == 1)		// đọc thông tin cơ bản của map
			{
				if (line[0] == ' ')
					line.erase(0, 1);
				size_t pos = 0;
				std::string token;
				int j = 0;
				while ((pos = line.find(" ")) != std::string::npos && j < 6)
				{
					token = line.substr(0, pos);
					if (j == 0) // map width
						mWidth = stoi(token);
					if (j == 1) // map height
						mHeight = stoi(token);
					if (j == 2) // row
						mRows = stoi(token);
					if (j == 3) // column
						mCols = stoi(token);
					if (j == 4) // tile width
						mTileWidth = stoi(token);
					if (j == 5) // tile height
						mTileHeight = stoi(token);
					line.erase(0, pos + 1);
					j++;
				}
			}
			if (mode == 2)		// đọc thông tin các items
			{
				if (line[0] == ' ')
					line.erase(0, 1);
				row++;
				col = 0;
				size_t pos = 0;
				std::string token;
				int j = 0;
				QNodeItem item;

				while ((pos = line.find(" ")) != std::string::npos && j < 4)
				{
					token = line.substr(0, pos);
					if (j == 0)	// index
						item.index = stoi(token);
					if (j == 1)	// type id
						item.typeId = stoi(token);
					if (j == 2)	// item width
						item.w = stoi(token);
					if (j == 3)	// item height
						item.h = stoi(token);
					line.erase(0, pos + 1);
					j++;
				}
				all_items.push_back(item);
			}
			if (mode == 3)		// đọc thông tin quad tree node
			{
				if (line[0] == ' ')
					line.erase(0, 1);
				row++;
				col = 0;
				size_t pos = 0;
				std::string token;
				int j = 0;
				TileMap qnode;
				while ((pos = line.find(" ")) != std::string::npos && j < 5)
				{
					token = line.substr(0, pos);
					if (j == 0) // node id
						qnode.id = stoi(token);
					if (j == 1) // x
						qnode.x = stoi(token);
					if (j == 2) // y
						qnode.y = stoi(token);
					if (j == 3) // width
						qnode.w = stoi(token);
					if (j == 4) // height
						qnode.h = stoi(token);

					line.erase(0, pos + 1);
					j++;
				}
				all_quadnodes.push_back(qnode);
			}
			if (mode == 4)		// đọc thông tin các objects trong map
			{

				if (line[0] == ' ')
					line.erase(0, 1);
				size_t pos = 0;
				std::string token;
				int j = 0;
				QNodeObjects qobject;
				while ((pos = line.find(" ")) != std::string::npos && j < 4)
				{
					token = line.substr(0, pos);
					if (j == 0)	// index
						qobject.index = stoi(token);
					if (j == 1)	// node id
						qobject.node_id = stoi(token);
					if (j == 2)	// x
						qobject.x = stoi(token);
					if (j == 3)	// y
						qobject.y = stoi(token);

					line.erase(0, pos + 1);
					j++;
				}
				all_objects.push_back(qobject);
			}

		}

#pragma endregion

		myfile.close();
		/*for (int j = 0; j < all_objects.size(); j++){
			int typeId = -1;
			int x = all_objects.at(j).x;
			int y = all_objects.at(j).y;
			int  w = 0, h = 0;
			for (int k = 0; k < all_items.size(); k++){
				if (all_objects.at(j).index == all_items.at(k).index){
					w = all_items.at(k).w;
					h = all_items.at(k).h;
					typeId = all_items.at(k).typeId;
					break;
				}
			}
			if (typeId == ID_BRICK)
			{
				CGameObject * objAdd = new Brick(x, y, w, h, 0.0f, 0.0f);
				all_objects.erase(all_objects.begin() + j--);
				this->_list_objects.push_back(objAdd);
			}
			if (typeId == ID_TILEBOX_NORMAL ||
				typeId == ID_TILEBOX_COIN ||
				typeId == ID_TILEBOX_HEART ||
				typeId == ID_TILEBOX_TIME ||
				typeId == ID_TILEBOX_VELOCITY ||
				typeId == ID_TILEBOX_SUPERBOMB){
				CGameObject * objAdd = new TileBox(typeId, x, y, w, h, resourMgt->getSpriteWithID(ID_TILEBOX_NORMAL));
				all_objects.erase(all_objects.begin() + j--);
				this->_list_objects.push_back(objAdd);
			}
			if (typeId == ID_GIFTBOX_KEY){
				CGameObject * objAdd = new GiftBox(typeId, -1, x, y, w, h, resourMgt->getSpriteWithID(ID_GIFTBOX_KEY));
				all_objects.erase(all_objects.begin() + j--);
				this->_list_objects.push_back(objAdd);
			}
			if (typeId == ID_DOOR){
				CGameObject * objAdd = new DoorObject(typeId, x, y, w, h, resourMgt->getSpriteWithID(ID_DOOR));
				all_objects.erase(all_objects.begin() + j--);
				this->_list_objects.push_back(objAdd);
			}
		}*/

		std::vector<CQuadNode*>* all_q_nodes = new std::vector<CQuadNode*>[1];
		for (int i = 0; i < all_quadnodes.size(); i++){
			int id = all_quadnodes.at(i).id;
			int x = all_quadnodes.at(i).x;
			int y = all_quadnodes.at(i).y;
			int w = all_quadnodes.at(i).w;
			int h = all_quadnodes.at(i).h;

			std::vector<CGameObject*> q_node_objects;
			for (int j = 0; j < all_objects.size(); j++){
				int typeId = -1;
				int x = all_objects.at(j).x;
				int y = all_objects.at(j).y;
				int  w = 0, h = 0;
				for (int k = 0; k < all_items.size(); k++){
					if (all_objects.at(j).index == all_items.at(k).index){
						w = all_items.at(k).w;
						h = all_items.at(k).w;
						typeId = all_items.at(k).typeId;
						break;
					}
				}
				if (all_objects[j].node_id == id){
					if (typeId == ID_BRICK)
					{
						CGameObject * objAdd = new Brick(x, y, w, h, 0.0f, 0.0f);
						all_objects.erase(all_objects.begin() + j--);
						q_node_objects.push_back(objAdd);
					}
					if (typeId == ID_TILEBOX_NORMAL ||
						typeId == ID_TILEBOX_COIN ||
						typeId == ID_TILEBOX_HEART ||
						typeId == ID_TILEBOX_TIME ||
						typeId == ID_TILEBOX_VELOCITY ||
						typeId == ID_TILEBOX_SUPERBOMB){
						CGameObject * objAdd = new TileBox(typeId, x, y, w, h, resourMgt->getSpriteWithID(ID_TILEBOX_NORMAL));
						all_objects.erase(all_objects.begin() + j--);
						q_node_objects.push_back(objAdd);
					}
					if (typeId == ID_GIFTBOX_KEY){
						CGameObject * objAdd = new GiftBox(typeId, -1, x, y, w, h, resourMgt->getSpriteWithID(ID_GIFTBOX_KEY));
						all_objects.erase(all_objects.begin() + j--);
						q_node_objects.push_back(objAdd);
					}
					if (typeId == ID_DOOR){
						CGameObject * objAdd = new DoorObject(typeId, x, y, w, h, resourMgt->getSpriteWithID(ID_DOOR));
						all_objects.erase(all_objects.begin() + j--);
						q_node_objects.push_back(objAdd);
					}
				}
			}

			CQuadNode* node = new CQuadNode(id, D3DXVECTOR2(x, y), D3DXVECTOR2(w, h), q_node_objects);
			all_q_nodes->push_back(node);
		}

		this->_quad_tree = new CQuadTree(all_q_nodes);
	}
	return;
}

