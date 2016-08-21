#include "PlayMapMgt.h"


PlayMapMgt::PlayMapMgt(ResourceManager * resourceMgt)
{
	this->_list_map.clear();
	this->_list_gamebar.clear();
	this->_b_live = 0;
	this->_b_gold = 0;
	this->_b_keys = 0;
	this->_b_bomber_man = NULL;
	this->_collision = NULL;
	this->_current_map = -1;
	this->_b_map_times = 0;
	this->_b_camera = NULL;
	this->_screen_width = 0;
	this->_screen_height = 0;
	this->_resourceMgt = resourceMgt;
	this->_return_menu = false;
	this->_play_sound_bg = false;
	this->_fisrt_update_map = false;
}


PlayMapMgt::~PlayMapMgt()
{
	SAFE_DELETE(this->_b_bomber_man);
	SAFE_DELETE(this->_collision);
	SAFE_DELETE(this->_b_camera);
	SoundManager::GetInstance()->Release();
}

void PlayMapMgt::inital(CDirectX * directX, int screenWidth, int screenHeight){

	// tạo ra các map và add vào danh sách tuy nhiên chưa khởi động cũng như chưa load map
	this->_list_map.clear();
	Map *map1 = new Map("White Farm", MAP_01_IMG_FILE, MAP_01_TEXT_FILE, MAP_01_INFO_FILE, MAP_01_TIME_MAP, MAP_01_NEED_KEYS);
	map1->inital(directX->getDevice(), this->_resourceMgt);
	this->_list_map.push_back(map1);

	Map *map2 = new Map("Black Farm", MAP_02_IMG_FILE, MAP_02_TEXT_FILE, MAP_02_INFO_FILE, MAP_02_TIME_MAP, MAP_02_NEED_KEYS);
	map2->inital(directX->getDevice(), this->_resourceMgt);
	this->_list_map.push_back(map2);

	// tạo ra các thanh gamebar và add vào list
	this->_list_gamebar.clear();
	GameBar *heartBar = new GameBar();
	heartBar->inital(GAMEBAR_HEART_BAR_ID, directX->getDevice(), directX->getSpriteHandler(), GAMEBAR_HEART_BAR_IMG_FILE, GAMEBAR_WIDTH, GAMEBAR_HEIGHT,
		D3DXVECTOR2(GAMEBAR_HEART_BAR_X, GAMEBAR_HEART_BAR_Y), CBox(GAMEBAR_TEXT_X, GAMEBAR_TEXT_Y, GAMEBAR_TEXT_WIDTH, GAMEBAR_TEXT_HEIGHT), DEFAULT_LIVE);
	this->_list_gamebar.push_back(heartBar);

	GameBar *keyBar = new KeyGameBar();
	keyBar->inital(GAMEBAR_KEY_BAR_ID, directX->getDevice(), directX->getSpriteHandler(), GAMEBAR_KEY_BAR_IMG_FILE, GAMEBAR_WIDTH, GAMEBAR_HEIGHT,
		D3DXVECTOR2(GAMEBAR_KEY_BAR_X, GAMEBAR_KEY_BAR_Y), CBox(GAMEBAR_TEXT_X, GAMEBAR_TEXT_Y, GAMEBAR_TEXT_WIDTH, GAMEBAR_TEXT_HEIGHT), 0);
	this->_list_gamebar.push_back(keyBar);

	GameBar *goldBar = new GameBar();
	goldBar->inital(GAMEBAR_GOLD_BAR_ID, directX->getDevice(), directX->getSpriteHandler(), GAMEBAR_GOLD_BAR_IMG_FILE, GAMEBAR_WIDTH, GAMEBAR_HEIGHT,
		D3DXVECTOR2(GAMEBAR_GOLD_BAR_X, GAMEBAR_GOLD_BAR_Y), CBox(GAMEBAR_TEXT_X, GAMEBAR_TEXT_Y, GAMEBAR_TEXT_WIDTH, GAMEBAR_TEXT_HEIGHT), 0);
	this->_list_gamebar.push_back(goldBar);

	GameBar *timeBar = new TimeGameBar();
	timeBar->inital(GAMEBAR_TIME_BAR_ID, directX->getDevice(), directX->getSpriteHandler(), GAMEBAR_TIME_BAR_IMG_FILE, GAMEBAR_WIDTH, GAMEBAR_HEIGHT,
		D3DXVECTOR2(GAMEBAR_TIME_BAR_X, GAMEBAR_TIME_BAR_Y), CBox(GAMEBAR_TEXT_X - 5, GAMEBAR_TEXT_Y, GAMEBAR_TEXT_WIDTH, GAMEBAR_TEXT_HEIGHT), 0);
	this->_list_gamebar.push_back(timeBar);

	GameBar *superBombdBar = new GameBar();
	superBombdBar->inital(GAMEBAR_SUPERBOMB_BAR_ID, directX->getDevice(), directX->getSpriteHandler(), GAMEBAR_SUPERBOMB_BAR_IMG_FILE, GAMEBAR_WIDTH, GAMEBAR_HEIGHT,
		D3DXVECTOR2(GAMEBAR_SUPERBOMB_BAR_X, GAMEBAR_SUPERBOMB_BAR_Y), CBox(40, GAMEBAR_TEXT_Y, GAMEBAR_TEXT_WIDTH, GAMEBAR_TEXT_HEIGHT), 0);
	this->_list_gamebar.push_back(superBombdBar);

	// khởi tạo nhân vật
	this->_b_bomber_man = new CCharacter(BOMBER_START_X, BOMBER_START_Y);
	this->_b_bomber_man->inital(directX->getSpriteHandler());

	// khởi tạo biến xét va chạm
	_collision = new CCollision();

	// khởi tạo camera
	this->_screen_width = screenWidth;
	this->_screen_height = screenHeight;
	this->_b_camera = new CCamera(screenWidth, screenHeight);

	//this->nextMap();
	this->_super_boom = true;
	this->_play_sound_bg = false;

	// font
	this->_gb_text_mgt = new CText();
	this->_gb_text_mgt->Initialize(directX->getDevice(), TEXT("Times New Roman"), 30, 1);

	// màn hình bắt đầu map và game over
	this->_game_over_background = LoadSurfaceFromFile(directX->getDevice(), MAP_GAME_OVER_IMG, NULL);
	this->_start_map_background = LoadSurfaceFromFile(directX->getDevice(), MAP_START_MAP_IMG, NULL);
}

