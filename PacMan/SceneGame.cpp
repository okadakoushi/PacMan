#include "stdafx.h"
#include "SceneGame.h"
#include "SceneBase.h"
#include "PacMan.h"
#include "EnemyBase.h"
#include "Enemy_BLINKY.h"
#include "Enemy_Pinky.h"
#include "Enemy_INKY.h"
#include "Enemy_POKEY.h"
#include "Fruit.h"
#include "PlayerUI.h"
#include "Stage.h"

static const char* Opening_fp		= "Assets/sound/opening_song.ogg";
static const char* ExtraSE_fp		= "Assets/sound/extend.wav";
static const char* SirenSE_fp		= "Assets/sound/siren_1.wav";
static const char* TweekModeSE_fp	= "Assets/sound/power_pellet.wav";
static const char* ReturnModeSE_fp	= "Assets/sound/retreating.wav";
static const char* EatingSE_fp		= "Assets/sound/eatghost.ogg";

std::map<bool, std::pair<const float, EnemyBase::EnemyState>> SceneGame::m_isChaseToChageStateTimeAndMoveState
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
	snprintf(m_scoreBuffer, sizeof(m_scoreBuffer) / sizeof(char), "%d", m_currentEatScore);
	m_scoreFont.Init(m_scoreBuffer, 13, 2);

	//GameOver用Sprite初期化。
	int drawhandle = LoadGraph("Assets/inStageMessage.bmp");
	int GameOverHanlde = DerivationGraph(0, 0, 128, 24, drawhandle);
	m_readySprite.Init(GameOverHanlde);

	//サウンドロード。
	m_enemySEList[GameBGMType_Normal] = GameSound()->Load(SirenSE_fp);
	ChangeVolumeSoundMem(255, m_enemySEList[GameBGMType_Normal]);
	m_enemySEList[GameBGMType_PowerMode] = GameSound()->Load(TweekModeSE_fp);
	m_enemySEList[GameBGMType_Return] = GameSound()->Load(ReturnModeSE_fp);
	m_openingBGM = GameSound()->Load(Opening_fp);
	m_eatingEnemySE = GameSound()->Load(EatingSE_fp);
	m_extraSE = GameSound()->Load(ExtraSE_fp);

	//フルーツの位置。
	m_apperFruitPosition = { CENTER_POSITION.x - 24, CENTER_POSITION.y + 24 };

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
		enemy->SetExcutionFlag(Actor::EnExcutionFlagType_Draw);
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
		if ( (m_sceneStartDeltaTime > CHARACTER_SPAWN_TIME) && m_pacMan == nullptr)
		{
			//opening
			//キャラクターを生成。
			m_pacMan = new PacMan(this);
			m_pacMan->Init();
			m_pacMan->SetExcutionFlag(Actor::EnExcutionFlagType_Draw);
			m_lifePoint--;
			//敵。
			CreateEnemy();
		}

		if (m_sceneStartDeltaTime < START_GAME_TIME)
		{
			//演出中。
			m_readySprite.Draw({ CENTER_POSITION.x - 64, CENTER_POSITION.y + SPRITE_SIZE * 2});
		}
		else
		{
			//演出終了。
			m_currentGameState = GameState_Running;
		}
		break;

	case SceneGame::GameState_Running:
		
		//ゲーム実行中//
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
		m_pacMan->SetExcutionFlag(Actor::EnExcutionFlagType_Update);
		for (auto* enemy : m_actorList)
		{
			enemy->SetExcutionFlag(Actor::EnExcutionFlagType_Active);
		}

		EnemyEvent();
		FruitEvent();

		m_enemyChaseTimer += GameTime()->GetDeltaTime();
		break;

	case SceneGame::GameState_EatingWait:

		//食べ待ち//
		if (!m_eatingWaitTimer)
		{
			//初めの処理。
			StopSoundMem(m_nextPlaySound);
			GameSound()->Play(m_eatingEnemySE);

			for (int i = 0; i < m_enemyList.size(); i++)
			{
				if (m_isCallDeadEventFlags == 1 << i)
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
			m_scoreFont.Draw({ m_pacMan->GetPosition().x, m_pacMan->GetPosition().y }, GetColor(0, 255, 255));
			//waitTimeが終了していない。
			m_pacMan->SetExcutionFlag(Actor::EnExcutionFlagType_NotActive);
			//エネミー捕食演出。
			m_eatingWaitTimer += GameTime()->GetDeltaTime();
		}
		break;

	case SceneGame::GameState_PlayerDead:

		//プレイヤー死亡演出中。
		for (int i = 0; i < m_enemyList.size(); i++)
		{
			//敵キャラを消す。
			m_enemyList[i]->SetExcutionFlag(Actor::EnExcutionFlagType_Dead);
			m_enemyList.erase(m_enemyList.begin() + i);
		}

		if (m_pacMan->PlayDeadAnim())
		{
			//死亡アニメーションが終わったのでステージのリセット処理を行う。
			delete m_pacMan;
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
		break;
	
	case SceneGame::GameState_NextRound:
		
		//次のラウンドに進む。
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
		m_isChaseMode ^= true;
		m_enemyChaseTimer = 0.0f;
	}

	int TweekEnemyCount = 0;

	for (int i = 0; i < m_enemyList.size(); i++)
	{

		if ( (m_enemyList[i]->GetCurrentState() == EnemyBase::ChaseMode) || (m_enemyList[i]->GetCurrentState() == EnemyBase::ScatterMode) )
		{
			//毎フレームEnemyをChase/Scatterモードに変更。
			EnemyBase::EnemyState frontFrameState = m_enemyList[i]->GetCurrentState();
			m_enemyList[i]->ChangeCurrentState(m_isChaseToChageStateTimeAndMoveState[m_isChaseMode].second);
			if (frontFrameState != m_enemyList[i]->GetCurrentState())
			{
				m_enemyList[i]->Turning();
			}
		}

		if ( (m_enemyList[i]->GetCurrentState() == EnemyBase::ReturnPrisonMode) && !m_enemyList[i]->IsCallDeadEvent())
		{
			//敵が死亡状態。該当Enemyのフラグを上げる。
			m_isCallDeadEventFlags |= 1 << i;
			m_enemyList[i]->SetDeadEvent(true);
			//スコアも更新。
			m_currentEatScore *= 2;
			m_score += m_currentEatScore;

		}
	}

	//流す曲の決定。
	{
		//通常状態のゴーストの数。
		int normalEnemyCount = m_enemyList.size();
		
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
	m_nextStageTimer = 0;
	m_sceneStartDeltaTime = 0.0f;
	m_enemyChaseTimer = 0.0f;
	m_eatingWaitTimer = 0.0f;
	m_obstacleList.clear();
	m_enemyList.clear();
	m_isChaseMode = false;
	GameSound()->AllStop();
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
		if (m_stage.GetRestCookieCount() == 84 || m_stage.GetRestCookieCount() == 167)
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
			else
			{
				//すでに削除されていた。
				m_fruit = nullptr;
			}
			m_fruitTimer = 0.0f;
		}
	}

}
