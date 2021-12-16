#include "stdafx.h"
#include "SceneGame.h"
#include "SceneBase.h"
#include "Character/PacMan.h"
#include "Character/Enemy/EnemyBase.h"
#include "Character/Enemy/Enemy_BLINKY.h"
#include "Character/Enemy/Enemy_Pinky.h"
#include "Character/Enemy/Enemy_INKY.h"
#include "Character/Enemy/Enemy_POKEY.h"
#include "StageObject/Fruit.h"
#include "PlayerUI.h"
#include "Stage.h"

static const char* StageMassage_FilePath	= "Assets/inStageMessage.bmp";
static const char* Opening_FilePath			= "Assets/sound/opening_song.ogg";
static const char* ExtraSE_FilePath			= "Assets/sound/extend.wav";
static const char* SirenSE_FilePath			= "Assets/sound/siren_1.wav";
static const char* TweekModeSE_FilePath		= "Assets/sound/power_pellet.wav";
static const char* ReturnModeSE_FilePath	= "Assets/sound/retreating.wav";
static const char* EatingSE_FilePath		= "Assets/sound/eatghost.ogg";

std::map<bool, std::pair<const float, EnemyBase::ENEMY_STATE>> SceneGame::m_isChaseToChageStateTimeAndMoveState
{
	//scatterモード時。
	{false, {6.0f, EnemyBase::ScatterMode} },
	//chaseモード時。
	{true, {20.0f, EnemyBase::ChaseMode} }
};

std::map<int, int> SceneGame::m_restCookieCountToFrequency
{
	//残りクッキー、周波数。
	{248, 45050},
	{198, 55050},
	{148, 60000},
	{98, 65000},
	{48, 70000},
};

SceneGame::SceneGame(SceneManager* sceneManager, PlayerUI* ui) : 
	SceneBase(sceneManager),
	m_playerUI(ui),
	m_stage(this)
{
}

SceneGame::~SceneGame()
{
	CleanUp();
}

void SceneGame::Init()
{
	m_stage.Init();
	
	//スコア初期化。
	int size = sizeof(m_scoreBuffer) / sizeof(char);
	snprintf(m_scoreBuffer, size, "%d", m_currentEatScore);
	m_scoreFont.Init(m_scoreBuffer, 13, 2);

	//GameOver用Sprite初期化。
	int drawhandle = LoadGraph(StageMassage_FilePath);
	int GameOverHanlde = DerivationGraph(0, 0, 128, 24, drawhandle);
	m_readySprite.Init(GameOverHanlde);

	//サウンドロード。
	m_enemySEList[GameBGMType_Normal] = GameSound()->Load(SirenSE_FilePath);
	ChangeVolumeSoundMem(255, m_enemySEList[GameBGMType_Normal]);
	m_enemySEList[GameBGMType_PowerMode] = GameSound()->Load(TweekModeSE_FilePath);
	m_enemySEList[GameBGMType_Return] = GameSound()->Load(ReturnModeSE_FilePath);
	m_openingBGM = GameSound()->Load(Opening_FilePath);
	m_eatingEnemySE = GameSound()->Load(EatingSE_FilePath);
	m_extraSE = GameSound()->Load(ExtraSE_FilePath);

	//フルーツの位置。
	m_apperFruitPosition = { CENTER_POSITION.x - 24.0f, CENTER_POSITION.y + 24.0f };

	m_playerUI->Init();

	GameSound()->Play(m_openingBGM);
}

void SceneGame::AddScore(int score)
{
	m_score += score;

	if (m_score > m_lifeExtendSocre)
	{
		m_lifePoint++;
		m_lifeExtendSocre += 10000;
		GameSound()->Play(m_extraSE);
	}

	m_lifePoint = std::clamp(m_lifePoint, 0, 3);
	m_score = std::clamp(m_score, 0, 99999);
}

