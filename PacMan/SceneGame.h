#pragma once

#include "StageLoader.h"
#include "EnemyBase.h"
#include "Font.h"
#include "Stage.h"

class Fruit;
class PlayerUI;
class PacMan;
class EnemyBase;

/// <summary>
/// ゲームシーン。
/// </summary>
class SceneGame : public SceneBase
{
protected:
	enum IsCallDeadEventFlag
	{
		EnCalledDeadEvent_None		= 0b0000,
		EnCalledDeadEvent_BLINKY	= 0b0001,
		EnCalledDeadEvent_PINKY		= 0b0010,
		EnCalledDeadEvent_INKY		= 0b0100,
		EnCalledDeadEvent_CLYDE		= 0b1000,
	};

	enum GameBGMType
	{
		GameBGMType_Normal,		//ノーマルサイレン音
		GameBGMType_PowerMode,	//PowerMode
		GameBGMType_Return,		//牢獄帰還音
		GameBGMType_Num			//サウンドの数。
	};

	enum GameState
	{
		GameState_WaitGameStart,
		GameState_Running,
		GameState_EatingWait,
		GameState_PlayerDead,
		GameState_NextRound,
	};

private:

	std::vector<Actor*> m_obstacleList;						//障害物一覧。
	GameState m_currentGameState = GameState_WaitGameStart;	//現在のゲームステート。

	//UIパラメーター。
	int m_lifePoint = 3;								//残機数。
	int m_score = 0;									//得点。
	int m_lifeExtendSocre = 10000;							

	//インスタンスのptr記憶。
	SceneManager* m_sceneManager = nullptr;				//SceneManager。
	PacMan* m_pacMan			 = nullptr;				//PacMan。
	PlayerUI* m_playerUI		 = nullptr;				//PlayerUI。
	Stage m_stage;										//ステージ。
	std::vector<EnemyBase*> m_enemyList;				//エネミーのリスト。

	//フルーツ生成用のパラメーター。
	const float FRUIT_APPEAR_DISAPPEAR_TIME = 10.0f;	//フルーツ用、出現or消失タイマー。
	Vector2 m_apperFruitPosition;						//フルーツの出現地点。
	float m_fruitTimer = 0.0f;							//フルーツ用のタイマー。
	Fruit* m_fruit = nullptr;							//フルーツ。

	//Enemyを食べたイベント用。
	const float WAIT_EATING_TINE = 1.0f;				//食べる演出の時間。
	bool m_isPowerMode = false;							//パワーモードフラグ。
	int m_isCallDeadEventFlags = EnCalledDeadEvent_None;//どの敵が食べられたのか識別用。
	Font m_scoreFont;									//エネミーが食べられた時のスコア表示。
	int m_currentEatScore = 100;						//現在のスコア。
	char m_scoreBuffer[12];								//スコア用のバッファー。

	//CHASE_SCATTER切り替え用。
	const float	CHASE_TIME = 20.0f;						//追跡モード時の時間。
	const float SCATTER_TIME = 6.0f;					//散開モード。
	bool m_isChaseMode = false;							//現在どちらのステートか。														
	static std::map<bool, std::pair<const float, EnemyBase::EnemyState>> m_isChaseToChageStateTimeAndMoveState;	//chaseモードフラグから切り替え時間と次の移動ステートを取得。
	static std::map<int, int> m_restCookieCountToFrequency;	//残りのクッキーの数から周波数を取得。
	
	//ゲーム進行用。
	const float CHARACTER_SPAWN_TIME = 3.0f;					//キャラクターを生成する
	const float START_GAME_TIME = CHARACTER_SPAWN_TIME + 1.5f;	//ゲームを開始する。
	const float BLINKING_TIME = 1.5f;							//点滅時間。
	const float NEXT_STAGE_TIME = BLINKING_TIME + 1.0f;			//次ステージ。

	//sound.
	int m_enemySEList[GameBGMType_Num];
	int m_openingBGM = 0;								//オープニング。
	int m_eatingEnemySE = 0;							//敵を食べた。
	int m_extraSE = 0;									//ライフポイント追加。

	GameBGMType m_nextPlaySound = GameBGMType_Normal;	//次に流す曲。

	//Timer.
	//シーン用。
	float m_sceneStartDeltaTime = 0.0f;					//シーンが始まってからの時間。
	float m_nextStageTimer = 0.0f;						//点滅管理
	//Ghost用。
	float m_enemyChaseTimer = 0.0f;						//敵キャラの追跡、散開を切り替える用のタイマー。
	float m_eatingWaitTimer = 0.0f;						//食べる演出を待った時間。

	//Ready
	Sprite m_readySprite;
	int m_drawHandle = 0;

	//敵のwaitTime
	const float ENEMY_WAIT_TIME[3] = {
		START_GAME_TIME + 1.0f,		//PINKY出撃。
		START_GAME_TIME + 5.0f,		//INKY出撃。
		START_GAME_TIME + 9.0f		//CLYDE出撃。
	};

	//敵の初期位置。
	const Vector2 ENEMY_START_POS[4] = {
		{ CENTER_POSITION.x - SPRITE_SIZE, CENTER_POSITION.y - SPRITE_SIZE * 4.0f },
		{ CENTER_POSITION.x - SPRITE_SIZE, CENTER_POSITION.y - SPRITE_SIZE * 2.0f },
		{ CENTER_POSITION.x - SPRITE_SIZE * 3, CENTER_POSITION.y - SPRITE_SIZE * 1.0f },
		{ CENTER_POSITION.x + SPRITE_SIZE * 2, CENTER_POSITION.y - SPRITE_SIZE * 1.0f }
	};

public:
	SceneGame(SceneManager* sceneManager);
	virtual ~SceneGame();
	virtual void Init() override;
	virtual void Update() override;

	/// <summary>
	/// 障害物リスト。
	/// </summary>
	/// <param name="actor"></param>
	void AddObstacle(Actor* actor)
	{
		m_obstacleList.push_back(actor);
	}

	/// <summary>
	/// 障害物のリストを取得。
	/// </summary>
	/// <returns></returns>
	const std::vector<Actor*>& GetObstacles() const  
	{
		return m_obstacleList;
	}

	/// <summary>
	/// スコアを加算。
	/// </summary>
	/// <param name="score"></param>
	void AddScore(int score);

	/// <summary>
	/// クッキーカウントを減らす。
	/// </summary>
	void ReduceCookieCount()
	{
		m_stage.ReduceCookieCount();
	}

protected:
	/// <summary>
	/// エネミー生成。
	/// </summary>
	void CreateEnemy();

	/// <summary>
	/// Playerが死亡した際に呼ばれるイベント。
	/// </summary>
	void PlayerDeadEvent();

	/// <summary>
	/// エネミーのステートを変更するイベント。
	/// </summary>
	void EnemyEvent();

	/// <summary>
	/// 次のラウンドへ。
	/// </summary>
	void NextRound();

private:
	/// <summary>
	/// フルーツが出現できるか。
	/// </summary>
	void FruitEvent();

	/// <summary>
	/// パラメーターをリセット。
	/// </summary>
	void ResetParams();
};

