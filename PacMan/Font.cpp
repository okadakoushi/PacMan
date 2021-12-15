#include "stdafx.h"
#include "Font.h"

static const char FONT_DATA_PATH[32] = "Assets/Pacman.dft";


Font::Font()
{
}

Font::~Font()
{
}

void Font::Init(const char* dispStr, int size, int thickness)
{
	//パス初期化。
	m_fontType = FONT_DATA_PATH;
	
	//パラメーター初期化。
	m_dispChar = dispStr;
	m_size = size;
	m_thickness = thickness;
	
	//ハンドル作成。
	m_fontHandle = LoadFontDataToHandle(m_fontType);

	if (m_fontHandle == -1)
	{
		OutputDebugString("WARNING: Font / FontHandle is invalid.");
	}
}

void Font::Draw(const Vector2& pos, unsigned int color)
{
	DrawStringToHandle((int)pos.x, (int)pos.y, m_dispChar, color, m_fontHandle);
}
