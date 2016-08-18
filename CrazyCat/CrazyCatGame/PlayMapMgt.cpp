#include "PlayMapMgt.h"


PlayMapMgt::PlayMapMgt()
{
	this->_list_map.clear();
	this->_list_gamebar.clear();
	this->_b_live = 0;
	this->_b_gold = 5000;
	this->_b_keys = 0;
	this->_b_bomber_man = NULL;
	this->_collision = NULL;
	this->_current_map = -1;
	this->_b_map_times = 0;
	this->_b_camera = NULL;
	this->_screen_width = 0;
	this->_screen_height = 0;
}


PlayMapMgt::~PlayMapMgt()
{
	SAFE_DELETE(this->_b_bomber_man);
	SAFE_DELETE(this->_collision);
	SAFE_DELETE(this->_b_camera);
}
void PlayMapMgt::inital(CDirectX * directX, int screenWidth, int screenHeight){
	// tạo ra các map và add vào danh sách tuy nhiên chưa khởi động cũng như chưa load map
	this->_list_map.clear();
	Map *map1 = new Map("White Farm", MAP_01_IMG_FILE, MAP_01_TEXT_FILE, MAP_01_INFO_FILE, MAP_01_TIME_MAP);
	map1->inital(directX->getDevice());
	this->_list_map.push_back(map1);
	

	// tạo ra các thanh gamebar và add vào list
	this->_list_gamebar.clear();
	GameBar *heartBar = new GameBar();
	heartBar->inital(HEART_BAR_ID, directX->getDevice(), directX->getSpriteHandler(), HEART_BAR_IMG_FILE, BAR_WIDTH, BAR_HEIGHT,
		D3DXVECTOR2(HEART_BAR_X, HEART_BAR_Y), CBox(BAR_TEXT_X, BAR_TEXT_Y, BAR_TEXT_WIDTH, BAR_TEXT_HEIGHT), DEFAULT_LIVE);
	this->_list_gamebar.push_back(heartBar);

	GameBar *keyBar = new GameBar();
	keyBar->inital(KEY_BAR_ID, directX->getDevice(), directX->getSpriteHandler(), KEY_BAR_IMG_FILE, BAR_WIDTH, BAR_HEIGHT,
		D3DXVECTOR2(KEY_BAR_X, KEY_BAR_Y), CBox(BAR_TEXT_X, BAR_TEXT_Y, BAR_TEXT_WIDTH, BAR_TEXT_HEIGHT), 0);
	this->_list_gamebar.push_back(keyBar);

	GameBar *goldBar = new GameBar();
	goldBar->inital(GOLD_BAR_ID, directX->getDevice(), directX->getSpriteHandler(), GOLD_BAR_IMG_FILE, BAR_WIDTH, BAR_HEIGHT,
		D3DXVECTOR2(GOLD_BAR_X, GOLD_BAR_Y), CBox(BAR_TEXT_X, BAR_TEXT_Y, BAR_TEXT_WIDTH, BAR_TEXT_HEIGHT), 0);
	this->_list_gamebar.push_back(goldBar);

	// khởi tạo nhân vật
	this->_b_bomber_man = new CCharacter(BOMBER_START_X, BOMBER_START_Y);
	this->_b_bomber_man->inital(directX->getSpriteHandler());

	// khởi tạo biến xét va chạm
	_collision = new CCollision();

	// khởi tạo camera
	this->_screen_width = screenWidth;
	this->_screen_height = screenHeight;
	this->_b_camera = new CCamera(screenWidth, screenHeight);

	this->nextMap();
}

void PlayMapMgt::resetCurrentMap(){
	this->_b_live = DEFAULT_LIVE;
	this->_b_gold = 5000;
	this->_b_keys = 0;
	if (this->_list_map.size() > this->_current_map && this->_current_map >= 0)
		this->_b_map_times = this->_list_map.at(this->_current_map)->getMaximumTimes();
	else
		this->_b_map_times = 0;
	if (this->_b_bomber_man != NULL){
		this->_b_bomber_man->setPosition(BOMBER_START_X, BOMBER_START_Y);
		this->_b_bomber_man->setVelocity(0.0f, 0.0f);
	}
}

