#include "stdafx.h"
#include "Fruit.h"
#include "PacMan.h"

Fruit::Fruit(SceneBase* sceneBase) : ItemBase(sceneBase, "Fruit", 0)
{
}

Fruit::~Fruit()
{
}

void Fruit::Init()
{
	m_spirte.Init("Assets/fruit.bmp");
	m_score = FRUIT_SCORE;
	m_spriteSize = { 36,36 };
	GameSound()->Load("Assets/sound/eatpill.ogg");
}

void Fruit::Draw()
{
	m_spirte.Draw(m_position);
}

void Fruit::HitEffect(Actor* actor)
{
	__super::HitEffect(actor);

	if (actor->GetHash() == std::hash<std::string>()("PacMan"))
	{
		//パックマンなので加点。
		PacMan* pacMan = dynamic_cast<PacMan*>(actor);
		if (pacMan != nullptr) 
		{
			m_actorExcutionFlag = Actor::EnExcutionFlagType_Dead;
			GameSound()->Play(m_eatFruitSound);
		}
	}
}
