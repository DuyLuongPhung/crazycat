#include "Collision.h"


CCollision::CCollision()
{
}

/****************************************************************************************
* Kiểm tra xem 2 đối tượng có đang va chạm hay không?
* Không quan tâm đến vận tốc mà chỉ xét ở thời điểm hiện tại
***************************************************************************************/
bool Intersec(CBox box1, CBox box2)
{
	float l = box2.x - (box1.x + box1.w);
	float r = (box2.x + box2.w) - box1.x;
	float t = box2.y - (box1.y - box1.h);
	float b = (box2.y - box2.h) - box1.y;

	// chưa xảy ra va chạm
	if (l > 0 || r < 0 || t < 0 || b > 0)
		return false;

	return true;

}


/*****************************************************************************************
* Lấy khung chứa vùng di chuyển của vật trong frame này
* Tức là vùng mà vật đó sẽ di chuyển từ frame trước tới vị trí ở frame đang xét
* Vận tốc ở đây là khoảng cách đi được
*****************************************************************************************/
CBox GetSweptBroadPhaseBox(CBox box)
{
	CBox broadphasebox(0, 0, 0, 0);

	broadphasebox.x = (box.vx > 0) ? box.x : (box.x + box.vx);	// lấy giá trị x - min
	broadphasebox.y = (box.vy > 0) ? (box.y + box.vy) : box.y;	// lấy giá trị y - max
	broadphasebox.w = abs(box.vx) + box.w;						// lấy độ lớn vx + width
	broadphasebox.h = abs(box.vy) + box.h;						// lấy độ lớn vy + height

	return broadphasebox;
}

/****************************************************************************************
* Kiểm tra xem hiện tại 2 đối tượng có xảy ra va chạm hay không?
* Nếu 2 không va chạm, kiểm tra xem 2 đối tượng có khả năng xảy ra va chạm hay không
* Box1 - đối tượng di chuyển, Box2 - đối tượng đứng yên không có vận tốc
* Nếu đối tượng đứng yên - box2, nằm trong vùng di chuyển của đối tượng di chuyển - box1
* thì có khả năng xảy ra va chạm và ngược lại thì không có khả năng xảy ra va chạm
***************************************************************************************/
DIRECTION AABB(CBox box1, CBox box2){
	// kiểm tra xem hiện tại, 2 đối tượng này có va chạm hay không
	// TH đang va chạm
	if (Intersec(box1, box2)){
		box2.x += box2.w / 2;
		box2.y -= box2.h / 2;

		// xác định hướng va chạm
		// kết quả chỉ mang tính chất tương đối, ưu tiên theo trục Oy
		float percentX = ((box2.x - box1.x) / (box2.w / 2));
		float percentY = ((box2.y - box1.y) / (box2.h / 2));
		if (abs(percentY) >= abs(percentX)){	// theo Oy
			if (percentY > 0)
				return DIRECTION::BOTTOM;
			return DIRECTION::TOP;
		}
		else{	// theo Ox
			if (percentX > 0)
				return DIRECTION::LEFT;
			return DIRECTION::RIGHT;
		}
	}
	// TH ko va chạm
	else{
		// kiểm tra khả năng xảy ra va chạm
		// Tính khung của đối tượng ở frame này
		// Khả năng đối tượng sẽ di chuyển đến vị trí này
		box1.vx -= box2.vx;
		box1.vy -= box2.vy;
		box2.vx = box2.vy = 0.0f;
		CBox moveBox = GetSweptBroadPhaseBox(box1);
		// Nếu đối tượng đứng yên - box2, nằm trong vùng di chuyển của đối tượng di chuyển - box1 thì
		// có khả năng xảy ra va chạm và ngược lại thì không có khả năng xảy ra va chạm
		if (Intersec(moveBox, box2)){
			return DIRECTION::NONE_CAN;
		}
		return DIRECTION::NONE;
	}
}