void PlayMapMgt::nextMap(){
	if (this->_list_map.size() > 0)
	{
		this->_current_map = (this->_current_map + 1) % (this->_list_map.size());
	}
	else
		this->_current_map = -1;
	this->resetCurrentMap();
}

void PlayMapMgt::update(int deltaTime, CDirectX * directX){

	if (this->_list_map.size() <= this->_current_map){
		return;
	}

	// cập nhật bomber man
	this->_b_bomber_man->update(deltaTime);

	// lấy khung của bomber man
	CBox characterBox = this->_b_bomber_man->getBounding();

	// cập nhật các đối tượng trong map
	// xóa các đối tượng: bom đã nổ, đường nổ đã kết thúc, đường nổ va chạm với tường
	for (int i = 0; i < this->_list_map.at(this->_current_map)->_list_objects.size(); i++){
		// kiểm tra bom đã nổ: xóa bom và sinh ra 4 đường đạn tương ứng
		if (this->_list_map.at(this->_current_map)->_list_objects.at(i)->getId() == BOMB_ID){
			if (((Bomb*)(this->_list_map.at(this->_current_map)->_list_objects.at(i)))->IsFired())
			{
				FireBang* centerFirebang = new FireBang(FIREBANG_ID,
					this->_list_map.at(this->_current_map)->_list_objects.at(i)->getPosition().x,
					this->_list_map.at(this->_current_map)->_list_objects.at(i)->getPosition().y,
					this->_list_map.at(this->_current_map)->_list_objects.at(i)->getWidth(),
					this->_list_map.at(this->_current_map)->_list_objects.at(i)->getHeight(),
					directX->getSpriteHandler(), FIRE_BANG_CENTER, 3, 3);
				centerFirebang->inital(directX->getSpriteHandler());
				this->_list_map.at(this->_current_map)->_list_objects.push_back(centerFirebang);

				FireBang* leftFirebang = new FireBang(FIREBANG_ID,
					this->_list_map.at(this->_current_map)->_list_objects.at(i)->getPosition().x - BOMB_WIDTH + 2,
					this->_list_map.at(this->_current_map)->_list_objects.at(i)->getPosition().y,
					this->_list_map.at(this->_current_map)->_list_objects.at(i)->getWidth(),
					this->_list_map.at(this->_current_map)->_list_objects.at(i)->getHeight(),
					directX->getSpriteHandler(), FIRE_BANG_LEFT, 3, 3);
				leftFirebang->inital(directX->getSpriteHandler());
				this->_list_map.at(this->_current_map)->_list_objects.push_back(leftFirebang);

				FireBang* rightFirebang = new FireBang(FIREBANG_ID,
					this->_list_map.at(this->_current_map)->_list_objects.at(i)->getPosition().x + BOMB_WIDTH - 2,
					this->_list_map.at(this->_current_map)->_list_objects.at(i)->getPosition().y,
					this->_list_map.at(this->_current_map)->_list_objects.at(i)->getWidth(),
					this->_list_map.at(this->_current_map)->_list_objects.at(i)->getHeight(),
					directX->getSpriteHandler(), FIRE_BANG_RIGHT, 3, 3);
				rightFirebang->inital(directX->getSpriteHandler());
				this->_list_map.at(this->_current_map)->_list_objects.push_back(rightFirebang);

				FireBang* topFirebang = new FireBang(FIREBANG_ID,
					this->_list_map.at(this->_current_map)->_list_objects.at(i)->getPosition().x,
					this->_list_map.at(this->_current_map)->_list_objects.at(i)->getPosition().y + BOMB_HEIGHT - 2,
					this->_list_map.at(this->_current_map)->_list_objects.at(i)->getWidth(),
					this->_list_map.at(this->_current_map)->_list_objects.at(i)->getHeight(),
					directX->getSpriteHandler(), FIRE_BANG_TOP, 3, 3);
				topFirebang->inital(directX->getSpriteHandler());
				this->_list_map.at(this->_current_map)->_list_objects.push_back(topFirebang);

				FireBang* bottomFirebang = new FireBang(FIREBANG_ID,
					this->_list_map.at(this->_current_map)->_list_objects.at(i)->getPosition().x,
					this->_list_map.at(this->_current_map)->_list_objects.at(i)->getPosition().y - BOMB_HEIGHT + 2,
					this->_list_map.at(this->_current_map)->_list_objects.at(i)->getWidth(),
					this->_list_map.at(this->_current_map)->_list_objects.at(i)->getHeight(),
					directX->getSpriteHandler(), FIRE_BANG_BOTTOM, 3, 3);
				bottomFirebang->inital(directX->getSpriteHandler());
				this->_list_map.at(this->_current_map)->_list_objects.push_back(bottomFirebang);

				this->_list_map.at(this->_current_map)->_list_objects.erase(
					this->_list_map.at(this->_current_map)->_list_objects.begin() + i--);
				continue;
			}
			this->_list_map.at(this->_current_map)->_list_objects.at(i)->update(deltaTime);
		}
		// kiểm tra các đường nổ: sẽ bị xóa nếu đã nổ xong hoặc va chạm với tường
		else if (this->_list_map.at(this->_current_map)->_list_objects.at(i)->getId() == FIREBANG_ID){
			// kiểm tra xem đã nổ xong chưa?
			if (((FireBang*)(this->_list_map.at(this->_current_map)->_list_objects.at(i)))->isFiredBang())
			{
				this->_list_map.at(this->_current_map)->_list_objects.erase(
					this->_list_map.at(this->_current_map)->_list_objects.begin() + i--);
				continue;
			}
			// kiểm tra xem có xảy ra va chạm với tường hay ko?
			bool flag = false;
			for (int j = 0; j < this->_list_map.at(this->_current_map)->_list_objects.size(); j++){
				if (this->_list_map.at(this->_current_map)->_list_objects.at(j)->getId() == BRICK_ID){
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
			if (!flag)
				this->_list_map.at(this->_current_map)->_list_objects.at(i)->update(deltaTime);
			else
				continue;

			// kiểm tra va chạm với bomber man: bomber man sẽ chết
			CBox tileBox = this->_list_map.at(this->_current_map)->_list_objects.at(i)->getBounding();
			float normalX = 0.0f, normalY = 0.0f, collisonTime = -1.0f, xOffset = 0.0f, yOffset = 0.0f;
			if (this->_b_live < 1){
				this->_b_bomber_man->Dead();
			}
			DIRECTION dir = _collision->isCollision(characterBox, tileBox, collisonTime, xOffset, yOffset);
			if (dir != DIRECTION::NONE && !this->_b_bomber_man->_is_dead){
				this->_b_bomber_man->setPosition(BOMBER_START_X, BOMBER_START_Y);
				this->_b_bomber_man->setVelocity(0, 0);
				this->_b_live -= 1;
			}

		}
		else{	// gach
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

	// cập nhật game bar
	for (int i = 0; i < this->_list_gamebar.size(); i++){
		if (this->_list_gamebar.at(i)->getId() == HEART_BAR_ID)
			this->_list_gamebar.at(i)->updateValue(this->_b_live);
		else if (this->_list_gamebar.at(i)->getId() == KEY_BAR_ID)
			this->_list_gamebar.at(i)->updateValue(this->_b_keys);
		else if (this->_list_gamebar.at(i)->getId() == GOLD_BAR_ID)
			this->_list_gamebar.at(i)->updateValue(this->_b_gold);
	}
}

void PlayMapMgt::draw(CDirectX * directX){
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
	float x = (int)((this->_b_bomber_man->getPosition().x + BOMB_WIDTH / 2) / BOMB_WIDTH)*(float)BOMB_WIDTH;
	float y = (int)((this->_b_bomber_man->getPosition().y + BOMB_WIDTH) / BOMB_WIDTH)*(float)BOMB_HEIGHT;
	Bomb *newBomb = new Bomb(BOMB_ID, x, y, BOMB_WIDTH, BOMB_HEIGHT, spriteHandler, BOMB_IMG, 3, 3, true, true, true, true);
	this->_list_map.at(this->_current_map)->_list_objects.push_back(newBomb);
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