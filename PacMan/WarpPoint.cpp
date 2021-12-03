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
	xLen = ((xLen / SPRITE_SIZE) * SPRITE_SIZE) * -direction;
	if (direction < 0)
	{
		xLen -= SPRITE_SIZE * 2;
	}
	actor->SetPosition({ xLen + CENTER_POSITION.x, actor->GetPosition().y });
}

void WarpPoint::Draw()
{
	m_spirte.Draw(m_position);
}
