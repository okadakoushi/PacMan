#include "stdafx.h"
#include "Cookie.h"
#include "PacMan.h"
#include "SceneGame.h"

Cookie::Cookie(SceneGame* sceneGame) : ItemBase(sceneGame, "Cookie", 0)
{
}

void Cookie::Init()
{
	m_score = COOKIE_SCORE;
	m_spirte.Init("Assets/LevelObjects/LevelObjects0-1.png");
}

void Cookie::Draw()
{
	m_spirte.Draw(m_position);
}

void Cookie::HitEffect(Actor* actor)
{
	__super::HitEffect(actor);

	if (actor->GetHash() == std::hash<std::string>()("PacMan"))
	{
		//パックマンなので加点。
		PacMan* pacMan = dynamic_cast<PacMan*>(actor);
		if (pacMan != nullptr) 
		{
			m_actorExcutionFlag = Actor::EnExcutionFlagType_Dead;
			m_sceneGame->ReduceCookieCount();

		}
	}
}
