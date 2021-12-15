#include "stdafx.h"
#include "SceneManager.h"
#include "SceneBase.h"
#include "SceneGame.h"
#include "SceneTitle.h"
#include "GameOver.h"
#include "PlayerUI.h"

SceneManager::SceneManager()
{
}

SceneManager::~SceneManager()
{
}

void SceneManager::Init()
{
	//�ŏ��̃V�[���B
	m_currentScene = new SceneTitle(this);
	m_currentScene->Init();
	m_UI = new PlayerUI;
}

void SceneManager::Update()
{
	m_currentScene->Update();
}

void SceneManager::ChangeScene(SceneBase::SCENE_ID sceneID)
{
	//�폜����V�[���B
	SceneBase* deleteScene = m_currentScene;
	delete deleteScene;
	
	//�I�������B
	InitGraph();//todo:Graphics��flywWeight����������A�o���N�̃������͏������炢���Ȃ��̂ł��̃R�[�h�͏����B
	GameSound()->AllStop();

	switch (sceneID)
	{
		case SceneBase::EnSceneID_Title:
			//�^�C�g���B
			m_currentScene = new SceneTitle(this);
			break;
		case SceneBase::EnSceneID_Game:
			//�Q�[���B
			m_currentScene = new SceneGame(this, m_UI);
			break;
		case SceneBase::EnSceneID_GameOver:
			m_currentScene = new GameOver(this);
			//�Q�[���I�[�o�[�B
			break;
	}

	//�V�[���������B
	m_currentScene->Init();
}