void PlayMapMgt::resetCurrentMap(){
	this->_b_live = DEFAULT_LIVE;
	this->_b_keys = 0;
	if (this->_list_map.size() > this->_current_map && this->_current_map >= 0)
		this->_b_map_times = this->_list_map.at(this->_current_map)->getMaximumTimes();
	else
		this->_b_map_times = 0;
	if (this->_b_bomber_man != NULL){
		this->_b_bomber_man->setPosition(BOMBER_START_X, BOMBER_START_Y);
		this->_b_bomber_man->setVelocity(0.0f, 0.0f);
	}
	this->_is_game_over = false;
	this->_return_menu = false;
	this->_fisrt_update_map = false;
}

void PlayMapMgt::defaultMap(){
	if (this->_list_map.size() > 0)
	{
		this->_current_map = 0;
	}
	else
		this->_current_map = -1;
	this->_super_bomb_count = 0;
	this->resetCurrentMap();
	this->startMap();
	for (int i = 0; i < this->_list_gamebar.size(); i++){
		if (this->_list_gamebar.at(i)->getId() == GAMEBAR_KEY_BAR_ID){
			((KeyGameBar*)this->_list_gamebar.at(i))->setMaxKeys(this->_list_map.at(this->_current_map)->getNeedKeys());
			break;
		}
	}
}

void PlayMapMgt::nextMap(){
	if (this->_list_map.size() > 0)
	{
		this->_current_map = (this->_current_map + 1) % (this->_list_map.size());
	}
	else
		this->_current_map = -1;
	this->_super_bomb_count = 0;
	this->resetCurrentMap();
	this->startMap();
	for (int i = 0; i < this->_list_gamebar.size(); i++){
		if (this->_list_gamebar.at(i)->getId() == GAMEBAR_KEY_BAR_ID){
			((KeyGameBar*)this->_list_gamebar.at(i))->setMaxKeys(this->_list_map.at(this->_current_map)->getNeedKeys());
			break;
		}
	}
}

void PlayMapMgt::startMap(){
	this->_is_game_starting = true;
	this->_time_waiting_start = GetTickCount();
	this->_fisrt_update_map = false;
}

void PlayMapMgt::gameOver(){
	this->_is_game_over = true;
	this->_time_waiting_gameover = GetTickCount();
	this->_play_sound_bg = false;
	SoundManager::GetInstance()->getSoundWithID(ID_SOUND_BACKGROUND)->Stop();
	SoundManager::GetInstance()->getSoundWithID(ID_SOUND_GAME_OVER)->Play();
	this->_return_menu = false;
}

void PlayMapMgt::activedNormalBomb(int i){

	FireBang* centerFirebang = new FireBang(ID_FIREBANG_CENTER,
		this->_list_map.at(this->_current_map)->_list_objects.at(i)->getPosition().x,
		this->_list_map.at(this->_current_map)->_list_objects.at(i)->getPosition().y,
		this->_list_map.at(this->_current_map)->_list_objects.at(i)->getWidth(),
		this->_list_map.at(this->_current_map)->_list_objects.at(i)->getHeight(),
		this->_resourceMgt->getSpriteWithID(ID_FIREBANG_CENTER),
		FIREBANG_EXIST_TIME);
	centerFirebang->inital(NULL);
	this->_list_map.at(this->_current_map)->_list_objects.push_back(centerFirebang);

	FireBang* leftFirebang = new FireBang(ID_FIREBANG_LEFT,
		this->_list_map.at(this->_current_map)->_list_objects.at(i)->getPosition().x - WIDTH_OBJECT + 2,
		this->_list_map.at(this->_current_map)->_list_objects.at(i)->getPosition().y,
		this->_list_map.at(this->_current_map)->_list_objects.at(i)->getWidth(),
		this->_list_map.at(this->_current_map)->_list_objects.at(i)->getHeight(),
		this->_resourceMgt->getSpriteWithID(ID_FIREBANG_LEFT),
		FIREBANG_EXIST_TIME);
	leftFirebang->inital(NULL);
	this->_list_map.at(this->_current_map)->_list_objects.push_back(leftFirebang);

	FireBang* rightFirebang = new FireBang(ID_FIREBANG_RIGHT,
		this->_list_map.at(this->_current_map)->_list_objects.at(i)->getPosition().x + WIDTH_OBJECT - 2,
		this->_list_map.at(this->_current_map)->_list_objects.at(i)->getPosition().y,
		this->_list_map.at(this->_current_map)->_list_objects.at(i)->getWidth(),
		this->_list_map.at(this->_current_map)->_list_objects.at(i)->getHeight(),
		this->_resourceMgt->getSpriteWithID(ID_FIREBANG_RIGHT),
		FIREBANG_EXIST_TIME);
	rightFirebang->inital(NULL);
	this->_list_map.at(this->_current_map)->_list_objects.push_back(rightFirebang);

	FireBang* topFirebang = new FireBang(ID_FIREBANG_TOP,
		this->_list_map.at(this->_current_map)->_list_objects.at(i)->getPosition().x,
		this->_list_map.at(this->_current_map)->_list_objects.at(i)->getPosition().y + HEIGHT_OBJECT - 2,
		this->_list_map.at(this->_current_map)->_list_objects.at(i)->getWidth(),
		this->_list_map.at(this->_current_map)->_list_objects.at(i)->getHeight(),
		this->_resourceMgt->getSpriteWithID(ID_FIREBANG_TOP),
		FIREBANG_EXIST_TIME);
	topFirebang->inital(NULL);
	this->_list_map.at(this->_current_map)->_list_objects.push_back(topFirebang);

	FireBang* bottomFirebang = new FireBang(ID_FIREBANG_BOT,
		this->_list_map.at(this->_current_map)->_list_objects.at(i)->getPosition().x,
		this->_list_map.at(this->_current_map)->_list_objects.at(i)->getPosition().y - HEIGHT_OBJECT + 2,
		this->_list_map.at(this->_current_map)->_list_objects.at(i)->getWidth(),
		this->_list_map.at(this->_current_map)->_list_objects.at(i)->getHeight(),
		this->_resourceMgt->getSpriteWithID(ID_FIREBANG_BOT),
		FIREBANG_EXIST_TIME);
	bottomFirebang->inital(NULL);
	SoundManager::GetInstance()->getSoundWithID(ID_SOUND_NORMAL_BOMB)->Play();
	this->_list_map.at(this->_current_map)->_list_objects.push_back(bottomFirebang);
}

