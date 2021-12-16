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
	//scatter���[�h���B
	{false, {6.0f, EnemyBase::ScatterMode} },
	//chase���[�h���B
	{true, {20.0f, EnemyBase::ChaseMode} }
};

std::map<int, int> SceneGame::m_restCookieCountToFrequency
{
	//�c��N�b�L�[�A���g���B
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
	
	//�X�R�A�������B
	int size = sizeof(m_scoreBuffer) / sizeof(char);
	snprintf(m_scoreBuffer, size, "%d", m_currentEatScore);
	m_scoreFont.Init(m_scoreBuffer, 13, 2);

	//GameOver�pSprite�������B
	int drawhandle = LoadGraph(StageMassage_FilePath);
	int GameOverHanlde = DerivationGraph(0, 0, 128, 24, drawhandle);
	m_readySprite.Init(GameOverHanlde);

	//�T�E���h���[�h�B
	m_enemySEList[GameBGMType_Normal] = GameSound()->Load(SirenSE_FilePath);
	ChangeVolumeSoundMem(255, m_enemySEList[GameBGMType_Normal]);
	m_enemySEList[GameBGMType_PowerMode] = GameSound()->Load(TweekModeSE_FilePath);
	m_enemySEList[GameBGMType_Return] = GameSound()->Load(ReturnModeSE_FilePath);
	m_openingBGM = GameSound()->Load(Opening_FilePath);
	m_eatingEnemySE = GameSound()->Load(EatingSE_FilePath);
	m_extraSE = GameSound()->Load(ExtraSE_FilePath);

	//�t���[�c�̈ʒu�B
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
	//�u�����L�[�͍ŏ�����O�B
	enemy_blinky->ChangeCurrentState(EnemyBase::ScatterMode);

}

void SceneGame::Update()
{
	//����Update�Ăяo���B
	__super::Update();

	m_sceneStartDeltaTime += GameTime()->GetDeltaTime();
	
	if (m_currentGameState != GameState_NextRound)
	{
		//�����E���h�J�ڒ���UI�\�����s��Ȃ��B
		m_playerUI->Update(m_score, m_lifePoint);
	}

	switch (m_currentGameState)
	{
	case SceneGame::GameState_WaitGameStart:
		//�Q�[���X�^�[�g�҂�//
		WaitGameStartProcess();
		break;

	case SceneGame::GameState_Running:
		//�Q�[�����s��//
		GameRunningProcess();
		break;

	case SceneGame::GameState_EatingWait:
		//�G��H�ׂ鉉�o��//
		WaitEatingProcess();
		break;

	case SceneGame::GameState_PlayerDead:
		//�v���C���[���S���o//
		PlayerDeadProcess();
		break;
	
	case SceneGame::GameState_NextRound:
		//�����E���h�ɐi��//
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

	//�^�C�}�[�ɉ����āAChase/Scatter��؂�ւ��B
	if (m_enemyChaseTimer > m_isChaseToChageStateTimeAndMoveState[m_isChaseMode].first)
	{
		//�t���O�؂�ւ��B
		m_isChaseMode = !m_isChaseMode;
		m_enemyChaseTimer = 0.0f;
	}

	int TweekEnemyCount = 0;

	for (int i = 0; i < m_enemyList.size(); i++)
	{
		EnemyBase::ENEMY_STATE enemyCurrentState = m_enemyList[i]->GetCurrentState();

		if ( (enemyCurrentState == EnemyBase::ChaseMode) || (enemyCurrentState == EnemyBase::ScatterMode) )
		{
			//���t���[��Enemy��Chase/Scatter���[�h�ɕύX�B
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
			//�G�����S��ԁB�Y��Enemy�̃t���O���グ��B
			m_isCallDeadEventFlags |= (1 << i);
			m_enemyList[i]->SetDeadEvent(true);
			//�X�R�A���X�V�B
			m_currentEatScore *= 2;
			AddScore(m_currentEatScore);
		}
	}

	//�����Ȃ̌���B
	{
		//�ʏ��Ԃ̃S�[�X�g�̐��B
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
			//�����Ԃ̓G�͂��Ȃ��̂Œʏ�Đ��B
			m_nextPlaySound = GameBGMType_Normal;
			//���g�����c��̃N�b�L�[���ɉ����ĕύX����B
			int speed = m_restCookieCountToFrequency[m_stage.GetRestCookieCount()];
			if (speed)
			{
				SetFrequencySoundMem(speed, m_enemySEList[m_nextPlaySound]);
			}
		}
	}

	//����Ȃ��Ȃ͎~�߂�/�Ȃ𗬂��B
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

	//�p�b�N�}�����p���[�N�b�L�[������Ă��邩�̊Ď��B
	if (m_pacMan->IsPowerMode())
	{
		for (auto* enemy : m_enemyList)
		{
			if (enemy->GetCurrentState() != EnemyBase::ReturnPrisonMode)
			{
				//���ׂĂ̓G�����������[�h�ɂ���B
				enemy->TweekEvent();
			}
		}
		//�t���O�͂��Ƃɖ߂��B
		m_pacMan->SetPowerMode(false);
		m_currentEatScore = 100;
	}
}

