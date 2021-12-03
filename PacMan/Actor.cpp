#include "stdafx.h"
#include "Actor.h"
#include "SceneBase.h"
#include "RectCollision.h"

Actor::Actor(SceneBase* sceneBase, std::string tag, int prio, RectCollision::CollisionType colType) : 
	Object(prio),
	m_collision(colType)
{
	m_sceneBasePtr = sceneBase;
	m_sceneBasePtr->RegistActor(this);
	m_hash = std::hash<std::string>()(tag);
}

Actor::~Actor()
{
	m_sceneBasePtr->UnRegistActor(this);
}