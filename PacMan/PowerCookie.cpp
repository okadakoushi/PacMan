#include "stdafx.h"
#include "PowerCookie.h"
#include "PacMan.h"
#include "PlayerUI.h"

static const char* PowerCookie_Sprite_FilePath = "Assets/LevelObjects/LevelObjects0-0.png";

PowerCookie::PowerCookie(SceneGame* sceneGame) : ItemBase(sceneGame, "PowerCookie", 0)
{
}

PowerCookie::~PowerCookie()
{
}

void PowerCookie::Init()
{
	m_spirte.Init(PowerCookie_Sprite_FilePath);
	m_score = POWER_COOKIE_SCORE;
}

void PowerCookie::Update()
{
	if (++m_blinkingFrame > POWER_COOKIE_BLINKING_FRAME)
	{
		if (m_actorExcutionFlag == EnExcutionFlagType_Active)
		{
			SetExcutionFlag(EnExcutionFlagType_Update);
		}
		else if(m_actorExcutionFlag == EnExcutionFlagType_Update)
		{
			SetExcutionFlag(EnExcutionFlagType_Active);
		}
		m_blinkingFrame = 0;
	}
}

void PowerCookie::Draw()
{
	m_spirte.Draw(m_position);
}

void PowerCookie::HitEffect(Actor* actor)
{
	__super::HitEffect(actor);

	if (actor->GetHash() == std::hash<std::string>()("PacMan"))
	{
		//パックマン。
		PacMan* pacMan = dynamic_cast<PacMan*>(actor);
		if (pacMan != nullptr) 
		{
			//パワーモードに変更。
			pacMan->SetPowerMode(true);
			m_actorExcutionFlag = Actor::EnExcutionFlagType_Dead;
			m_sceneGame->ReduceCookieCount();
		}
	}
}
	
