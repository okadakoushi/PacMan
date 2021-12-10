#include "stdafx.h"
#include "Fruit.h"
#include "PacMan.h"

Fruit::Fruit(SceneGame* sceneGame) : ItemBase(sceneGame, "Fruit", 0)
{
}

Fruit::~Fruit()
{
}

void Fruit::Init()
{
	m_spirte.Init("Assets/fruit.bmp");
	m_score = FRUIT_SCORE;
	m_scoreFont.Init("200", 13, 2);
	m_collision.SetCollisionSize({ 36, 36 });
	m_eatFruitSound = GameSound()->Load("Assets/sound/eatpill.ogg");
}

void Fruit::Draw()
{
	if (!m_getFlag)
	{
		m_spirte.Draw(m_position);
	}
	else
	{
		m_scoreFont.Draw({ m_position.x, m_position.y + 11}, GetColor(0, 255, 255));
	}
}

void Fruit::Update()
{
	if (m_getFlag)
	{
		//�X�R�A��ݒ�B
		sprintf(m_buffer, "%d", FRUIT_SCORE);
		m_scoreFont.SetDispStr(m_buffer);
	
		m_socreDispTime += GameTime()->GetDeltaTime();
		if (m_socreDispTime > 1.5f)
		{
			m_actorExcutionFlag = Actor::EnExcutionFlagType_Dead;
		}
	}

}

void Fruit::OnCollision(Actor* actor)
{
	HitEffect(actor);
}

void Fruit::HitEffect(Actor* actor)
{
	if ( (actor->GetHash() == std::hash<std::string>()("PacMan") ) && !m_getFlag)
	{
		//�p�b�N�}���Ȃ̂ŉ��_�B
		PacMan* pacMan = dynamic_cast<PacMan*>(actor);
		if (pacMan != nullptr) 
		{
			__super::HitEffect(actor);
			GameSound()->Play(m_eatFruitSound);
			m_sceneGame->AddScore(m_score);
			m_getFlag = true;
		}
	}
}
