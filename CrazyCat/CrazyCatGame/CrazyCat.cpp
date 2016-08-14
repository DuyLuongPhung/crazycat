#include "CrazyCat.h"
#include "CONST.h"
#include <stdio.h>
#include <stdlib.h>

#define _CRT_SECURE_NO_WARNINGS



CrazyCat::CrazyCat(HINSTANCE hInstance, LPWSTR name, int mode, int is_fullscreen, int frame_rate) :
CGame(hInstance, name, mode, is_fullscreen, frame_rate)
{
	_character = NULL;
	_collision = new CCollision();
}
char * vyBuffer = new char[30];

CrazyCat::~CrazyCat()
{
	SAFE_DELETE(this->_character);
	SAFE_DELETE(this->_collision);
	SAFE_DELETE(this->_textPrint);
	SAFE_DELETE(this->_map);
}
bool intersec = false;
void CrazyCat::Update(int Delta)
{
	if (intersec)
	Sleep(3000);
	//UpdateMap();
	UpdateCharacter(Delta);
	
	CBox tileBox = _tile_object->getBounding();
	CBox characterBox = _character->getBounding();
	characterBox.vx = characterBox.vx*Delta;
	characterBox.vy = characterBox.vy*Delta;

	_itoa_s((int)characterBox.vy, vyBuffer,30, 10);

	float normalX = 0.0f, normalY = 0.0f, collisonTime = -1.0f;
	DIRECTION dir = _collision->isCollision(characterBox, tileBox, collisonTime);

	switch (dir)
	{
	case DIRECTION::LEFT:
		lalbelTest = "Left";
		intersec = true;
		break;
	case DIRECTION::RIGHT:
		lalbelTest = "Right";
		intersec = true;
		break;
	case DIRECTION::TOP:
		lalbelTest = "Top";
		intersec = true;
		break;
	case DIRECTION::BOTTOM:
		lalbelTest = "Bottom";
		intersec = true;
		break;
	default:
		lalbelTest = "None";
		intersec = false;
		break;
	}
	
}


void CrazyCat::UpdateMap()
{
	// update background
	RECT from = _Camera->GetViewport();
	D3DXVECTOR2 realPosition(from.left, from.top);
	_Camera->InTransform(D3DXVECTOR2(0, _mapMaxHeight), &realPosition);

	_background_partition.left = realPosition.x;
	_background_partition.top = realPosition.y;
	_background_partition.right = _background_partition.left + _screenWidth;
	_background_partition.bottom = _background_partition.top + _screenHeight;

	// update object
	/**
	comming soon
	*/
}

void CrazyCat::UpdateCharacter(int Delta)
{

	_character->UpdatePosition(Delta);

	RECT from = _Camera->GetViewport();

	int x = _character->getPosition().x - (_screenWidth / 2);
	//int y = _character->_position_y + (_screenHeight / 2);
	int y = _Camera->GetPositionCamera().y;

	if (x < 0)
		x = 0;
	if (x>(_mapMaxWidth - _screenWidth))
		x = (_mapMaxWidth - _screenWidth);
	if (y < _screenHeight)
		y = _screenHeight;
	if (y > _mapMaxHeight)
		y = _mapMaxHeight;
	_Camera->SetPositionCamera(D3DXVECTOR2(x, y));
}

void CrazyCat::LoadResources(LPDIRECT3DDEVICE9 d3ddv)
{
	//LoadBackground(MAP_TEXT_FILE, MAP_IMG_FILE, 41, 176, 95, 16, 16);
	_textPrint = new CText();
	_textPrint->Initialize(_directXDivice->getDevice(), TEXT("Times New Roman"), 70, 1);
	_Camera->SetPositionCamera(D3DXVECTOR2(0, 576));
	_mapMaxHeight = 576;
	_mapMaxWidth = 9600;
	_character = new CCharacter(_directXDivice->getSpriteHandler(), 100, 100, _mapMaxWidth, _mapMaxHeight);
	_tile_object = new CDynamicGameObject(1, 0, 32, 800, 32, 0.0f, 0.0f, _directXDivice->getSpriteHandler(), L"Tile.png", 1, 1);
}

