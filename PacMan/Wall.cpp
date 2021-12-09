#include "stdafx.h"
#include "Wall.h"

Wall::Wall(SceneBase* sceneBase) : Actor(sceneBase, "Wall", 0, RectCollision::EnCollisionType_Static)
{
}

Wall::~Wall()
{
}

void Wall::Init()
{
	m_spirte.Init(m_filePath);
}

void Wall::Update()
{
}

void Wall::Draw()
{
	m_spirte.Draw(m_position);
}
