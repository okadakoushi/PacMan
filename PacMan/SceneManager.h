#pragma once

#include "SceneBase.h"

/// <summary>
/// シーンの管理者。
/// </summary>
class SceneManager
{
private:
	SceneBase::SceneID m_currentState;		//現在のシーン番号。
	SceneBase* m_currentScene;
public:
	/// <summary>
	/// 初期化。
	/// </summary>
	void Init();
	/// <summary>
	/// 更新。
	/// </summary>
	void Update();
	void ChangeScene(SceneBase::SceneID sceneID);
};