void PlayMapMgt::activedSuperBomb(int i){
	FireBang* centerFirebang = new FireBang(ID_FIREBANG_CENTER,
		this->_list_map.at(this->_current_map)->_list_objects.at(i)->getPosition().x,
		this->_list_map.at(this->_current_map)->_list_objects.at(i)->getPosition().y,
		this->_list_map.at(this->_current_map)->_list_objects.at(i)->getWidth(),
		this->_list_map.at(this->_current_map)->_list_objects.at(i)->getHeight(),
		this->_resourceMgt->getSpriteWithID(ID_FIREBANG_CENTER),
		FIREBANG_EXIST_TIME);
	centerFirebang->inital(NULL);
	this->_list_map.at(this->_current_map)->_list_objects.push_back(centerFirebang);

	FireBang* leftMidFirebang = new FireBang(ID_FIREBANG_MIDLR,
		this->_list_map.at(this->_current_map)->_list_objects.at(i)->getPosition().x - WIDTH_OBJECT + 2,
		this->_list_map.at(this->_current_map)->_list_objects.at(i)->getPosition().y,
		this->_list_map.at(this->_current_map)->_list_objects.at(i)->getWidth(),
		this->_list_map.at(this->_current_map)->_list_objects.at(i)->getHeight(),
		this->_resourceMgt->getSpriteWithID(ID_FIREBANG_MIDLR),
		FIREBANG_EXIST_TIME);
	leftMidFirebang->inital(NULL);
	this->_list_map.at(this->_current_map)->_list_objects.push_back(leftMidFirebang);

	FireBang* rightMidFirebang = new FireBang(ID_FIREBANG_MIDLR,
		this->_list_map.at(this->_current_map)->_list_objects.at(i)->getPosition().x + WIDTH_OBJECT - 2,
		this->_list_map.at(this->_current_map)->_list_objects.at(i)->getPosition().y,
		this->_list_map.at(this->_current_map)->_list_objects.at(i)->getWidth(),
		this->_list_map.at(this->_current_map)->_list_objects.at(i)->getHeight(),
		this->_resourceMgt->getSpriteWithID(ID_FIREBANG_MIDLR),
		FIREBANG_EXIST_TIME);
	rightMidFirebang->inital(NULL);
	this->_list_map.at(this->_current_map)->_list_objects.push_back(rightMidFirebang);

	FireBang* topMidFirebang = new FireBang(ID_FIREBANG_MIDTB,
		this->_list_map.at(this->_current_map)->_list_objects.at(i)->getPosition().x,
		this->_list_map.at(this->_current_map)->_list_objects.at(i)->getPosition().y + HEIGHT_OBJECT - 2,
		this->_list_map.at(this->_current_map)->_list_objects.at(i)->getWidth(),
		this->_list_map.at(this->_current_map)->_list_objects.at(i)->getHeight(),
		this->_resourceMgt->getSpriteWithID(ID_FIREBANG_MIDTB),
		FIREBANG_EXIST_TIME);
	topMidFirebang->inital(NULL);
	this->_list_map.at(this->_current_map)->_list_objects.push_back(topMidFirebang);

	FireBang* bottomMidFirebang = new FireBang(ID_FIREBANG_MIDTB,
		this->_list_map.at(this->_current_map)->_list_objects.at(i)->getPosition().x,
		this->_list_map.at(this->_current_map)->_list_objects.at(i)->getPosition().y - HEIGHT_OBJECT + 2,
		this->_list_map.at(this->_current_map)->_list_objects.at(i)->getWidth(),
		this->_list_map.at(this->_current_map)->_list_objects.at(i)->getHeight(),
		this->_resourceMgt->getSpriteWithID(ID_FIREBANG_MIDTB),
		FIREBANG_EXIST_TIME);
	bottomMidFirebang->inital(NULL);
	this->_list_map.at(this->_current_map)->_list_objects.push_back(bottomMidFirebang);

	FireBang* leftFirebang = new FireBang(ID_FIREBANG_LEFT,
		this->_list_map.at(this->_current_map)->_list_objects.at(i)->getPosition().x - WIDTH_OBJECT + 2 + (-WIDTH_OBJECT + 2),
		this->_list_map.at(this->_current_map)->_list_objects.at(i)->getPosition().y,
		this->_list_map.at(this->_current_map)->_list_objects.at(i)->getWidth(),
		this->_list_map.at(this->_current_map)->_list_objects.at(i)->getHeight(),
		this->_resourceMgt->getSpriteWithID(ID_FIREBANG_LEFT),
		FIREBANG_EXIST_TIME);
	leftFirebang->inital(NULL);
	this->_list_map.at(this->_current_map)->_list_objects.push_back(leftFirebang);

	FireBang* rightFirebang = new FireBang(ID_FIREBANG_RIGHT,
		this->_list_map.at(this->_current_map)->_list_objects.at(i)->getPosition().x + WIDTH_OBJECT - 2 + (WIDTH_OBJECT - 2),
		this->_list_map.at(this->_current_map)->_list_objects.at(i)->getPosition().y,
		this->_list_map.at(this->_current_map)->_list_objects.at(i)->getWidth(),
		this->_list_map.at(this->_current_map)->_list_objects.at(i)->getHeight(),
		this->_resourceMgt->getSpriteWithID(ID_FIREBANG_RIGHT),
		FIREBANG_EXIST_TIME);
	rightFirebang->inital(NULL);
	this->_list_map.at(this->_current_map)->_list_objects.push_back(rightFirebang);

	FireBang* topFirebang = new FireBang(ID_FIREBANG_TOP,
		this->_list_map.at(this->_current_map)->_list_objects.at(i)->getPosition().x,
		this->_list_map.at(this->_current_map)->_list_objects.at(i)->getPosition().y + HEIGHT_OBJECT - 2 + (HEIGHT_OBJECT - 2),
		this->_list_map.at(this->_current_map)->_list_objects.at(i)->getWidth(),
		this->_list_map.at(this->_current_map)->_list_objects.at(i)->getHeight(),
		this->_resourceMgt->getSpriteWithID(ID_FIREBANG_TOP),
		FIREBANG_EXIST_TIME);
	topFirebang->inital(NULL);
	this->_list_map.at(this->_current_map)->_list_objects.push_back(topFirebang);

	FireBang* bottomFirebang = new FireBang(ID_FIREBANG_BOT,
		this->_list_map.at(this->_current_map)->_list_objects.at(i)->getPosition().x,
		this->_list_map.at(this->_current_map)->_list_objects.at(i)->getPosition().y - HEIGHT_OBJECT + 2 + (-HEIGHT_OBJECT + 2),
		this->_list_map.at(this->_current_map)->_list_objects.at(i)->getWidth(),
		this->_list_map.at(this->_current_map)->_list_objects.at(i)->getHeight(),
		this->_resourceMgt->getSpriteWithID(ID_FIREBANG_BOT),
		FIREBANG_EXIST_TIME);
	bottomFirebang->inital(NULL);
	SoundManager::GetInstance()->getSoundWithID(ID_SOUND_SUPER_BOMB)->Play();
	this->_list_map.at(this->_current_map)->_list_objects.push_back(bottomFirebang);
}

