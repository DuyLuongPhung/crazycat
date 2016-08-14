#include "Text.h"


CText::CText()
{
	m_pFont = NULL;
}



BOOL CText::Initialize(LPDIRECT3DDEVICE9 d3ddev, LPWSTR fontName, int size, BOOL bold, BOOL italic)
{
	SAFE_RELEASE(m_pFont);
	HRESULT hr = 0;
	hr = D3DXCreateFont(d3ddev, -size, 0, bold ? 800 : 0, 1, italic, DEFAULT_CHARSET,
		OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, fontName, &m_pFont);
	if (FAILED(hr))
	{
		return FALSE;
	}
	return TRUE;
}

void CText::Print(LPSTR text, int xPosition, int yPosition, DWORD color, LPD3DXSPRITE sprite,
	int textBoxWidth, int textBoxHeight, FONTALIGNMENT alignment)
{
	if (!m_pFont)
	{
		return;
	}
	DWORD format = DT_EXPANDTABS;
	if (textBoxWidth == 0)
	{
		format |= DT_NOCLIP;
	}
	else
	{
		format |= DT_WORDBREAK;
		switch (alignment)
		{
		case FA_LEFT:
			format |= DT_LEFT;
			break;
		case FA_CENTER:
			format |= DT_CENTER;
			break;
		case FA_RIGHT:
			format |= DT_RIGHT;
			break;
		case FA_TOPRIGHT:
			format |= DT_RIGHT | DT_TOP;
			break;
		case FA_BOTTOMRIGHT:
			format |= DT_RIGHT | DT_BOTTOM;
			break;
		case FA_TOPLEFT:
			format |= DT_LEFT | DT_TOP;
			break;
		case FA_BOTTOMLEFT:
			format |= DT_LEFT | DT_BOTTOM;
			break;
		}
		if (textBoxHeight == 0)
		{
			// A width is specified, but not a height.
			// Make it seem like height is infinite
			textBoxHeight = 2000;
		}
	}
	RECT rect = { xPosition, yPosition, xPosition + textBoxWidth, yPosition + textBoxHeight };
	m_pFont->DrawTextA(sprite, text, -1, &rect, format, color);
}


void CText::OnLostDevice()
{
	if (m_pFont)
	{
		m_pFont->OnLostDevice();
	}
}


void CText::OnResetDevice()
{
	if (m_pFont)
	{
		m_pFont->OnResetDevice();
	}
}


void CText::Release()
{
	SAFE_RELEASE(m_pFont);
}