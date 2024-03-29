#include "stdafx.h"
#include "Sprite.h"

Sprite::Sprite()
{
}

Sprite::~Sprite()
{
}

void Sprite::Init(const char* filePath)
{
	//scaleについては実装予定。
	m_drawHandle = LoadGraph(filePath);
}

void Sprite::Init(int drawHandle)
{
	m_drawHandle = drawHandle;
}

void Sprite::Draw(Vector2 pos, double scale, double Angle, int drawHandle)
{
	//描画。
	if (DrawRotaGraph(pos.x, pos.y, scale, Angle, drawHandle, true) == -1)
	{
		OutputDebugString("WARNING: Sprite / DrawHandle is invalid.\n");
	}
}

void Sprite::Draw(Vector2 pos, double scale, double Angle)
{
	Draw(pos, scale, Angle, m_drawHandle);
}

void Sprite::Draw(Vector2 pos, int drawHandle)
{
	//描画。
	if (DrawGraph(pos.x, pos.y, drawHandle, true) == -1)
	{
		OutputDebugString("WARNING: Sprite / DrawHandle is invalid.\n");
	}
}

void Sprite::Draw(Vector2 pos)
{
	Draw(pos, m_drawHandle);
}



void Sprite::Draw(float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4, int drawHandle)
{
	if (DrawModiGraph(x1, y1, x2, y2, x3, y3, x4, y4, drawHandle, true) == -1)
	{
		OutputDebugString("WARNING: Sprite / DrawHandle is invalid.\n");
	}
}

void Sprite::Draw(float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4)
{
	Draw(x1, y1, x2, y2, x3, y3, x4, y4, m_drawHandle);
}