void PlayMapMgt::bomberDied(){
	if (this->_b_bomber_man->isDeading())
		return;

	this->_b_live -= 1;
	this->_b_bomber_man->Dead();
}

void PlayMapMgt::update(int deltaTime, CDirectX * directX){

	if (!this->_is_game_over && this->_b_map_times < 1)
	{
		this->gameOver();
		SoundManager::GetInstance()->getSoundWithID(ID_SOUND_TIME_OVER)->Play();
		return;
	}

	if (this->_super_bomb_count > 0)
		this->_super_boom = true;
	else
		this->_super_boom = false;

	DWORD now = GetTickCount();
	if (this->_is_game_over && (now - this->_time_waiting_gameover) > MAP_TIME_WAITING){
		this->_return_menu = true;
		return;
	}

	if (this->_b_live < 0 && !this->_b_bomber_man->isDeading() && !this->_is_game_over){
		this->gameOver();
		return;
	}

	if (this->_is_game_starting && (now - this->_time_waiting_start) > MAP_TIME_WAITING){
		this->_is_game_starting = false;
	}

	if (this->_is_game_over || this->_is_game_starting)
		return;
	if (!this->_fisrt_update_map){
		this->_fisrt_update_map = true;
		SoundManager::GetInstance()->getSoundWithID(ID_SOUND_MAP_START)->Play();
	}

	if (!this->_play_sound_bg){
		this->_play_sound_bg = true;
		SoundManager::GetInstance()->getSoundWithID(ID_SOUND_BACKGROUND)->Repeat();
	}

	if (this->_list_map.size() <= this->_current_map){
		return;
	}

	this->_list_map.at(this->_current_map)->update(this->_b_camera->GetPositionCamera(), this->_screen_width, this->_screen_height);

	// cập nhật bomber man
	this->_b_bomber_man->update(deltaTime);

	// lấy khung của bomber man
	CBox characterBox = this->_b_bomber_man->getBounding();

	// cập nhật các đối tượng trong map
	// xóa các đối tượng: bom đã nổ, đường nổ đã kết thúc, đường nổ va chạm với tường
	for (int i = 0; i < this->_list_map.at(this->_current_map)->_list_objects.size(); i++){
		int objectID = this->_list_map.at(this->_current_map)->_list_objects.at(i)->getId();
		switch (objectID)
		{
		case ID_BOMB_NORMAL:
			// kiểm tra bom đã nổ: xóa bom và sinh ra 5 đường đạn tương ứng
			if (((Bomb*)(this->_list_map.at(this->_current_map)->_list_objects.at(i)))->IsFired())
			{
				activedNormalBomb(i);
				this->_list_map.at(this->_current_map)->_list_objects.erase(
					this->_list_map.at(this->_current_map)->_list_objects.begin() + i--);
				break;
			}
			// cập nhật nếu chưa nổ
			else
				this->_list_map.at(this->_current_map)->_list_objects.at(i)->update(deltaTime);
			break;
		case ID_BOMB_SUPER:
			// kiểm tra bom đã nổ: xóa bom và sinh ra 9 đường đạn tương ứng
			if (((Bomb*)(this->_list_map.at(this->_current_map)->_list_objects.at(i)))->IsFired())
			{
				activedSuperBomb(i);
				this->_list_map.at(this->_current_map)->_list_objects.erase(
					this->_list_map.at(this->_current_map)->_list_objects.begin() + i--);
				break;
			}
			// cập nhật nếu chưa nổ
			else
				this->_list_map.at(this->_current_map)->_list_objects.at(i)->update(deltaTime);
			break;
		case ID_FIREBANG_LEFT: case ID_FIREBANG_RIGHT:case ID_FIREBANG_TOP: case ID_FIREBANG_BOT: case ID_FIREBANG_CENTER:
		case ID_FIREBANG_MIDLR: case ID_FIREBANG_MIDTB:
		{
			// kiểm tra xem đã nổ xong chưa? nếu đã nổ xong thì xóa khỏi danh sách
			if (((FireBang*)(this->_list_map.at(this->_current_map)->_list_objects.at(i)))->isFiredBang())
			{
				this->_list_map.at(this->_current_map)->_list_objects.erase(
					this->_list_map.at(this->_current_map)->_list_objects.begin() + i--);
				break;
			}

			// kiểm tra xem có xảy ra va chạm với các đối tượng khác hay ko?
			bool flag = false;
			for (int j = 0; j < this->_list_map.at(this->_current_map)->_list_objects.size(); j++){

				int checkObjId = this->_list_map.at(this->_current_map)->_list_objects.at(j)->getId();

				// kiểm tra nếu đường bom nổ sinh ra va chạm với tường nó sẽ bị xóa đi
				if (checkObjId == ID_BRICK){
					CBox tileBox1 = this->_list_map.at(this->_current_map)->_list_objects.at(j)->getBounding();
					CBox tileBox2 = this->_list_map.at(this->_current_map)->_list_objects.at(i)->getBounding();
					if (tileBox1.IsIntersectedWith(tileBox2)){
						this->_list_map.at(this->_current_map)->_list_objects.erase(
							this->_list_map.at(this->_current_map)->_list_objects.begin() + i--);
						flag = true;
						break;
					}
				}
			}
			if (flag)
				break;

			for (int j = 0; j < this->_list_map.at(this->_current_map)->_list_objects.size(); j++){

				int checkObjId = this->_list_map.at(this->_current_map)->_list_objects.at(j)->getId();

				// kiểm tra nếu đường đạn nổ sinh ra va chạm với các tilebox
				if (checkObjId == ID_TILEBOX_NORMAL ||
					checkObjId == ID_TILEBOX_COIN ||
					checkObjId == ID_TILEBOX_HEART ||
					checkObjId == ID_TILEBOX_TIME ||
					checkObjId == ID_TILEBOX_VELOCITY ||
					checkObjId == ID_TILEBOX_SUPERBOMB){
					CBox tileBox1 = this->_list_map.at(this->_current_map)->_list_objects.at(j)->getBounding();
					CBox tileBox2 = this->_list_map.at(this->_current_map)->_list_objects.at(i)->getBounding();
					if (tileBox1.IsIntersectedWith(tileBox2)){
						// sinh ra các hộp quà (nếu có)
						if (checkObjId != ID_TILEBOX_NORMAL){
							int giftBoxId = -1;
							switch (checkObjId){
							case ID_TILEBOX_COIN:
							{
								CGameObject * objAdd = new GiftBox(ID_GIFTBOX_COIN, -1, tileBox1.x, tileBox1.y, tileBox1.w, tileBox1.h,
									this->_resourceMgt->getSpriteWithID(ID_GIFTBOX_COIN));
								this->_list_map.at(this->_current_map)->_list_objects.push_back(objAdd);
								break;
							}
							case ID_TILEBOX_HEART:
							{
								CGameObject * objAdd = new GiftBox(ID_GIFTBOX_HEART, -1, tileBox1.x, tileBox1.y, tileBox1.w, tileBox1.h,
									this->_resourceMgt->getSpriteWithID(ID_GIFTBOX_HEART));
								this->_list_map.at(this->_current_map)->_list_objects.push_back(objAdd);
								break;
							}
							case ID_TILEBOX_TIME:
							{
								CGameObject * objAdd = new GiftBox(ID_GIFTBOX_TIME, -1, tileBox1.x, tileBox1.y, tileBox1.w, tileBox1.h,
									this->_resourceMgt->getSpriteWithID(ID_GIFTBOX_TIME));
								this->_list_map.at(this->_current_map)->_list_objects.push_back(objAdd);
								break;
							}
							case ID_TILEBOX_VELOCITY:
							{
								CGameObject * objAdd = new GiftBox(ID_GIFTBOX_VELOCITY, -1, tileBox1.x, tileBox1.y, tileBox1.w, tileBox1.h,
									this->_resourceMgt->getSpriteWithID(ID_GIFTBOX_VELOCITY));
								this->_list_map.at(this->_current_map)->_list_objects.push_back(objAdd);
								break;
							}
							case ID_TILEBOX_SUPERBOMB:
							{
								CGameObject * objAdd = new GiftBox(ID_GIFTBOX_SUPERBOMB, -1, tileBox1.x, tileBox1.y, tileBox1.w, tileBox1.h,
									this->_resourceMgt->getSpriteWithID(ID_GIFTBOX_SUPERBOMB));
								this->_list_map.at(this->_current_map)->_list_objects.push_back(objAdd);
								break;
							}
							}
						}
						this->_list_map.at(this->_current_map)->_list_objects.erase(
							this->_list_map.at(this->_current_map)->_list_objects.begin() + j);
						if (j-- <= i)
							i--;
					}
				}
			}

			// kiểm tra va chạm với bomber man: bomber man sẽ chết
			CBox tileBox = this->_list_map.at(this->_current_map)->_list_objects.at(i)->getBounding();
			float normalX = 0.0f, normalY = 0.0f, collisonTime = -1.0f, xOffset = 0.0f, yOffset = 0.0f;

			DIRECTION dir = _collision->isCollision(characterBox, tileBox, collisonTime, xOffset, yOffset);
			if (dir != DIRECTION::NONE){
				this->bomberDied();
			}
			this->_list_map.at(this->_current_map)->_list_objects.at(i)->update(deltaTime);
			break;
		}
		case ID_GIFTBOX_COIN:
		{
			// kiểm tra va chạm với bomber man: bomber sẽ nhận được  tiền
			CBox tileBox = this->_list_map.at(this->_current_map)->_list_objects.at(i)->getBounding();
			float normalX = 0.0f, normalY = 0.0f, collisonTime = -1.0f, xOffset = 0.0f, yOffset = 0.0f;

			DIRECTION dir = _collision->isCollision(characterBox, tileBox, collisonTime, xOffset, yOffset);
			if (dir != DIRECTION::NONE){
				this->_b_gold++;
				// xóa giftbox này
				this->_list_map.at(this->_current_map)->_list_objects.erase(
					this->_list_map.at(this->_current_map)->_list_objects.begin() + i--);
				SoundManager::GetInstance()->getSoundWithID(ID_SOUND_PICK_ITEM)->Play();
				break;
			}
			else
				this->_list_map.at(this->_current_map)->_list_objects.at(i)->update(deltaTime);
			break;
		}
		case ID_GIFTBOX_HEART:
		{
			// kiểm tra va chạm với bomber man: bomber sẽ nhận được 1 mạng chơi
			CBox tileBox = this->_list_map.at(this->_current_map)->_list_objects.at(i)->getBounding();
			float normalX = 0.0f, normalY = 0.0f, collisonTime = -1.0f, xOffset = 0.0f, yOffset = 0.0f;

			DIRECTION dir = _collision->isCollision(characterBox, tileBox, collisonTime, xOffset, yOffset);
			if (dir != DIRECTION::NONE){
				this->_b_live++;
				// xóa giftbox này
				this->_list_map.at(this->_current_map)->_list_objects.erase(
					this->_list_map.at(this->_current_map)->_list_objects.begin() + i--);
				SoundManager::GetInstance()->getSoundWithID(ID_SOUND_PICK_ITEM)->Play();
				break;
			}
			else
				this->_list_map.at(this->_current_map)->_list_objects.at(i)->update(deltaTime);
			break;
		}
		case ID_GIFTBOX_TIME:
		{
			// kiểm tra va chạm với bomber man: bomber sẽ nhận được thêm 5s
			CBox tileBox = this->_list_map.at(this->_current_map)->_list_objects.at(i)->getBounding();
			float normalX = 0.0f, normalY = 0.0f, collisonTime = -1.0f, xOffset = 0.0f, yOffset = 0.0f;

			DIRECTION dir = _collision->isCollision(characterBox, tileBox, collisonTime, xOffset, yOffset);
			if (dir != DIRECTION::NONE){
				this->_b_map_times += 30000;
				// xóa giftbox này
				this->_list_map.at(this->_current_map)->_list_objects.erase(
					this->_list_map.at(this->_current_map)->_list_objects.begin() + i--);
				SoundManager::GetInstance()->getSoundWithID(ID_SOUND_PICK_ITEM)->Play();
				break;
			}
			else
				this->_list_map.at(this->_current_map)->_list_objects.at(i)->update(deltaTime);
			break;
		}
		case ID_GIFTBOX_VELOCITY:
		{
			// kiểm tra va chạm với bomber man: bomber sẽ nhận được tăng tốc độ
			CBox tileBox = this->_list_map.at(this->_current_map)->_list_objects.at(i)->getBounding();
			float normalX = 0.0f, normalY = 0.0f, collisonTime = -1.0f, xOffset = 0.0f, yOffset = 0.0f;

			DIRECTION dir = _collision->isCollision(characterBox, tileBox, collisonTime, xOffset, yOffset);
			if (dir != DIRECTION::NONE){
				this->_b_bomber_man->BootVelocity();
				// xóa giftbox này
				this->_list_map.at(this->_current_map)->_list_objects.erase(
					this->_list_map.at(this->_current_map)->_list_objects.begin() + i--);
				SoundManager::GetInstance()->getSoundWithID(ID_SOUND_PICK_ITEM)->Play();
				break;
			}
			else
				this->_list_map.at(this->_current_map)->_list_objects.at(i)->update(deltaTime);
			break;
		}
		case ID_GIFTBOX_KEY:
		{
			// kiểm tra va chạm với bomber man: bomber sẽ nhận được 1 chìa khóa
			CBox tileBox = this->_list_map.at(this->_current_map)->_list_objects.at(i)->getBounding();
			float normalX = 0.0f, normalY = 0.0f, collisonTime = -1.0f, xOffset = 0.0f, yOffset = 0.0f;

			DIRECTION dir = _collision->isCollision(characterBox, tileBox, collisonTime, xOffset, yOffset);
			if (dir != DIRECTION::NONE){
				this->_b_keys++;
				this->_b_gold += 50;
				// xóa giftbox này
				this->_list_map.at(this->_current_map)->_list_objects.erase(
					this->_list_map.at(this->_current_map)->_list_objects.begin() + i--);
				SoundManager::GetInstance()->getSoundWithID(ID_SOUND_PICK_ITEM)->Play();
				break;
			}
			else
				this->_list_map.at(this->_current_map)->_list_objects.at(i)->update(deltaTime);
			break;
		}
		case ID_GIFTBOX_SUPERBOMB:
		{
			// kiểm tra va chạm với bomber man: bomber sẽ nhận được super bom
			CBox tileBox = this->_list_map.at(this->_current_map)->_list_objects.at(i)->getBounding();
			float normalX = 0.0f, normalY = 0.0f, collisonTime = -1.0f, xOffset = 0.0f, yOffset = 0.0f;

			DIRECTION dir = _collision->isCollision(characterBox, tileBox, collisonTime, xOffset, yOffset);
			if (dir != DIRECTION::NONE){
				this->_super_bomb_count += 5;
				// xóa giftbox này
				this->_list_map.at(this->_current_map)->_list_objects.erase(
					this->_list_map.at(this->_current_map)->_list_objects.begin() + i--);
				SoundManager::GetInstance()->getSoundWithID(ID_SOUND_PICK_ITEM)->Play();
				break;
			}
			else
				this->_list_map.at(this->_current_map)->_list_objects.at(i)->update(deltaTime);
			break;
		}
		case ID_DOOR:
		{
			if (this->_b_keys >= this->_list_map.at(this->_current_map)->getNeedKeys()){
				((DoorObject*)this->_list_map.at(this->_current_map)->_list_objects.at(i))->openDoor();
			}
			// kiểm tra va chạm với bomber man: qua màn
			CBox tileBox = this->_list_map.at(this->_current_map)->_list_objects.at(i)->getBounding();
			float normalX = 0.0f, normalY = 0.0f, collisonTime = -1.0f, xOffset = 0.0f, yOffset = 0.0f;

			DIRECTION dir = _collision->isCollision(characterBox, tileBox, collisonTime, xOffset, yOffset);
			if (dir != DIRECTION::NONE){
				if (((DoorObject*)this->_list_map.at(this->_current_map)->_list_objects.at(i))->isOpen()){
					SoundManager::GetInstance()->getSoundWithID(ID_SOUND_WINNER)->Play();
					Sleep(1000);
					this->nextMap();
				}
				else
				{
					switch (dir)
					{
					case DIRECTION::LEFT:
						this->_b_bomber_man->setPosition(tileBox.x - this->_b_bomber_man->getWidth() - 2,
							this->_b_bomber_man->getPosition().y);
						this->_b_bomber_man->setVelocity(0, 0);
						break;
					case DIRECTION::RIGHT:
						this->_b_bomber_man->setPosition(tileBox.w + tileBox.x + 2,
							this->_b_bomber_man->getPosition().y);
						this->_b_bomber_man->setVelocity(0, 0);
						break;
					case DIRECTION::TOP:
						this->_b_bomber_man->setPosition(this->_b_bomber_man->getPosition().x,
							tileBox.y + this->_b_bomber_man->getHeight() + 2);
						this->_b_bomber_man->setVelocity(0, 0);
						break;
					case DIRECTION::BOTTOM:
						this->_b_bomber_man->setPosition(this->_b_bomber_man->getPosition().x, tileBox.y - tileBox.h - 2);
						this->_b_bomber_man->setVelocity(0, 0);
						break;
					default:
						break;
					}
				}
				break;
			}
			else
				this->_list_map.at(this->_current_map)->_list_objects.at(i)->update(deltaTime);
			break;
		}
		case ID_GHOST:
		{
			// kiểm tra va chạm với bomber man: bomber chết
			CBox tileBox = this->_list_map.at(this->_current_map)->_list_objects.at(i)->getBounding();
			float normalX = 0.0f, normalY = 0.0f, collisonTime = -1.0f, xOffset = 0.0f, yOffset = 0.0f;

			DIRECTION dir = _collision->isCollision(characterBox, tileBox, collisonTime, xOffset, yOffset);
			if (dir != DIRECTION::NONE){
				//

				//this->_super_boom = true;
				// xóa giftbox này
				//this->_list_map.at(this->_current_map)->_list_objects.erase(
				//	this->_list_map.at(this->_current_map)->_list_objects.begin() + i--);
				break;
			}
			else
				this->_list_map.at(this->_current_map)->_list_objects.at(i)->update(deltaTime);
			break;
		}

		default:
		{
			CBox tileBox = this->_list_map.at(this->_current_map)->_list_objects.at(i)->getBounding();
			float normalX = 0.0f, normalY = 0.0f, collisonTime = -1.0f, xOffset = 0.0f, yOffset = 0.0f;
			DIRECTION dir = _collision->isCollision(characterBox, tileBox, collisonTime, xOffset, yOffset);

			switch (dir)
			{
			case DIRECTION::LEFT:
				this->_b_bomber_man->setPosition(tileBox.x - this->_b_bomber_man->getWidth() - 2,
					this->_b_bomber_man->getPosition().y);
				this->_b_bomber_man->setVelocity(0, 0);
				break;
			case DIRECTION::RIGHT:
				this->_b_bomber_man->setPosition(tileBox.w + tileBox.x + 2,
					this->_b_bomber_man->getPosition().y);
				this->_b_bomber_man->setVelocity(0, 0);
				break;
			case DIRECTION::TOP:
				this->_b_bomber_man->setPosition(this->_b_bomber_man->getPosition().x,
					tileBox.y + this->_b_bomber_man->getHeight() + 2);
				this->_b_bomber_man->setVelocity(0, 0);
				break;
			case DIRECTION::BOTTOM:
				this->_b_bomber_man->setPosition(this->_b_bomber_man->getPosition().x, tileBox.y - tileBox.h - 2);
				this->_b_bomber_man->setVelocity(0, 0);
				break;
			default:
				break;
			}
			break;
		}
		}
	}
	// cập nhật camera
	RECT from = _b_camera->GetViewport();
	int x = this->_b_bomber_man->getPosition().x - (this->_screen_width / 2);
	int y = this->_b_bomber_man->getPosition().y + (this->_screen_height / 2);
	if (x < 0)
		x = 0;
	if (x>(this->_list_map.at(this->_current_map)->getMapWidth() - this->_screen_width))
		x = (this->_list_map.at(this->_current_map)->getMapWidth() - this->_screen_width);
	if (y < this->_screen_height)
		y = this->_screen_height;
	if (y > this->_list_map.at(this->_current_map)->getMapHeight())
		y = this->_list_map.at(this->_current_map)->getMapHeight();
	this->_b_camera->SetPositionCamera(D3DXVECTOR2(x, y));

	// cập nhật thông số game
	this->_b_map_times -= deltaTime;

	if (deltaTime > 1000)
	{
		this->_b_map_times = 0;
	}
	// cập nhật game bar
	for (int i = 0; i < this->_list_gamebar.size(); i++){
		if (this->_list_gamebar.at(i)->getId() == GAMEBAR_HEART_BAR_ID)
			this->_list_gamebar.at(i)->updateValue(this->_b_live);
		else if (this->_list_gamebar.at(i)->getId() == GAMEBAR_KEY_BAR_ID)
			this->_list_gamebar.at(i)->updateValue(this->_b_keys);
		else if (this->_list_gamebar.at(i)->getId() == GAMEBAR_GOLD_BAR_ID)
			this->_list_gamebar.at(i)->updateValue(this->_b_gold);
		else if (this->_list_gamebar.at(i)->getId() == GAMEBAR_TIME_BAR_ID)
			this->_list_gamebar.at(i)->updateValue(this->_b_map_times);
		else if (this->_list_gamebar.at(i)->getId() == GAMEBAR_SUPERBOMB_BAR_ID)
			this->_list_gamebar.at(i)->updateValue(this->_super_bomb_count);
	}
}