/****************************************************************************************
* Tính thời điểm và hướng va chạm
* Box1 đại diện cho đối tượng di chuyển, Box2 đại diện cho đối tượng đứng yên
* Nếu xảy ra va chạm mốc thời gian sẽ nằm trong: (0.0 -> 1.0)
* Nếu không xảy ra va chạm mốc thời gian sẽ: -1.0
* Hướng va chạm: nếu ko có sẽ: 0.0
* Hướng va chạm nếu xảy ra: 1.0 ~ right, top, -1.0 ~ left, bottom xét theo box1
***************************************************************************************/
float SweptAABB(CBox b1, CBox b2, float& normalx, float& normaly)
{
	// Khoảng cách cần thiết để đi vào miền đụng độ
	float xInvEntry, yInvEntry;
	// Khoảng cách cần thiết để đi ra khỏi miền đụng độ
	float xInvExit, yInvExit;

	// Tính toán các khoảng cách
	if (b1.vx > 0.0f)
	{
		xInvEntry = b2.x - (b1.x + b1.w);
		xInvExit = (b2.x + b2.w) - b1.x;
	}
	else
	{
		xInvEntry = (b2.x + b2.w) - b1.x;
		xInvExit = b2.x - (b1.x + b1.w);
	}

	if (b1.vy > 0.0f)
	{
		yInvEntry = b2.y - (b1.y + b1.h);
		yInvExit = (b2.y + b2.h) - b1.y;
	}
	else
	{
		yInvEntry = (b2.y + b2.h) - b1.y;
		yInvExit = b2.y - (b1.y + b1.h);
	}

	// Thời gian đi vào miền va chạm
	float xEntry, yEntry;
	// Thời gian đi ra khỏi miền va chạm
	float xExit, yExit;

	if (b1.vx == 0.0f)
	{
		xEntry = -std::numeric_limits<float>::infinity();
		xExit = std::numeric_limits<float>::infinity();
	}
	else
	{
		xEntry = xInvEntry / b1.vx;
		xExit = xInvExit / b1.vx;
	}

	if (b1.vy == 0.0f)
	{
		yEntry = -std::numeric_limits<float>::infinity();
		yExit = std::numeric_limits<float>::infinity();
	}
	else
	{
		yEntry = yInvEntry / b1.vy;
		yExit = yInvExit / b1.vy;
	}

	// Tính thời gia va chạm
	// Khoảng thời gian tối đa để xảy ra va chạm theo 2 trục: Ox, Oy
	float entryTime = max(xEntry, yEntry);

	// Tính thời gian đi ra khỏi va chạm
	// Khoảng thời gian tối thiểu đi ra khỏi va chạm theo 2 trục: Ox, Oy
	float exitTime = min(xExit, yExit);

	// TH không xảy ra va chạm
	if (entryTime > exitTime || xEntry < 0.0f && yEntry < 0.0f || xEntry > 1.0f || yEntry > 1.0f)
	{
		normalx = 0.0f;
		normaly = 0.0f;
		return -1.0f;
	}
	// TH xảy ra va chạm
	else
	{
		if (xEntry > yEntry)
		{
			if (xInvEntry < 0.0f)
			{
				normalx = 1.0f;
				normaly = 0.0f;
			}
			else
			{
				normalx = -1.0f;
				normaly = 0.0f;
			}
		}
		else
		{
			if (yInvEntry < 0.0f)
			{
				normalx = 0.0f;
				normaly = 1.0f;
			}
			else
			{
				normalx = 0.0f;
				normaly = -1.0f;
			}
		}

		// Trả về thời điểm xảy ra va chạm
		return entryTime;
	}
}

/****************************************************************************************
* Xét va chạm cho 2 đối tượng trong không gian 2 chiều (OXY)
* Trường hợp tổng quát: 2 đối tượng bất kỳ được đại diện bởi 2 CBox
***************************************************************************************/
DIRECTION CCollision::isCollision(CBox box1, CBox box2, float &collisionTime)
{
	DIRECTION dir = AABB(box1, box2);

	// đang xảy ra va chạm hoặc không có khả năng va chạm
	if (dir != DIRECTION::NONE_CAN)
		return dir;
		
	// TH cả 2 đều không có vận tốc
	if (box1.vx == 0.0f && box1.vy == 0.0f && box2.vx == 0.0f && box2.vy == 0.0f)
		return DIRECTION::NONE;

	// TH có khả năng xảy ra va chạm
	// kiểm tra va chạm và thời điểm va chạm, hướng va chạm (nếu có)
	collisionTime = -1.0f;
	float normalX = 0.0f, normalY = 0.0f;
	CBox moveBox = box1;
	CBox staticBox = box2;
	moveBox.vx -= staticBox.vx;
	moveBox.vy -= staticBox.vy;
	staticBox.vx = staticBox.vy = 0.0f;
	collisionTime = SweptAABB(moveBox, staticBox, normalX, normalY);
	if (normalY == 1.0f)
		return DIRECTION::TOP;
	if (normalY == -1.0f)
		return DIRECTION::BOTTOM;
	if (normalX == 1.0f)
		return DIRECTION::RIGHT;
	if (normalX == -1.0f)
		return DIRECTION::LEFT;
	return DIRECTION::NONE;
}

CCollision::~CCollision()
{
}
