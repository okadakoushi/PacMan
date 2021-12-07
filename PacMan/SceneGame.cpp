#include "stdafx.h"
#include "SceneGame.h"
#include "SceneBase.h"
#include "PacMan.h"
#include "Wall.h"
#include "Gate.h"
#include "WarpPoint.h"
#include "EnemyBase.h"
#include "Enemy_BLINKY.h"
#include "Enemy_Pinky.h"
#include "Enemy_INKY.h"
#include "Enemy_POKEY.h"
#include "Cookie.h"
#include "PowerCookie.h"
#include "Fruit.h"
#include "PlayerUI.h"
#include "StageLoader.h"

std::map<bool, std::pair<const float, EnemyBase::EnemyState>> SceneGame::m_isChaseToChageStateTimeAndMoveState
{
	//scatterモード時。
	{false, {6.0f, EnemyBase::ScatterMode} },
	//chaseモード時。
	{true, {20.0f, EnemyBase::ChaseMode} }
};

SceneGame::SceneGame(SceneManager* sceneManager) : SceneBase(sceneManager)
{
}

SceneGame::~SceneGame()
{
}

void SceneGame::Init()
{
	//スコア初期化。
	snprintf(m_scoreBuffer, sizeof(m_scoreBuffer) / sizeof(char), "%d", m_currentEatScore);
	m_scoreFont.Init(m_scoreBuffer, 10, 1);

	//GameOver用Sprite初期化。
	int drawhandle = LoadGraph("Assets/inStageMessage.bmp");
	m_drawHandle = DerivationGraph(0, 0, 128, 24, drawhandle);
	
	//UI
	m_playerUI = new PlayerUI(this);

	//ステージを生成。
	LoadStage();
	CreateStage();

	//サウンドロード。
	m_openingBGM = GameSound()->Load("Assets/sound/opening_song.ogg");
	m_standardModeSound = GameSound()->Load("Assets/sound/siren.ogg");
	m_eatingEnemySE = GameSound()->Load("Assets/sound/eatghost.ogg");
	m_powerModeSE = GameSound()->Load("Assets/sound/power_pellet.wav");

	GameSound()->Play(m_openingBGM);
}

void SceneGame::LoadStage()
{
	m_stageTable.resize(STAGE_TABLE_HEIGHT, std::vector<int>(STAGE_TABLE_WIDTH));
	m_stageLoader.Init(m_stageTable, STAGE_TABLE_WIDTH, STAGE_TABLE_HEIGHT, "Assets/pacMan_Stage_bg.csv", "Assets/pacMan_Stage_Item.csv", "Assets/pacMan_Stage_Obstacle.csv");
	int i = 0;
}

