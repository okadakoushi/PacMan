#include "stdafx.h"
#include "Canvas.h"

void Canvas::SetPosition(Vector2_Int pos)
{
	if (m_parent != nullptr)
	{
		//親に合わせる。
		m_position = pos + m_parent->GetPosition();
	}
	else
	{
		m_position = pos;
	}
}