void SceneGame::CreateEnemy()
{
	Enemy_BLINKY* enemy_blinky = new Enemy_BLINKY(this, m_pacMan, ENEMY_START_POS[0]);
	m_enemyList.push_back(enemy_blinky);
	Enemy_Pinky* enemy_pinky = new Enemy_Pinky(this, m_pacMan, ENEMY_START_POS[1]);
	m_enemyList.push_back(enemy_pinky);
	Enemy_INKY* enemy_inky = new Enemy_INKY(this, m_pacMan, enemy_blinky, ENEMY_START_POS[2]);
	m_enemyList.push_back(enemy_inky);
	Enemy_POKEY* enemy_pokey = new Enemy_POKEY(this, m_pacMan, ENEMY_START_POS[3]);
	m_enemyList.push_back(enemy_pokey);

	for (auto* enemy : m_enemyList)
	{
		enemy->Init();
		enemy->ChangeCurrentState(EnemyBase::InPrisonMode);
	}
	//ブリンキーは最初から外。
	enemy_blinky->ChangeCurrentState(EnemyBase::ScatterMode);

}

void SceneGame::Update()
{
	//基底のUpdate呼び出し。
	__super::Update();

	m_sceneStartDeltaTime += GameTime()->GetDeltaTime();
	
	if (m_currentGameState != GameState_NextRound)
	{
		//次ラウンド遷移中はUI表示を行わない。
		m_playerUI->Update(m_score, m_lifePoint);
	}

	switch (m_currentGameState)
	{
	case SceneGame::GameState_WaitGameStart:
		//ゲームスタート待ち//
		WaitGameStartProcess();
		break;

	case SceneGame::GameState_Running:
		//ゲーム実行中//
		GameRunningProcess();
		break;

	case SceneGame::GameState_EatingWait:
		//敵を食べる演出中//
		WaitEatingProcess();
		break;

	case SceneGame::GameState_PlayerDead:
		//プレイヤー死亡演出//
		PlayerDeadProcess();
		break;
	
	case SceneGame::GameState_NextRound:
		//次ラウンドに進む//
		NextRoundProcess();
		break;

	}//swich-case
}

void SceneGame::EnemyEvent()
{
	for (int i = 1; i < m_enemyList.size(); i++)
	{
		if ( (m_sceneStartDeltaTime >= ENEMY_WAIT_TIME[i - 1]) && (m_enemyList[i]->GetCurrentState() == EnemyBase::InPrisonMode) )
		{
			m_enemyList[i]->ChangeCurrentState(EnemyBase::GetOutPrisonMode);
		}
	}

	//タイマーに応じて、Chase/Scatterを切り替え。
	if (m_enemyChaseTimer > m_isChaseToChageStateTimeAndMoveState[m_isChaseMode].first)
	{
		//フラグ切り替え。
		m_isChaseMode = !m_isChaseMode;
		m_enemyChaseTimer = 0.0f;
	}

	int TweekEnemyCount = 0;

	for (int i = 0; i < m_enemyList.size(); i++)
	{
		EnemyBase::ENEMY_STATE enemyCurrentState = m_enemyList[i]->GetCurrentState();

		if ( (enemyCurrentState == EnemyBase::ChaseMode) || (enemyCurrentState == EnemyBase::ScatterMode) )
		{
			//毎フレームEnemyをChase/Scatterモードに変更。
			EnemyBase::ENEMY_STATE frontFrameState = m_enemyList[i]->GetCurrentState();
			EnemyBase::ENEMY_STATE nextState = m_isChaseToChageStateTimeAndMoveState[m_isChaseMode].second;
			m_enemyList[i]->ChangeCurrentState(nextState);
			if (frontFrameState != m_enemyList[i]->GetCurrentState())
			{
				m_enemyList[i]->Turning();
			}
		}

		if ( (enemyCurrentState == EnemyBase::ReturnPrisonMode) && !m_enemyList[i]->IsCallDeadEvent())
		{
			//敵が死亡状態。該当Enemyのフラグを上げる。
			m_isCallDeadEventFlags |= (1 << i);
			m_enemyList[i]->SetDeadEvent(true);
			//スコアも更新。
			m_currentEatScore *= 2;
			AddScore(m_currentEatScore);
		}
	}

	//流す曲の決定。
	{
		//通常状態のゴーストの数。
		size_t normalEnemyCount = m_enemyList.size();
		
		for (auto* enemy : m_enemyList)
		{
			if (enemy->GetCurrentState() == EnemyBase::ReturnPrisonMode)
			{
				m_nextPlaySound = GameBGMType_Return;
				normalEnemyCount--;
				break;
			}
			else if (enemy->IsTweek())
			{
				m_nextPlaySound = GameBGMType_PowerMode;
				normalEnemyCount--;
			}
		}
		if (normalEnemyCount == m_enemyList.size())
		{
			//特殊状態の敵はいないので通常再生。
			m_nextPlaySound = GameBGMType_Normal;
			//周波数を残りのクッキー数に応じて変更する。
			int speed = m_restCookieCountToFrequency[m_stage.GetRestCookieCount()];
			if (speed)
			{
				SetFrequencySoundMem(speed, m_enemySEList[m_nextPlaySound]);
			}
		}
	}

	//いらない曲は止める/曲を流す。
	for (auto handle : m_enemySEList)
	{
		if (m_enemySEList[m_nextPlaySound] == handle)
		{
			GameSound()->Play(handle, SoundManager::PlayingType_EndPlaying, SoundManager::PlayType_Back | SoundManager::PlayType_Loop);
		}
		else
		{
			StopSoundMem(handle);
		}
	}

	//パックマンがパワークッキーを取っているかの監視。
	if (m_pacMan->IsPowerMode())
	{
		for (auto* enemy : m_enemyList)
		{
			if (enemy->GetCurrentState() != EnemyBase::ReturnPrisonMode)
			{
				//すべての敵をいじけモードにする。
				enemy->TweekEvent();
			}
		}
		//フラグはもとに戻す。
		m_pacMan->SetPowerMode(false);
		m_currentEatScore = 100;
	}
}

