#include "SoundManager.h"


SoundManager *SoundManager::_instance = NULL;

SoundManager::SoundManager()
{
	this->_list_sound_resource.clear();
}


SoundManager::~SoundManager()
{
}

SoundManager *SoundManager::GetInstance()
{
	if (_instance == NULL)
	{
		_instance = new SoundManager();
	}
	return _instance;
}

void SoundManager::inital(CDirectX * directx){
	this->_list_sound_resource.push_back(new SoundResource(ID_SOUND_BACKGROUND, directx->getSoundDevice(), SOUND_BACKGROUND));
	this->_list_sound_resource.push_back(new SoundResource(ID_SOUND_GAME_START, directx->getSoundDevice(), SOUND_GAME_START));
	this->_list_sound_resource.push_back(new SoundResource(ID_SOUND_MAP_START, directx->getSoundDevice(), SOUND_MAP_START));
	this->_list_sound_resource.push_back(new SoundResource(ID_SOUND_ADD_BOMB, directx->getSoundDevice(), SOUND_ADD_BOMB));
	this->_list_sound_resource.push_back(new SoundResource(ID_SOUND_BOMBER_WALK, directx->getSoundDevice(), SOUND_BOMBER_WALK));
	this->_list_sound_resource.push_back(new SoundResource(ID_SOUND_GAME_OVER, directx->getSoundDevice(), SOUND_GAME_OVER));
	this->_list_sound_resource.push_back(new SoundResource(ID_SOUND_NORMAL_BOMB, directx->getSoundDevice(), SOUND_NORMAL_BOMB));
	this->_list_sound_resource.push_back(new SoundResource(ID_SOUND_PAUSE, directx->getSoundDevice(), SOUND_PAUSE));
	this->_list_sound_resource.push_back(new SoundResource(ID_SOUND_PICK_ITEM, directx->getSoundDevice(), SOUND_PICK_ITEM));
	this->_list_sound_resource.push_back(new SoundResource(ID_SOUND_SUPER_BOMB, directx->getSoundDevice(), SOUND_SUPER_BOMB));
	this->_list_sound_resource.push_back(new SoundResource(ID_SOUND_TIME_OVER, directx->getSoundDevice(), SOUND_TIME_OVER));
	this->_list_sound_resource.push_back(new SoundResource(ID_SOUND_WINNER, directx->getSoundDevice(), SOUND_WINNER));
}

Sound* SoundManager::getSoundWithID(int id){
	for (int i = 0; i < this->_list_sound_resource.size(); i++){
		if (this->_list_sound_resource.at(i)->getId() == id){
			Sound* soundResult = new Sound();
			*soundResult = *(this->_list_sound_resource.at(i)->getSound());
			return soundResult;
		}
	}
	return NULL;
}

void SoundManager::Release()
{
	this->_list_sound_resource.clear();
}