void SceneGame::CreateStage()
{
	//中央からブロック単位でどれくらい離れているか。
	int centerIndexX = STAGE_TABLE_WIDTH / 2;
	int centerIndexY = STAGE_TABLE_HEIGHT / 2;

	//ロードしてきたデータを変数として保存。
	for (int i = 0; i < STAGE_TABLE_WIDTH; i++)
	{
		for (int j = 0; j < STAGE_TABLE_HEIGHT; j++)
		{
			if (m_stageTable[i][j] == EnPlaceObjectType_None)
			{
				//設置しない。
				continue;
			}

			//中心からどれくらい離れているか。
			Vector2 CenterDist;
			CenterDist.x = j - centerIndexX;
			CenterDist.y = i - centerIndexY;
			//実際に置く場所。
			Vector2 PlaceObjectPos;
			PlaceObjectPos = CENTER_POSITION + Vector2(CenterDist.x * SPRITE_SIZE, CenterDist.y * SPRITE_SIZE);

			//Cookie.
			if (m_stageTable[i][j] == EnPlaceObjectType_Cookie)
			{
				Cookie* cookie = new Cookie(this);
				cookie->Init();
				cookie->SetPosition(PlaceObjectPos);
				m_restCookieCount++;
			}
			else if (m_stageTable[i][j] == EnPlaceObjectType_PowerCookie)
			{
				PowerCookie* pCookie = new PowerCookie(this);
				pCookie->Init();
				pCookie->SetPosition(PlaceObjectPos);
				m_restCookieCount++;
			}
			else if (m_stageTable[i][j] == EnPlaceObjectType_WarpPoint)
			{
				WarpPoint* warp = new WarpPoint(this);
				warp->Init();
				warp->SetPosition(PlaceObjectPos);
			}
			else if (m_stageTable[i][j] == EnPlaceObjectType_Gate)
			{
				//wallについては名称を変更する。
				Gate* gate = new Gate(this);
				gate->Init();
				gate->SetPosition(PlaceObjectPos);
				m_obstacleList.push_back(gate);
			}
			else
			{
				//ここまできたオブジェクトはすべて壁。
				Wall* wall = new Wall(this);
				wall->SetPosition(PlaceObjectPos);
				//ファイルパスをマップチップIDより割り出してくる。
				//str格納用。
				char str[64];
				//ObjectIDからファイルパスに変換する。LevelObject<行>-<列>.png
				sprintf(str, "Assets/LevelObjects/LevelObjects%d-%d.png", m_stageTable[i][j] % 15, (m_stageTable[i][j] / 15) % 3);
				wall->SetFilePath(str);
				m_obstacleList.push_back(wall);
				wall->Init();
			}
		}
	}

	//フルーツの位置。
	m_apperFruitPosition = { CENTER_POSITION.x - SPRITE_SIZE, CENTER_POSITION.y + SPRITE_SIZE * 1.5f };

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

	if (m_restCookieCount == 0)
	{
		NextRound();
		return;
	}

	if (m_sceneStartDeltaTime > CHARACTER_SPAWN_TIME && m_pacMan == nullptr)
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

	//UI.
	m_playerUI->Update(m_score, m_lifePoint);

	if (m_sceneStartDeltaTime < START_GAME_TIME)
	{
		m_readySprite.Draw({ CENTER_POSITION.x - 64 , CENTER_POSITION .y + SPRITE_SIZE * 2}, m_drawHandle);
		return;
	}
	else
	{
		//ReadySpriteを表示。
		m_pacMan->SetExcutionFlag(Actor::EnExcutionFlagType_Update);
		for (auto* enemy : m_actorList)
		{
			enemy->SetExcutionFlag(Actor::EnExcutionFlagType_Active);
		}
	}

	if (m_pacMan->IsDying())
	{
		//プレイヤー死亡中。
		PlayerDeadEvent();
		return;
	}

	if (m_isCallDeadEventFlags)
	{
		StopSoundMem(m_standardModeSound);
		GameSound()->Play(m_eatingEnemySE);

		//エネミー捕食演出。
		m_eatingWaitTimer += GameTime()->GetDeltaTime();

		if (m_eatingWaitTimer > WAIT_EATING_TINE)
		{
			m_pacMan->SetExcutionFlag(Actor::EnExcutionFlagType_Active);

			for (auto* enemy : m_enemyList)
			{
				enemy->SetExcutionFlag(Actor::EnExcutionFlagType_Active);
			}

			
			m_eatingWaitTimer = 0.0f;
			m_isCallDeadEventFlags = EnCalledDeadEvent_None;
		}
		else
		{
			snprintf(m_scoreBuffer, sizeof(m_scoreBuffer) / sizeof(char), "%d", m_currentEatScore);
			m_scoreFont.SetDispStr(m_scoreBuffer);
			m_scoreFont.Draw({ m_pacMan->GetPosition().x + 6, m_pacMan->GetPosition().y + 6 });
			//waitTimeが終了していない。
			m_pacMan->SetExcutionFlag(Actor::EnExcutionFlagType_NotActive);

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
		return;
	}

	EnemyEvent();
	FruitEvent();

	m_enemyChaseTimer += GameTime()->GetDeltaTime();


}

void SceneGame::PlayerDeadEvent()
{
	//プレイヤー死亡。敵、Playerの位置をリセット。
	for (int i = 0; i < m_enemyList.size(); i++)
	{
		m_enemyList[i]->SetExcutionFlag(Actor::EnExcutionFlagType_Dead);
		m_enemyList.erase(m_enemyList.begin() + i);
	}

	if (m_pacMan->PlayDeadAnim())
	{
		//パックマンを削除。
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
			delete this;
			return;
		}
		m_enemyChaseTimer = 0.0f;
		m_sceneStartDeltaTime = 0.0f;
		m_isChaseMode = false;
	}
}

