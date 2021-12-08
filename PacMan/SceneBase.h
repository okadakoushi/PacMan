#pragma once

#include "Object.h"

class Actor;
class SceneManager;

class SceneBase : public Object
{
public:
	/// <summary>
	/// SceneID.
	/// </summary>
	enum SceneID
	{
		EnSceneID_Title,
		EnSceneID_Game,
		EnSceneID_GameOver,
	};

protected:
	SceneID				m_nextStage = EnSceneID_Title;	//次のシーン。
	SceneManager*		m_sceneManagerPtr = nullptr;	//Managerへのptr。	
	std::vector<Actor*>	m_actorList;					//アクターリスト。

private:
	float				m_waitTime = 0.0f;				//waitタイム。
	float				m_currentWaitTime = 0.0f;		//現在の待ち時間。

public:
	/// <summary>
	/// コンストラクタ。
	/// </summary>
	/// <param name="sceneManager">シーンマネージャー。</param>
	SceneBase(SceneManager* sceneManager):
		Object::Object(0),
		m_sceneManagerPtr(sceneManager)
	{
	}
	/// <summary>
	/// デストラクタ。
	/// </summary>
	virtual ~SceneBase()
	{

	}

public:
	/// <summary>
	/// アクターを登録。
	/// </summary>
	/// <param name="actor">登録するアクター。</param>
	void RegistActor(Actor* actor);

	/// <summary>
	/// アクターを取得。
	/// </summary>
	/// <param name="tag">取得したいActorのタグ。</param>
	Actor* GetActor(const char* tag);

	/// <summary>
	/// 登録解除。
	/// </summary>
	/// <param name="actor"></param>
	void UnRegistActor(Actor* actor);

	/// <summary>
	/// 初期化。
	/// </summary>
	virtual void Init() = 0;

	/// <summary>
	/// 更新。
	/// </summary>
	virtual void Update();

private:
	///// <summary>
	///// クリーンアップ。
	///// </summary>
	//void CleanUp();

	/// <summary>
	/// コリジョン同士が当たっているかのチェック。
	/// </summary>
	void CheckHitActorCollision();
};

