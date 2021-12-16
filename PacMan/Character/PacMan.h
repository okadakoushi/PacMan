#pragma once

#include "StageObject/Wall.h"
#include "SceneGame.h"

class PacMan : public Actor
{
private:
	enum ANIMATION {
		moveAnimatiomEnd = 3,
		deadAnimatiomEnd = 12,
		AniamtionNum
	};

private:
	const float MOVE_SPEED = 2.00f;				//移動速度。
	const Vector2 PLAYER_RESPAWN_POINT = { (float)SCREEN_WIDTH / 2 - SPRITE_SIZE / 2.0f +1 , (float)SCREEN_HEIGHT / 2 + SPRITE_SIZE * 8.0f };

	Vector2 m_movedVector;						//動いたベクトル。
	Vector2 m_frontFrameMoved;					//前フレーム動いていた方向。
	int m_bufferedInput = 0;					//先行入力。
	bool m_powerMode = false;					//パワーモードかどうか。
	bool m_isDying = false;						//死亡演出中。
	SceneGame* m_sceneGamePtr = nullptr;		//シーンのポインタ。
	
	//アニメーション。
	const int AnimationSpeed = 1;					//アニメーション速度
	const int DEAD_ANIMATION_SPEED = 7;				//死亡アニメーション速度
	const int DEAD_FIRST_EDN_ANIMATION_SPEED = 60;	//先端と終端の速度。
	int m_drawHandle[AniamtionNum] = { 0 };			//アニメーション分のハンドル。
	int m_animationIndex = 0;						//インデックス。
	int m_frontFrameAnimIndex = 0;					//前フレームのアニメーション。
	int m_animationWaitFrame = 0;					//アニメーション切り替えのフレーム数。

	//サウンド。
	int m_deadSE = 0;								//死亡SE。
	int m_eatingSE = 0;								//Cookie食べる音。

public:
	PacMan(SceneBase* sceneBase);
	virtual ~PacMan();

public:
	virtual void Init() override;
	virtual void OnCollision(Actor* actor) override;
	virtual void Update() override;
	virtual void Draw() override;

	/// <summary>
	/// 移動アニメーションの更新。
	/// </summary>
	void MoveAnimationUpdate();

	/// <summary>
	/// 死亡処理。
	/// </summary>
	void Death();

	/// <summary>
	/// 死亡アニメーションを再生。
	/// </summary>
	/// <returns>再生が終端まで行ったら、trueを返す。</returns>
	bool PlayDeadAnim();

	/// <summary>
	/// パラメーターをリセット。
	/// </summary>
	void ResetParams();

public:
	/// <summary>
	/// 方向を取得。
	/// </summary>
	/// <returns></returns>
	Vector2 GetDirection() 
	{
		return m_frontFrameMoved.Normalized();
	}
	
	/// <summary>
	/// パワーモードか。
	/// </summary>
	/// <returns></returns>
	bool IsPowerMode() 
	{
		return m_powerMode;
	}

	/// <summary>
	/// 死亡演出中か.
	/// </summary>
	/// <returns></returns>
	bool IsDying()
	{
		return m_isDying;
	}
	
	/// <summary>
	/// パワークッキーを取っているかを設定。
	/// </summary>
	/// <param name="isGet"></param>
	void SetPowerMode(bool isPowerMode)
	{
		m_powerMode = isPowerMode;
	}

private:
	/// <summary>
	/// 障害物と衝突していないか確認。
	/// </summary>
	bool CheckHitObstacle();
};

