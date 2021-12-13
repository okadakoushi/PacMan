#include "stdafx.h"
#include "Cookie.h"
#include "PacMan.h"
#include "SceneGame.h"

static const char* Cookie_Sprite = "Assets/LevelObjects/LevelObjects0-1.png";

Cookie::Cookie(SceneGame* sceneGame) : ItemBase(sceneGame, "Cookie", 0)
{
}

Cookie::~Cookie()
{
}

void Cookie::Init()
{
	m_score = COOKIE_SCORE;
	m_spirte.Init(Cookie_Sprite);
}

void Cookie::Draw()
{
	m_spirte.Draw(m_position);
}

void Cookie::HitEffect(Actor* actor)
{

	if (actor->GetHash() == std::hash<std::string>()("PacMan"))
	{
		//パックマンなので加点。
		PacMan* pacMan = dynamic_cast<PacMan*>(actor);
		if (pacMan != nullptr) 
		{
			__super::HitEffect(actor);
			m_actorExcutionFlag = Actor::EnExcutionFlagType_Dead;
			m_sceneGame->ReduceCookieCount();
		}
	}
}
