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

void Font::Draw(unsigned int color)
{
	Vector2_Int DrawPos;
	
	if (m_parent != nullptr)
	{
		//parent�̈ʒu+�����̈ʒu�B
		DrawPos = m_parent->GetPosition() + m_position;
	}
	else
	{
		DrawPos = m_position;
	}

	DrawStringToHandle((int)DrawPos.x, (int)DrawPos.y, m_dispChar, color, m_fontHandle);
}