void SceneGame::ResetParams()
{
	//パラメーターをリセット。
	m_nextStageTimer = 0.0f;
	m_sceneStartDeltaTime = 0.0f;
	m_enemyChaseTimer = 0.0f;
	m_eatingWaitTimer = 0.0f;
	m_obstacleList.clear();
	m_enemyList.clear();
	m_isChaseMode = false;
	GameSound()->AllStop();
}

void SceneGame::WaitGameStartProcess()
{
	if ((m_sceneStartDeltaTime > CHARACTER_SPAWN_TIME) && m_pacMan == nullptr)
	{
		//opening
		//キャラクターを生成。
		m_pacMan = new PacMan(this);
		m_pacMan->Init();
		m_lifePoint--;
		//敵。
		CreateEnemy();
	}

	if (m_sceneStartDeltaTime < START_GAME_TIME)
	{
		//演出中。
		Vector2 readySpritePosition = { CENTER_POSITION.x - 64.0f, CENTER_POSITION.y + 40.0f };
		m_readySprite.Draw(readySpritePosition);

		for (auto* actor : m_actorList)
		{
			actor->SetExcutionFlag(Actor::EnExcutionFlagType_Draw);
		}
	}
	else
	{
		//演出終了。
		m_currentGameState = GameState_Running;

		for (auto* actor : m_actorList)
		{
			actor->SetExcutionFlag(Actor::EnExcutionFlagType_Active);
		}
	}
}

void SceneGame::GameRunningProcess()
{
	if (m_stage.GetRestCookieCount() == 0)
	{
		//次ラウンドへ行く演出。
		m_currentGameState = GameState_NextRound;
		return;
	}

	if (m_pacMan->IsDying())
	{
		//パックマン死亡演出。
		m_currentGameState = GameState_PlayerDead;
		return;
	}

	if (m_isCallDeadEventFlags)
	{
		//敵キャラを食べる演出。
		m_currentGameState = GameState_EatingWait;
		return;
	}

	//ステートは戻す。
	m_pacMan->SetExcutionFlag(Actor::EnExcutionFlagType_Active);
	for (auto* enemy : m_enemyList)
	{
		enemy->SetExcutionFlag(Actor::EnExcutionFlagType_Active);
	}

	EnemyEvent();
	FruitEvent();

	m_enemyChaseTimer += GameTime()->GetDeltaTime();
}

