#include "stdafx.h"
#include "Fruit.h"
#include "Character/PacMan.h"

static const char* Fruit_Sprite_FilePath = "Assets/fruit.bmp";
static const char* Fruit_EatSE_FilePath = "Assets/sound/eatpill.ogg";

Fruit::Fruit(SceneGame* sceneGame) : ItemBase(sceneGame, "Fruit", 0)
{
}

Fruit::~Fruit()
{
}

void Fruit::Init()
{
	m_spirte.Init(Fruit_Sprite_FilePath);
	m_score = FRUIT_SCORE;
	m_collision.SetCollisionSize({ 36, 36 });
	m_eatFruitSound = GameSound()->Load(Fruit_EatSE_FilePath);
	m_scoreFont.Init("200", 13, 2);
	Vector2 DrawScorePosition = { m_position.x, m_position.y + 11 };
	m_scoreFont.SetPosition(EngineMath::ConvertToIntVec(DrawScorePosition));
}

void Fruit::Draw()
{
	if (!m_getFlag)
	{
		m_spirte.Draw(m_position);
	}
	else
	{
		m_scoreFont.Draw(GetColor(0, 255, 255));
	}
}

void Fruit::Update()
{
	if (m_getFlag)
	{
		//スコアを設定。
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
		//パックマンなので加点。
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
