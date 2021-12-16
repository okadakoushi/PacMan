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
	//�p�X�������B
	m_fontType = FONT_DATA_PATH;
	
	//�p�����[�^�[�������B
	m_dispChar = dispStr;
	m_size = size;
	m_thickness = thickness;
	
	//�n���h���쐬�B
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