void SceneGame::WaitEatingProcess()
{
	if (!m_eatingWaitTimer)
	{
		//初めの処理。
		StopSoundMem(m_nextPlaySound);
		GameSound()->Play(m_eatingEnemySE);

		for (int i = 0; i < m_enemyList.size(); i++)
		{
			if (m_isCallDeadEventFlags == (1 << i))
			{
				m_enemyList[i]->SetExcutionFlag(Actor::EnExcutionFlagType_NotActive);
			}
			else
			{
				m_enemyList[i]->SetExcutionFlag(Actor::EnExcutionFlagType_Draw);
			}
		}
	}

	if (m_eatingWaitTimer > WAIT_EATING_TINE)
	{
		//食べ終わり。
		m_eatingWaitTimer = 0.0f;
		m_isCallDeadEventFlags = EnCalledDeadEvent_None;
		m_currentGameState = GameState_Running;
	}
	else
	{
		snprintf(m_scoreBuffer, sizeof(m_scoreBuffer) / sizeof(char), "%d", m_currentEatScore);
		m_scoreFont.SetDispStr(m_scoreBuffer);
		Vector2_Int DrawPos = EngineMath::ConvertToIntVec(m_pacMan->GetPosition());
		m_scoreFont.SetPosition(DrawPos);
		m_scoreFont.Draw(GetColor(0, 255, 255));
		//waitTimeが終了していない。
		m_pacMan->SetExcutionFlag(Actor::EnExcutionFlagType_NotActive);
		//エネミー捕食演出。
		m_eatingWaitTimer += GameTime()->GetDeltaTime();
	}
}

void SceneGame::PlayerDeadProcess()
{
	for (int i = 0; i < m_enemyList.size(); i++)
	{
		//敵キャラを消す。
		m_enemyList[i]->SetExcutionFlag(Actor::EnExcutionFlagType_Dead);
		m_enemyList.erase(m_enemyList.begin() + i);
	}

	if (m_pacMan->PlayDeadAnim())
	{
		//死亡アニメーションが終わったのでステージのリセット処理を行う。
		m_pacMan->SetExcutionFlag(Actor::EnExcutionFlagType_Dead);
		m_pacMan = nullptr;

		if (m_fruit != nullptr)
		{
			m_fruit->SetExcutionFlag(Actor::EnExcutionFlagType_Dead);
		}

		if (m_lifePoint == 0)
		{
			//残機0。シーンを切り替え。
			m_sceneManagerPtr->ChangeScene(SceneBase::EnSceneID_GameOver);
			return;
		}

		m_enemyChaseTimer = 0.0f;
		m_sceneStartDeltaTime = 0.0f;
		m_isChaseMode = false;
		m_currentGameState = GameState_WaitGameStart;
	}
}

void SceneGame::NextRoundProcess()
{
	GameSound()->AllStop();
	//パラメーターをリセット。
	delete m_pacMan;
	m_pacMan = nullptr;

	for (auto* enemy : m_enemyList)
	{
		enemy->SetExcutionFlag(Actor::EnExcutionFlagType_Dead);
	}

	m_nextStageTimer += GameTime()->GetDeltaTime();

	//ステージ点滅。
	m_stage.BlinkingStage();

	//ステージ点滅。
	if (m_nextStageTimer > BLINKING_TIME)
	{
		SetDrawBright(255, 255, 255);
		for (auto* actor : m_actorList)
		{
			actor->SetExcutionFlag(Actor::EnExcutionFlagType_Dead);
		}
	}

	if (m_nextStageTimer > NEXT_STAGE_TIME)
	{
		//ラウンド進行で使用するライフを追加しておく。
		m_lifePoint++;
		//パラメーターをリセット。
		ResetParams();
		//ステージを作成しなおす。
		m_stage.CreateStage();
		m_currentGameState = GameState_WaitGameStart;
	}
}

void SceneGame::CleanUp()
{
	for (auto it = m_actorList.begin(); it != m_actorList.end();)
	{
		Actor* actor = *it;
		it = m_actorList.erase(it);
		delete actor;
	}
}

void SceneGame::FruitEvent()
{

	if (m_fruit == nullptr)
	{
		//フルーツが出現していない。
		if ( ( m_stage.GetRestCookieCount() % FRUIT_APPEAR_REST_COOKIE_COUNT ) == 0)
		{
			//フルーツが出現。		
			m_fruit = new Fruit(this);
			m_fruit->SetPosition(m_apperFruitPosition);
			m_fruit->Init();
			m_fruitTimer = 0.0f;
		}
	}
	else
	{
		m_fruitTimer += GameTime()->GetDeltaTime();
		//出現済み。
		if (m_fruitTimer > FRUIT_APPEAR_DISAPPEAR_TIME)
		{
			auto it = std::find(m_actorList.begin(), m_actorList.end(), m_fruit);
			if (it != m_actorList.end())
			{
				//ほかの処理でまだ削除されたりしていないので削除。
				m_fruit->SetExcutionFlag(Actor::EnExcutionFlagType_Dead);
			}
			m_fruitTimer = 0.0f;
		}
	}

}
