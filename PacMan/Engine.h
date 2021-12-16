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
	/// エンジン初期化。
	/// </summary>
	int InitEngine();

	/// <summary>
	/// エンジン更新。
	/// </summary>
	void ExcuteEngine();

	/// <summary>
	/// デバッグ用のラインを描画。
	/// </summary>
	void DebugLineDraw();
private:
	/// <summary>
	/// マネージャーを更新。
	/// </summary>
	void ExcuteManager();
};

