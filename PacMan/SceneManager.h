#pragma once

#include "SceneBase.h"

class PlayerUI;

/// <summary>
/// �V�[���̊Ǘ��ҁB
/// </summary>
class SceneManager
{
private:
	SceneBase::SceneID m_currentState;		//���݂̃V�[���ԍ��B
	SceneBase* m_currentScene;
	PlayerUI* m_UI;

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
	void ChangeScene(SceneBase::SceneID sceneID);
};

