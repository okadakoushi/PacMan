#pragma once

#include "Wall.h"
#include "SceneGame.h"

class PacMan : public Actor
{
private:
	enum animation {
		moveAnimatiomEnd = 3,
		deadAnimatiomEnd = 12,
		AniamtionNum
	};

private:
	const float MOVE_SPEED = 2.0f;				//移動速度。
	const Vector2 RESPAWN_POINT = { 500, 432 };	//復活地点。
	const Vector2 PLAYER_RESPAWN_POINT = { (float)SCREEN_WIDTH / 2 - SPRITE_SIZE / 2.0f , (float)SCREEN_HEIGHT / 2 + SPRITE_SIZE * 8.0f };

	Vector2 m_movedVector;						//動いたベクトル。
	Vector2 m_frontFrameMoved;					//前フレーム動いていた方向。
	int m_bufferedInput = 0;					//先行入力。
	bool m_powerMode = false;					//パワーモードかどうか。
	bool m_isDying = false;						//死亡演出中。
	SceneGame* m_sceneGamePtr = nullptr;		//シーンのポインタ。
	
	//アニメーション。
	const int AnimationSpeed = 1;
	const int DEAD_ANIMATION_SPEED = 7;
	const int DEAD_FIRST_EDN_ANIMATION_SPEED = 60;
	int m_drawHandle[AniamtionNum];
	int m_animationIndex = 0;
	int m_animationWaitFrame = 0;

public:
	PacMan(SceneBase* sceneBase);

public:
	virtual void Init() override;
	virtual void OnCollision(Actor* actor) override;
	virtual void Update() override;
	virtual void Draw() override;
	void MoveAnimationUpdate();
	void Death();
	bool PlayDeadAnim();
	void ResetParams();
public:

	/// <summary>
	/// 方向を取得。
	/// </summary>
	/// <returns></returns>
	const Vector2& GetDirection() const 
	{
		return m_frontFrameMoved.Normalized();
	}
	
	/// <summary>
	/// パワークッキーを入手しているか。
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

