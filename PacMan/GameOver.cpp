#include "stdafx.h"
#include "GameOver.h"

GameOver::GameOver(SceneManager* sceneManager) : SceneBase(sceneManager)
{
}

GameOver::~GameOver()
{
}

void GameOver::Init()
{
	int drawhandle = LoadGraph("Assets/inStageMessage.bmp");
	m_drawHandle = DerivationGraph(0, 48, 128, 24, drawhandle);
}

void GameOver::Update()
{

	m_gameOverSprite.Draw({ CENTER_POSITION.x, CENTER_POSITION.y }, 3.0f, 0, m_drawHandle);

	if (m_isStart)
	{
		if (m_fadeColor < 0)
		{
			m_sceneManagerPtr->ChangeScene(SceneBase::EnSceneID_Title);
			m_fadeColor = 255;
		}
		m_fadeColor -= FADE_SPEED;
		SetDrawBright(m_fadeColor, m_fadeColor, m_fadeColor);
		return;
	}
	m_isStart = CheckHitKey(KEY_INPUT_Z);

}