int CrazyCat::LoadBackground(LPWSTR fileText, LPWSTR fileImage, int rows, int columns, int tiles, int tileWidth, int tileHeight)
{
	_textPrint = new CText();
	_textPrint->Initialize(_directXDivice->getDevice(), TEXT("Times New Roman"), 70, 1);
	//map = new Map();
	//_map = new Map(800, 576, 9600, 576);
	//_map->inital(_directXDivice->getDevice());
	//LPDIRECT3DSURFACE9 tile = LoadSurfaceFromFile(_directXDivice->getDevice(), L"Tile.png", D3DCOLOR_XRGB(255, 0, 255));

	//MapTiles *_tilesItem;
	//int **_tilesMatrix;
	//_tilesItem = new MapTiles[tiles];		// khởi tạo mảng với số lượng : tiles
	//_tilesMatrix = new int *[rows];		// khởi tạo ma trận với số dòng: rows
	//for (int i = 0; i < rows; i++)
	//{
	//	_tilesMatrix[i] = new int[columns];		// khởi tạo dòng ma trận với số cột: columns
	//}
	//ReadMapText(fileText, _tilesItem, _tilesMatrix, columns);
	//_mapMaxHeight = tileHeight*rows;
	//_mapMaxWidth = tileWidth*columns;


	//MapTest = new int*[25];
	//for (int i = 0; i < 25; i++)
	//{
	//	MapTest[i] = new int[150];		// khởi tạo dòng ma trận với số cột: columns
	//}
	//ReadMap(L"Map.txt", MapTest);

	//LPDIRECT3DSURFACE9 desImage = LoadSurfaceFromFile(_directXDivice->getDevice(), fileImage, D3DCOLOR_XRGB(255, 0, 255));
	/*HRESULT result;
	LPDIRECT3DSURFACE9 surface = NULL;
	result = _directXDivice->getDevice()->CreateOffscreenPlainSurface(tileWidth * columns, tileHeight * rows, D3DFMT_X8R8G8B8, D3DPOOL_DEFAULT, &surface, NULL);
	if (result != D3D_OK)
	return NULL;
	for (int i = 0; i < rows; i++)
	{
	for (int j = 0; j < columns; j++)
	{
	RECT from, to;
	from.left = _tilesItem[_tilesMatrix[i][j]]._x;
	from.top = _tilesItem[_tilesMatrix[i][j]]._y;
	from.right = from.left + tileWidth;
	from.bottom = from.top + tileHeight;

	to.left = j*tileWidth;
	to.top = i*tileHeight;
	to.right = to.left + tileWidth;
	to.bottom = to.top + tileHeight;

	_directXDivice->getDevice()->StretchRect(desImage, &from, surface, &to, D3DTEXF_NONE);
	}
	}*/
	//_background = tile;
	//_tile = tile;
	return 1;
}

void CrazyCat::RenderFrame(LPDIRECT3DDEVICE9 d3ddv, int t)
{
	/*if (mode != -1 && mode != 4){
		Sleep(1000);
	}*/
	CGame::RenderFrame(d3ddv, t);

	// Render background
	//d3ddv->StretchRect(
	//	_background,			// from 
	//	NULL,//&_background_partition,				// which portion?
	//	_directXDivice->getBackBuffer(),		// to 
	//	NULL,				// which portion?
	//	D3DTEXF_NONE);
	//map->draw(_directXDivice, this->_Camera->GetPositionCamera());

	//D3DXVECTOR2 pos =  _Camera->GetPositionCamera();
	//RECT src;
	//src.top = 544;
	//src.bottom = 576;
	//src.left = 0;
	//src.right = src.left + 800;

	////D3DXVECTOR2 posDes(pos.x + 100,pos.y - 200);
	////CCamera::Transform(_Camera->GetPositionCamera(), &posDes);
	//RECT des;
	//des.top = 300;
	//des.bottom = 332;
	//des.left = 0;
	//des.right = des.left + 800;
	//d3ddv->StretchRect(
	//					_tile,			// from 
	//					&src,//&_background_partition,				// which portion?
	//					_directXDivice->getBackBuffer(),		// to 
	//					&des,				// which portion?
	//					D3DTEXF_NONE);




	//wsprintfW(buffer, L"%d", (int)_character->_freeFallingTime);
	//_directXDivice->DrawString(100, 100, D3DCOLOR_XRGB(0, 0, 0), buffer);
	/*wsprintfW(buffer, L"%d", (int)_character->realDeltaTime);
	_directXDivice->DrawString(100, 50, D3DCOLOR_XRGB(0, 0, 0), buffer);*/

	/*if (now - last_time > 1000 / ANIMATE_RATE)
	{*/
	/*if (mode == 0)
	_directXDivice->DrawString(100, 100, D3DCOLOR_XRGB(0, 0, 0), L"NONE");
	if (mode == 1)
	_directXDivice->DrawString(100, 100, D3DCOLOR_XRGB(0, 0, 0), L"RIGHT");
	if (mode == 2)
	_directXDivice->DrawString(100, 100, D3DCOLOR_XRGB(0, 0, 0), L"LEFT");
	if (mode == 3)
	_directXDivice->DrawString(100, 100, D3DCOLOR_XRGB(0, 0, 0), L"SPACE");*/
	//last_time = now;
	//}

	_directXDivice->getSpriteHandler()->Begin(D3DXSPRITE_ALPHABLEND);
	_tile_object->draw(_Camera->GetPositionCamera());
	_character->RenderCharacter(_Camera->GetPositionCamera());
	/*for (int i = 0; i < 300; i++){
		_mtile->draw(_Camera->GetPositionCamera(), map->_listObject[i].x, map->_listObject[i].y);

	}*/
	_textPrint->Print(vyBuffer, 100, 100, D3DCOLOR_XRGB(0, 0, 0), 0, 0, 0, FA_RIGHT);
	_textPrint->Print(lalbelTest, 200, 100, D3DCOLOR_XRGB(0, 0, 0), 0, 0, 0, FA_RIGHT);
	
	_directXDivice->getSpriteHandler()->End();

	/*AutoBall_x += 1; if (AutoBall_x > 500){
	AutoBall_x = 0;
	}*/




	/*Ball_x += velocityx;
	Ball_y += velocityy;

	CBox ball(Ball_x, Ball_y, 128, 128, velocityx, velocityy);
	CBox AutoBall(AutoBall_x, AutoBall_y, 80, 40, 0, 0);

	RECT inRect;
	inRect.left = Ball_x;
	inRect.right = inRect.left + 128;
	inRect.top = 576-Ball_y;
	inRect.bottom = inRect.top + 128;

	RECT autob;
	autob.left = AutoBall_x;
	autob.right = autob.left+80;
	autob.top = 576-AutoBall_y;
	autob.bottom = autob.top+40;


	d3ddv->ColorFill(_directXDivice->getBackBuffer(), &inRect, D3DCOLOR_ARGB(0, 255, 0, 0));
	d3ddv->ColorFill(_directXDivice->getBackBuffer(), &autob, D3DCOLOR_ARGB(0, 255, 0, 255));


	float collisionTime = 0.0f;
	DIRECTION direction = DIRECTION::NONE;
	char* label;
	char* labelI;
	if (CCollision::Intersec(ball, AutoBall)){
	labelI = "Intersec";
	}
	else
	{
	labelI = "None Intersec";
	}

	if (CCollision::isCollision(ball, AutoBall,collisionTime,direction)){

	switch (direction)
	{
	case 1:
	label = "LEFT";
	break;
	case 3:
	label = "RIGHT";
	break;
	case 2:
	label = "TOP";
	break;
	case 4:
	label = "BOTTOM";
	break;
	default:
	label = "Không Xác Định Hướng";
	break;
	}
	mode = 1;
	}
	else{
	mode = -1;
	label = "Không xảy ra va chạm";
	}
	_textPrint->Print(label, 200, 100, D3DCOLOR_XRGB(0, 0, 0), 0, 0, 0, FA_RIGHT);
	_textPrint->Print(labelI, 200, 200, D3DCOLOR_XRGB(0, 0, 0), 0, 0, 0, FA_RIGHT);*/
}

