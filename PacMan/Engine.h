#pragma once

#include "SceneManager.h"

class Engine
{
private:
	SceneManager m_sceneManager;
public:
	Engine();
public:
	/// <summary>
	/// �G���W���������B
	/// </summary>
	int InitEngine();

	/// <summary>
	/// �G���W���X�V�B
	/// </summary>
	void ExcuteEngine();

	/// <summary>
	/// �f�o�b�O�p�̃��C����`��B
	/// </summary>
	void DebugLineDraw();
private:
	/// <summary>
	/// �}�l�[�W���[���X�V�B
	/// </summary>
	void ExcuteManager();
};

