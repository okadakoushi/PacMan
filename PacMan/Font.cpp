#include "stdafx.h"
#include "Font.h"

void Font::Init(const char* dispStr, int size, int thickness)
{
	m_dispChar = dispStr;
	m_size = size;
	m_thickness = thickness;
	//ハンドル作成。
	m_fontHandle = CreateFontToHandle(m_fontType, size, thickness);
}

void Font::Draw(const Vector2& pos)
{
	DrawStringToHandle(pos.x, pos.y, m_dispChar, GetColor(255, 255, 255), m_fontHandle);
}
