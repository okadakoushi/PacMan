#include "stdafx.h"
#include "Canvas.h"

void Canvas::RegistChild(ParentChildComponent* child)
{
	m_childs.push_back(child);
}

void Canvas::RemoveChild(ParentChildComponent* child)
{
	auto it = std::find(m_childs.begin(), m_childs.end(), child);
	
	if (it != m_childs.end())
	{
		m_childs.erase(it);
	}
}

//ParentChildComponent* Canvas::GetChild()
//{
//	return nullptr;
//}
