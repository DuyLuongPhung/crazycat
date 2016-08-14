#ifndef Box_H
#define Box_H

#include <d3d9.h>

class CBox
{
public:
	// Tọa độ của góc trái trên, top-left
	float x, y;

	// Kích thước khung: chiều rộng, chiều dài
	float w, h;

	// Tốc độ di chuyển của đối tượng theo 2 chiều Ox, Oy
	// Tốc độ ở đây là độ dài nó sẽ di chuyển được
	float vx, vy;

public:
	CBox();
	CBox(float x, float y, float w, float h, float vx, float vy);
	CBox(float x, float y, float w, float h);
	~CBox();

	// kiểm tra 2 box giao nhau
	bool IsIntersectedWith(CBox box);

	// lấy ra kiểu RECT- rectangle
	RECT ToRect();
};

#endif