void SceneGame::EnemyEvent()
{
	for (int i = 1; i < m_enemyList.size(); i++)
	{
		if (m_sceneStartDeltaTime >= ENEMY_WAIT_TIME[i - 1] && m_enemyList[i]->GetCurrentState() == EnemyBase::InPrisonMode)
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

	for (int i = 0; i < m_enemyList.size(); i++)
	{

		if (m_enemyList[i]->GetCurrentState() == EnemyBase::ChaseMode || m_enemyList[i]->GetCurrentState() == EnemyBase::ScatterMode)
		{
			//毎フレームEnemyをChase/Scatterモードに変更。
			EnemyBase::EnemyState frontFrameState = m_enemyList[i]->GetCurrentState();
			m_enemyList[i]->ChangeCurrentState(m_isChaseToChageStateTimeAndMoveState[m_isChaseMode].second);
			if (frontFrameState != m_enemyList[i]->GetCurrentState())
			{
				m_enemyList[i]->Turning();
			}
		}

		if (m_enemyList[i]->GetCurrentState() == EnemyBase::ReturnPrisonMode && !m_enemyList[i]->IsCallDeadEvent())
		{
			//敵が死亡状態。該当Enemyのフラグを上げる。
			m_isCallDeadEventFlags |= 1 << i;
			m_enemyList[i]->SetDeadEvent(true);
			//スコアも更新。
			m_currentEatScore *= 2;
			m_score += m_currentEatScore;
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
				enemy->SetFrontState(enemy->GetCurrentState());
				enemy->ChangeCurrentState(EnemyBase::TweekMode);
			}
		}
		//フラグはもとに戻す。
		m_pacMan->SetPowerMode(false);
		m_currentEatScore = 100;
	}
}

void SceneGame::NextRound()
{
	//パラメーターをリセット。
	delete m_pacMan;
	m_pacMan = nullptr;
	for (auto* enemy : m_enemyList)
	{
		enemy->SetExcutionFlag(Actor::EnExcutionFlagType_Dead);
	}
	m_enemyList.clear();

	//ラウンド進行で使用するライフを追加しておく。
	m_lifePoint++;

	m_nextStageTimer += GameTime()->GetDeltaTime();
	
	//点滅フレーム制御。
	if (++m_colorTriggerFrame > COLOR_TRIGGER_FRAME)
	{
		SetDrawBright(255 * m_colorTriggerFlag, 255 * m_colorTriggerFlag, 255 * m_colorTriggerFlag);
		m_colorTriggerFlag ^= true;
		m_colorTriggerFrame = 0;
	}

	//ステージ点滅。
	if (m_nextStageTimer > BLINKING_TIME)
	{
		SetDrawBright(255, 255, 255);
		for (auto* actor : m_actorList)
		{
			actor->SetExcutionFlag(Actor::EnExcutionFlagType_Dead);
		}
	}
	
	//パラメーターをリセット。
	if(m_nextStageTimer > NEXT_STAGE_TIME)
	{
		m_nextStageTimer = 0;
		m_sceneStartDeltaTime = 0.0f;
		m_enemyChaseTimer = 0.0f;
		m_eatingWaitTimer = 0.0f;
		CreateStage();
	}


}

void SceneGame::FruitEvent()
{

	if (m_fruit == nullptr)
	{
		//フルーツが出現していない。
		if (m_restCookieCount == 84 || m_restCookieCount == 167)
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

