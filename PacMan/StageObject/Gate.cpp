#include "stdafx.h"
#include "Gate.h"
#include "EnemyBase.h"

static const char* Gate_Sprite_FilePath = "Assets/wall.bmp";

Gate::Gate(SceneBase* sceneBase) : Actor(sceneBase, "Gate", 0, RectCollision::EnCollisionType_Static)
{

}

Gate::~Gate()
{
}

void Gate::Init()
{
	int drawhandle = LoadGraph(Gate_Sprite_FilePath);
	m_drawHandle = DerivationGraph(80, 80, 24, 24, drawhandle);
}

void Gate::OnCollision(Actor* actor)
{
}

void Gate::Draw()
{
	m_spirte.Draw(m_position, m_drawHandle);
}
