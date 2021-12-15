#include "stdafx.h"
#include "SceneTitle.h"

static const char* TitleSprite_FilePath = "Assets/title.bmp";

SceneTitle::SceneTitle(SceneManager* sceneManager) : SceneBase(sceneManager)
{
}

SceneTitle::~SceneTitle()
{
	SetDrawBright(255, 255, 255);
}

void SceneTitle::Init()
{
	m_title.Init(TitleSprite_FilePath);
}

void SceneTitle::Update()
{
	m_title.Draw({ CENTER_POSITION.x - 217, CENTER_POSITION.y - 54 });

	if (m_isStart)
	{
		if (m_fadeColor < 0)
		{
			m_sceneManagerPtr->ChangeScene(SceneBase::EnSceneID_Game);
			return;
		}
		m_fadeColor -= FADE_SPEED;
		SetDrawBright(m_fadeColor, m_fadeColor, m_fadeColor);
		return;
	}

	m_isStart = CheckHitKey(KEY_INPUT_Z);
}
