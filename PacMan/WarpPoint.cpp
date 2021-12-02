#include "stdafx.h"
#include "WarpPoint.h"

WarpPoint::WarpPoint(SceneBase* sceneBase) : Actor(sceneBase, "WarpPoint", 0, RectCollision::EnCollisionType_Static)
{

}

void WarpPoint::Init()
{
	m_spirte.Init("Assets/portal.bmp");
}

void WarpPoint::Update()
{
}

void WarpPoint::OnCollision(Actor* actor)
{
	Vector2 fix = m_position - CENTER_POSITION;
	float direction = std::clamp(fix.x, -1.0f, 1.0f);
	float xLen = abs(fix.x);
	xLen = (xLen / 24) * 24;
	if (xLen < actor->GetPosition().x - CENTER_POSITION.x)
	{
		actor->SetPosition({ xLen * direction, actor->GetPosition().y });
	}
}

void WarpPoint::Draw()
{
	m_spirte.Draw(m_position);
}