void PlayMapMgt::draw(CDirectX * directX){

	if (this->_is_game_starting){
		this->_gb_text_mgt->Initialize(directX->getDevice(), TEXT("Times New Roman"), 30, 1);
		directX->getDevice()->StretchRect(this->_start_map_background, NULL, directX->getBackBuffer(), NULL, D3DTEXF_NONE);
		std::string mapStr = std::to_string(this->_current_map + 1) + "";
		char *cstr = new char[mapStr.length() + 1];
		strcpy(cstr, mapStr.c_str());
		this->_gb_text_mgt->Print(cstr, 288, 223, D3DCOLOR_XRGB(255, 0, 0), directX->getSpriteHandler(), 0, 0, FA_LEFT);
		delete[] cstr;
		return;
	}
	if (this->_is_game_over){
		this->_gb_text_mgt->Initialize(directX->getDevice(), TEXT("Times New Roman"), 18, 1);
		directX->getDevice()->StretchRect(this->_game_over_background, NULL, directX->getBackBuffer(), NULL, D3DTEXF_NONE);
		std::string mapStr = std::to_string(this->_b_gold);
		char *cstr = new char[mapStr.length() + 1];
		strcpy(cstr, mapStr.c_str());
		this->_gb_text_mgt->Print(cstr, 288, 335, D3DCOLOR_XRGB(206, 230, 5), directX->getSpriteHandler(), 0, 0, FA_LEFT);
		delete[] cstr;
		return;
	}

	if (this->_list_map.size() <= this->_current_map){
		return;
	}
	// vẽ map 
	this->_list_map.at(this->_current_map)->draw(directX, this->_b_camera->GetPositionCamera(),
		this->_screen_width, this->_screen_height);

	// vẽ nhân vật - bomber
	this->_b_bomber_man->draw(this->_b_camera->GetPositionCamera());
	// vẽ game bar
	for (int i = 0; i < this->_list_gamebar.size(); i++){
		this->_list_gamebar.at(i)->draw(directX->getSpriteHandler());
	}
}

