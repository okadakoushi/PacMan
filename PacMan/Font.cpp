#include "stdafx.h"
#include "Font.h"

Font::Font()
{
}

Font::~Font()
{
}

void Font::Init(const char* dispStr, int size, int thickness)
{
	m_dispChar = dispStr;
	m_size = size;
	m_thickness = thickness;
	//ƒnƒ“ƒhƒ‹ì¬B
	m_fontHandle = CreateFontToHandle(m_fontType, size, thickness);
}

void Font::Draw(const Vector2& pos, unsigned int color)
{
	DrawStringToHandle(pos.x, pos.y, m_dispChar, color, m_fontHandle);
}
