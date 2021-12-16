#include "stdafx.h"
#include "WarpPoint.h"

static const char* PortalSprite_FilePath = "Assets/portal.bmp";

WarpPoint::WarpPoint(SceneBase* sceneBase) : Actor(sceneBase, "WarpPoint", 0, RectCollision::EnCollisionType_Static)
{

}

WarpPoint::~WarpPoint()
{
}

void WarpPoint::Init()
{
	m_spirte.Init(PortalSprite_FilePath);
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
