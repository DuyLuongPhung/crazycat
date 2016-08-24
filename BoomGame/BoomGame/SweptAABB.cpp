#include "SweptAABB.h"


//---------------------------------------------
//lay vi tri o frame tiep theo cua box
//---------------------------------------------
CBox getSweptBroadphaseBox(CBox box)
{
	CBox broadphasebox;

	broadphasebox.x = box.vx > 0 ? box.x : box.x + box.vx;
	broadphasebox.y = box.vy > 0 ? box.y + box.vy : box.y;
	broadphasebox.w = box.vx > 0 ? box.vx + box.w : box.w - box.vx;
	broadphasebox.h = box.vy > 0 ? box.vy + box.h : box.h - box.vy;
	broadphasebox.vx = 0;
	broadphasebox.vy = 0;

	return broadphasebox;
}

//----------------------------------------------------------
// returns true if the boxes are colliding (velocities are not used)
// dung trong truong hop xet va cham voi camera
//----------------------------------------------------------
bool AABBCheck(CBox box1, CBox box2)
{
	return !(box1.x + box1.w <= box2.x || box1.x >= box2.x + box2.w || box1.y - box1.h >= box2.y || box1.y <= box2.y - box2.h);
}

//--------------------------------------------------------------------------
//kiem tra va tranh va cham
//tra ve true neu va cham
//movex va movey la khoang cach ma b1 phai di chuyen de tranh va cham
//--------------------------------------------------------------------------
bool AABB(CBox b1, CBox b2, float& moveX, float& moveY, float& offsetX, float& offsetY)
{
	moveX = moveY = 0.0f;

	float l = b2.x - (b1.x + b1.w);
	float r = (b2.x + b2.w) - b1.x;
	float t = b2.y - (b1.y - b1.h);
	float b = (b2.y - b2.h) - b1.y;

	// chưa xảy ra va chạm
	if (l > 0 || r < 0 || t < 0 || b > 0)
		return false;

	// tính dentry của x và y với mọi vx, vy
	moveX = abs(l) < r ? l : r;
	moveY = abs(b) < t ? b : t;
	//offset để dùng khi xử lý va chạm ở từng đối tượng
	offsetX = abs(moveX);
	offsetY = abs(moveY);
	// sử dụng biến move nào nhỏ hơn, biến còn lại cho bằng 0, 
	if (abs(moveY) <= abs(moveX))
		moveX = 0.0f;
	else
		moveY = 0.0f;
	return true;
}

//-------------------------------------------------------------
//tinh thoi gian va huong va cham
//tra ve (0, 1) neu va cham, tra ve 1 neu khong va cham
//normalx va normaly dung de xac dinh mat va cham
//--------------------------------------------------------------
float sweptAABB(CBox box1, CBox box2, float &normalx, float &normaly)
{
	//khoang cach vao mien dung do
	float xInvEntry, yInvEntry;

	//khoang cach thoat khoi mien dung do
	float xInvExit, yInvExit;

	// find the distance between the objects on the near and far sides for both x and y
	if (box1.vx > 0.0f)
	{
		xInvEntry = box2.x - (box1.x + box1.w);
		xInvExit = (box2.x + box2.w) - box1.x;
	}
	else
	{
		xInvEntry = (box2.x + box2.w) - box1.x;
		xInvExit = box2.x - (box1.x + box1.w);
	}

	if (box1.vy > 0.0f)
	{
		yInvEntry = (box2.y - box2.h) - box1.y;
		yInvExit = box2.y - (box1.y - box1.h);
	}
	else
	{
		yInvEntry = box2.y - (box1.y - box1.h);
		yInvExit = (box2.y - box2.h) - box1.y;
	}

	//thoi gian vao mien va cham
	float xEntry, yEntry;

	//thoi gian ra khoi mien va cham
	float xExit, yExit;

	//neu van toc la 0 thi thoi gian va cham la vo cuc
	if (box1.vx == 0)
	{
		xEntry = -std::numeric_limits<float>::infinity();
		xExit = std::numeric_limits<float>::infinity();
	}
	else
	{
		//thoi gian = quang duong / van toc
		xEntry = xInvEntry / box1.vx;
		xExit = xInvExit / box1.vx;
	}

	//neu van toc la 0 thi thoi gian va cham la vo cuc
	if (box1.vy == 0)
	{
		yEntry = -std::numeric_limits<float>::infinity();
		yExit = std::numeric_limits<float>::infinity();
	}
	else
	{
		//thoi gian = quang duong / van toc
		yEntry = yInvEntry / box1.vy;
		yExit = yInvExit / box1.vy;
	}

	//tim thoi gian bat dau va cham la thoi gian lon nhat
	float entryTime = max(xEntry, yEntry);

	//thoi gian ket thuc va cham la thoi gian nho nhat
	float exitTime = min(xExit, yExit);

	//truong hop khong xay ra va cham
	/*if (entryTime > exitTime)*/
	if (entryTime > exitTime || xEntry < 0.0f && yEntry < 0.0f || xEntry > 1.0f || yEntry > 1.0f)
	{
		normalx = 0.0f;
		normaly = 0.0f;
		return 1.0f;
	}

	//truong hop xay ra va cham
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
	}
	return entryTime;
}