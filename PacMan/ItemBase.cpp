#include "stdafx.h"
#include "ItemBase.h"
#include "PlayerUI.h"

ItemBase::ItemBase(SceneBase* sceneBase, const char* tag, int prio) : Actor(sceneBase, tag, prio, RectCollision::EnCollisionType_Static)
{
	m_sceneGame = dynamic_cast<SceneGame*>(sceneBase);
	assert(m_sceneGame);
}

void ItemBase::HitEffect(Actor* actor)
{
	m_sceneGame->AddScore(m_score);
}
