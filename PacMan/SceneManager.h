#pragma once

#include "SceneBase.h"

/// <summary>
/// �V�[���̊Ǘ��ҁB
/// </summary>
class SceneManager
{
private:
	SceneBase::SceneID m_currentState;		//���݂̃V�[���ԍ��B
	SceneBase* m_currentScene;
public:
	/// <summary>
	/// �������B
	/// </summary>
	void Init();
	/// <summary>
	/// �X�V�B
	/// </summary>
	void Update();
	void ChangeScene(SceneBase::SceneID sceneID);
};

