#include "stdafx.h"
#include "Gate.h"
#include "EnemyBase.h"

Gate::Gate(SceneBase* sceneBase) : Actor(sceneBase, "Gate", 0, RectCollision::EnCollisionType_Static)
{

}

Gate::~Gate()
{
}

void Gate::Init()
{
	int drawhandle = LoadGraph("Assets/wall.bmp");
	m_drawHandle = DerivationGraph(80, 80, 24, 24, drawhandle);
}

void Gate::OnCollision(Actor* actor)
{
}

void Gate::Draw()
{
	m_spirte.Draw(m_position, m_drawHandle);
}
