#include "stdafx.h"
#include "SceneManager.h"
#include "SceneBase.h"
#include "SceneGame.h"
#include "SceneTitle.h"
#include "GameOver.h"

SceneManager::SceneManager()
{
}

SceneManager::~SceneManager()
{
}

void SceneManager::Init()
{
	//最初のシーン。
	m_currentScene = new SceneTitle(this);
	m_currentScene->Init();
}

void SceneManager::Update()
{
	m_currentScene->Update();
}

void SceneManager::ChangeScene(SceneBase::SceneID sceneID)
{
	switch (sceneID)
	{
		case SceneBase::EnSceneID_Title:
			//タイトル。
			m_currentScene = new SceneTitle(this);
			break;
		case SceneBase::EnSceneID_Game:
			//ゲーム。
			m_currentScene = new SceneGame(this);
			break;
		case SceneBase::EnSceneID_GameOver:
			m_currentScene = new GameOver(this);
			//ゲームオーバー。
			break;
	}
	//シーン初期化。
	m_currentScene->Init();
}
