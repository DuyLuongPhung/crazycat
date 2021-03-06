
#ifndef Sprite_H
#define Sprite_H

#include <d3d9.h>
#include <d3dx9.h>

class CSprite 
{
protected:
	LPDIRECT3DTEXTURE9 _Image;
	LPD3DXSPRITE _SpriteHandler;

	int _Index;								// Current sprite index
	int _Width;								// Sprite width
	int _Height;							// Sprite height
	int _Count;								// Number of sprites
	int _SpritePerRow;						// Number of sprites per row
public:
	CSprite();
	CSprite(LPD3DXSPRITE SpriteHandler, LPWSTR FilePath, int Width, int Height, int Count, int SpritePerRow);
	CSprite(LPD3DXSPRITE SpriteHandler, LPWSTR FilePath, int Width, int Height, int Count, int SpritePerRow, D3DCOLOR transparentColor);
	~CSprite();
	void Next();
	void Reset();
	void Index(int index);

	int getWidth();
	int getHeight();
	int getCountSprite(){ return this->_Count; }
	bool isHighestSprite(){ return (this->_Index >= this->_Count-1); }

	// Render current sprite at location (X,Y) at the target surface
	void Render(D3DXVECTOR2 viewPort, int X, int Y);
	void Render( int X, int Y);
};
#endif