void CrazyCat::ProcessInput(LPDIRECT3DDEVICE9 d3ddv, int t)
{
	if (_keyboardDevice->IsKeyDown(DIK_RIGHT))
	{
		_character->setVelocity( _character->getVelocity().x + 5, _character->getVelocity().y);
		//_character->
		//_character->UpdateCharacterMode(Character_Mode::Slide);
	}
	else if (_keyboardDevice->IsKeyDown(DIK_LEFT))
	{
		//velocityx = -5;
		_character->setVelocity(_character->getVelocity().x - 5, _character->getVelocity().y);
		//_character->UpdateCharacterMode(Character_Mode::Slide);
	}
	else if (_keyboardDevice->IsKeyDown(DIK_UP))
	{
		//velocityy = 5;
		_character->setVelocity(_character->getVelocity().x , _character->getVelocity().y +5);
		//_character->UpdateCharacterMode(Character_Mode::Slide);
	}
	else if (_keyboardDevice->IsKeyDown(DIK_DOWN))
	{
		//velocityy = -5;
		_character->setVelocity(_character->getVelocity().x, _character->getVelocity().y-5);
		//_character->UpdateCharacterMode(Character_Mode::Slide);
	}
	/*else if (_keyboardDevice->IsKeyDown(DIK_UP))
	{
	_character->UpdateCharacterMode(Character_Mode::Walk);
	}
	else if (_keyboardDevice->IsKeyDown(DIK_LEFT))
	{
	_character->UpdateCharacterMode(Character_Mode::Dead);
	}
	else
	_character->UpdateCharacterMode(Character_Mode::Run);*/
}

void CrazyCat::OnKeyDown(int KeyCode)
{
	switch (KeyCode)
	{
	case DIK_SPACE:
		//_character->UpdateCharacterMode(Character_Mode::Jump);
		_character->Jumping(_deltaTime);
		break;
	case DIK_D:
		_character->dead();
		break;
	case DIK_H:
		//_character->_isHurt = true;
		//_character->_hurtDrawCount = 0;
		//_character->UpdateCharacterMode(Character_Mode::Hurt);
		break;
	case DIK_C:
		////if (_character->_mode == Character_Mode::Run)
		//	_character->UpdateCharacterMode(Character_Mode::Slide);
		//else if (_character->_mode == Character_Mode::Slide)
		//	_character->UpdateCharacterMode(Character_Mode::Walk);
		//else if (_character->_mode == Character_Mode::Walk)
		//	_character->UpdateCharacterMode(Character_Mode::Run);
		//else
		//	_character->UpdateCharacterMode(Character_Mode::Run);
		//_character->_isDead = false;
		//_character->_deadDrawCount = 0;
		break;
	}
}

void CrazyCat::OnKeyUp(int KeyCode)
{
	switch (KeyCode)
	{
	case DIK_SPACE:
		break;
	}
}


