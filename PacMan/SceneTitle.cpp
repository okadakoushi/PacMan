#include "stdafx.h"
#include "SceneTitle.h"

SceneTitle::SceneTitle(SceneManager* sceneManager) : SceneBase(sceneManager)
{
}

SceneTitle::~SceneTitle()
{
}

void SceneTitle::Init()
{
	m_title.Init("Assets/title.bmp");

}

void SceneTitle::Update()
{
	m_title.Draw({ CENTER_POSITION.x - 217, CENTER_POSITION.y - 54 });

	if (m_isStart)
	{
		if (m_fadeColor < 0)
		{
			m_sceneManagerPtr->ChangeScene(SceneBase::EnSceneID_Game);
			m_fadeColor = 255;
		}
		m_fadeColor -= FADE_SPEED;
		SetDrawBright(m_fadeColor, m_fadeColor, m_fadeColor);
		return;
	}

	m_isStart = CheckHitKey(KEY_INPUT_Z);
}