void PlayMapMgt::addBomb(LPD3DXSPRITE spriteHandler){
	if (this->_list_map.size() <= this->_current_map){
		return;
	}

	if (!this->_b_bomber_man->isAllowAddBomb())
		return;

	float x = (int)((this->_b_bomber_man->getPosition().x + WIDTH_OBJECT / 2) / WIDTH_OBJECT)*(float)WIDTH_OBJECT;
	float y = (int)((this->_b_bomber_man->getPosition().y + HEIGHT_OBJECT) / HEIGHT_OBJECT)*(float)HEIGHT_OBJECT;
	if (this->_super_boom){
		Bomb *newBomb = new Bomb(ID_BOMB_SUPER, x, y, WIDTH_OBJECT, HEIGHT_OBJECT,
			this->_resourceMgt->getSpriteWithID(ID_BOMB_SUPER), SUPER_BOMB_EXIST_TIME);
		newBomb->inital(NULL);
		this->_list_map.at(this->_current_map)->_list_objects.push_back(newBomb);
		this->_super_bomb_count -= 1;
	}
	else{
		Bomb *newBomb = new Bomb(ID_BOMB_NORMAL, x, y, WIDTH_OBJECT, HEIGHT_OBJECT,
			this->_resourceMgt->getSpriteWithID(ID_BOMB_NORMAL), NORMAL_BOMB_EXIST_TIME);
		newBomb->inital(NULL);
		this->_list_map.at(this->_current_map)->_list_objects.push_back(newBomb);
	}
	SoundManager::GetInstance()->getSoundWithID(ID_SOUND_ADD_BOMB)->Play();
	this->_b_bomber_man->AddBomb();
}

void PlayMapMgt::bomberRunRight(){
	this->_b_bomber_man->WalkingRight();
}
void PlayMapMgt::bomberRunLeft(){
	this->_b_bomber_man->WalkingLeft();
}
void PlayMapMgt::bomberRunFront(){
	this->_b_bomber_man->WalkingFront();
}
void PlayMapMgt::bomberRunBehind(){
	this->_b_bomber_man->WalkingBehind();
}
void PlayMapMgt::bomberMoveNone(){
	this->_b_bomber_man->MoveNone();
}