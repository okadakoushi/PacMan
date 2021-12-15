#pragma once

#include "SceneBase.h"

class PlayerUI;

/// <summary>
/// シーンの管理者。
/// </summary>
class SceneManager
{
private:
	SceneBase::SCENE_ID m_currentState = SceneBase::EnSceneID_Title;	//現在のシーン番号。
	SceneBase* m_currentScene = nullptr;
	PlayerUI* m_UI = nullptr;

public:
	SceneManager();
	~SceneManager();

	/// <summary>
	/// 初期化。
	/// </summary>
	void Init();
	
	/// /// <summary>
	/// 更新。
	/// </summary>
	void Update();

	/// <summary>
	/// シーンを変更。
	/// </summary>
	/// <param name="sceneID"></param>
	void ChangeScene(SceneBase::SCENE_ID sceneID);
};

