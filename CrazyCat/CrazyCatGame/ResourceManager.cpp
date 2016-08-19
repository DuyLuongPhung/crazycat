#include "ResourceManager.h"


ResourceManager::ResourceManager()
{
}


ResourceManager::~ResourceManager()
{
}

void ResourceManager::inital(CDirectX * directx){
	/* Load các sprite */
	this->_list_sprites.push_back(new SpriteResource(ID_TILEBOX_NORMAL, directx->getSpriteHandler(), IMG_TILEBOX_NORMAL,
		WIDTH_OBJECT, HEIGHT_OBJECT, 1, 1, NULL));
	this->_list_sprites.push_back(new SpriteResource(ID_GIFTBOX_COIN, directx->getSpriteHandler(), IMG_GIFTBOX_COIN,
		WIDTH_OBJECT, HEIGHT_OBJECT, 1, 1, NULL));
	this->_list_sprites.push_back(new SpriteResource(ID_GIFTBOX_HEART, directx->getSpriteHandler(), IMG_GIFTBOX_HEART,
		WIDTH_OBJECT, HEIGHT_OBJECT, 1, 1, NULL));
	this->_list_sprites.push_back(new SpriteResource(ID_GIFTBOX_TIME, directx->getSpriteHandler(), IMG_GIFTBOX_TIME,
		WIDTH_OBJECT, HEIGHT_OBJECT, 1, 1, NULL));
	this->_list_sprites.push_back(new SpriteResource(ID_GIFTBOX_VELOCITY, directx->getSpriteHandler(), IMG_GIFTBOX_VELOCITY,
		WIDTH_OBJECT, HEIGHT_OBJECT, 1, 1, NULL));
	this->_list_sprites.push_back(new SpriteResource(ID_GIFTBOX_KEY, directx->getSpriteHandler(), IMG_GIFTBOX_KEY,
		WIDTH_OBJECT, HEIGHT_OBJECT, 1, 1, NULL));
	this->_list_sprites.push_back(new SpriteResource(ID_DOOR, directx->getSpriteHandler(), IMG_DOOR,
		WIDTH_OBJECT, HEIGHT_OBJECT, 5, 5, NULL));

	this->_list_sprites.push_back(new SpriteResource(ID_BOMB_NORMAL, directx->getSpriteHandler(), IMG_BOMB_NORMAL,
		WIDTH_OBJECT, HEIGHT_OBJECT, 3, 3, NULL));
	this->_list_sprites.push_back(new SpriteResource(ID_BOMB_SUPER, directx->getSpriteHandler(), IMG_BOMB_SUPER,
		WIDTH_OBJECT, HEIGHT_OBJECT, 3, 3, NULL));
	this->_list_sprites.push_back(new SpriteResource(ID_FIREBANG_LEFT, directx->getSpriteHandler(), IMG_FIREBANG_LEFT,
		WIDTH_OBJECT, HEIGHT_OBJECT, 4, 4, NULL));
	this->_list_sprites.push_back(new SpriteResource(ID_FIREBANG_RIGHT, directx->getSpriteHandler(), IMG_FIREBANG_RIGHT,
		WIDTH_OBJECT, HEIGHT_OBJECT, 4, 4, NULL));
	this->_list_sprites.push_back(new SpriteResource(ID_FIREBANG_TOP, directx->getSpriteHandler(), IMG_FIREBANG_TOP,
		WIDTH_OBJECT, HEIGHT_OBJECT, 4, 4, NULL));
	this->_list_sprites.push_back(new SpriteResource(ID_FIREBANG_BOT, directx->getSpriteHandler(), IMG_FIREBANG_BOT,
		WIDTH_OBJECT, HEIGHT_OBJECT, 4, 4, NULL));
	this->_list_sprites.push_back(new SpriteResource(ID_FIREBANG_MIDLR, directx->getSpriteHandler(), IMG_FIREBANG_MIDLR,
		WIDTH_OBJECT, HEIGHT_OBJECT, 4, 4, NULL));
	this->_list_sprites.push_back(new SpriteResource(ID_FIREBANG_MIDTB, directx->getSpriteHandler(), IMG_FIREBANG_MIDTB,
		WIDTH_OBJECT, HEIGHT_OBJECT, 4, 4, NULL));
	this->_list_sprites.push_back(new SpriteResource(ID_FIREBANG_CENTER, directx->getSpriteHandler(), IMG_FIREBANG_CENTER,
		WIDTH_OBJECT, HEIGHT_OBJECT, 4, 4, NULL));
}

CSprite* ResourceManager::getSpriteWithID(int id){
	for (int i = 0; i < this->_list_sprites.size(); i++){
		if (this->_list_sprites.at(i)->getId() == id){
			CSprite* spriteResult = new CSprite();
			*spriteResult = *(this->_list_sprites.at(i)->getData());
			return spriteResult;
		}
	}
	return NULL;
}
