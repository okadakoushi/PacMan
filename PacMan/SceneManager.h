#pragma once

#include "SceneBase.h"

class PlayerUI;

/// <summary>
/// �V�[���̊Ǘ��ҁB
/// </summary>
class SceneManager
{
private:
	SceneBase::SCENE_ID m_currentState = SceneBase::EnSceneID_Title;	//���݂̃V�[���ԍ��B
	SceneBase* m_currentScene = nullptr;
	PlayerUI* m_UI = nullptr;

public:
	SceneManager();
	~SceneManager();

	/// <summary>
	/// �������B
	/// </summary>
	void Init();
	
	/// /// <summary>
	/// �X�V�B
	/// </summary>
	void Update();

	/// <summary>
	/// �V�[����ύX�B
	/// </summary>
	/// <param name="sceneID"></param>
	void ChangeScene(SceneBase::SCENE_ID sceneID);
};