void SceneGame::ResetParams()
{
	//�p�����[�^�[�����Z�b�g�B
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
		//�L�����N�^�[�𐶐��B
		m_pacMan = new PacMan(this);
		m_pacMan->Init();
		m_lifePoint--;
		//�G�B
		CreateEnemy();
	}

	if (m_sceneStartDeltaTime < START_GAME_TIME)
	{
		//���o���B
		Vector2 readySpritePosition = { CENTER_POSITION.x - 64.0f, CENTER_POSITION.y + 40.0f };
		m_readySprite.Draw(readySpritePosition);

		for (auto* actor : m_actorList)
		{
			actor->SetExcutionFlag(Actor::EnExcutionFlagType_Draw);
		}
	}
	else
	{
		//���o�I���B
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
		//�����E���h�֍s�����o�B
		m_currentGameState = GameState_NextRound;
		return;
	}

	if (m_pacMan->IsDying())
	{
		//�p�b�N�}�����S���o�B
		m_currentGameState = GameState_PlayerDead;
		return;
	}

	if (m_isCallDeadEventFlags)
	{
		//�G�L������H�ׂ鉉�o�B
		m_currentGameState = GameState_EatingWait;
		return;
	}

	//�X�e�[�g�͖߂��B
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
		//���߂̏����B
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
		//�H�׏I���B
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
		//waitTime���I�����Ă��Ȃ��B
		m_pacMan->SetExcutionFlag(Actor::EnExcutionFlagType_NotActive);
		//�G�l�~�[�ߐH���o�B
		m_eatingWaitTimer += GameTime()->GetDeltaTime();
	}
}

void SceneGame::PlayerDeadProcess()
{
	for (int i = 0; i < m_enemyList.size(); i++)
	{
		//�G�L�����������B
		m_enemyList[i]->SetExcutionFlag(Actor::EnExcutionFlagType_Dead);
		m_enemyList.erase(m_enemyList.begin() + i);
	}

	if (m_pacMan->PlayDeadAnim())
	{
		//���S�A�j���[�V�������I������̂ŃX�e�[�W�̃��Z�b�g�������s���B
		m_pacMan->SetExcutionFlag(Actor::EnExcutionFlagType_Dead);
		m_pacMan = nullptr;

		if (m_fruit != nullptr)
		{
			m_fruit->SetExcutionFlag(Actor::EnExcutionFlagType_Dead);
		}

		if (m_lifePoint == 0)
		{
			//�c�@0�B�V�[����؂�ւ��B
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
	//�p�����[�^�[�����Z�b�g�B
	delete m_pacMan;
	m_pacMan = nullptr;

	for (auto* enemy : m_enemyList)
	{
		enemy->SetExcutionFlag(Actor::EnExcutionFlagType_Dead);
	}

	m_nextStageTimer += GameTime()->GetDeltaTime();

	//�X�e�[�W�_�ŁB
	m_stage.BlinkingStage();

	//�X�e�[�W�_�ŁB
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
		//���E���h�i�s�Ŏg�p���郉�C�t��ǉ����Ă����B
		m_lifePoint++;
		//�p�����[�^�[�����Z�b�g�B
		ResetParams();
		//�X�e�[�W���쐬���Ȃ����B
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
		//�t���[�c���o�����Ă��Ȃ��B
		if ( ( m_stage.GetRestCookieCount() % FRUIT_APPEAR_REST_COOKIE_COUNT ) == 0)
		{
			//�t���[�c���o���B		
			m_fruit = new Fruit(this);
			m_fruit->SetPosition(m_apperFruitPosition);
			m_fruit->Init();
			m_fruitTimer = 0.0f;
		}
	}
	else
	{
		m_fruitTimer += GameTime()->GetDeltaTime();
		//�o���ς݁B
		if (m_fruitTimer > FRUIT_APPEAR_DISAPPEAR_TIME)
		{
			auto it = std::find(m_actorList.begin(), m_actorList.end(), m_fruit);
			if (it != m_actorList.end())
			{
				//�ق��̏����ł܂��폜���ꂽ�肵�Ă��Ȃ��̂ō폜�B
				m_fruit->SetExcutionFlag(Actor::EnExcutionFlagType_Dead);
			}
			m_fruitTimer = 0.0f;
		}
	}

}
