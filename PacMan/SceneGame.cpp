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
	//scatter���[�h���B
	{false, {6.0f, EnemyBase::ScatterMode} },
	//chase���[�h���B
	{true, {20.0f, EnemyBase::ChaseMode} }
};

SceneGame::SceneGame(SceneManager* sceneManager) : SceneBase(sceneManager)
{
}

void SceneGame::Init()
{
	//�X�R�A�������B
	snprintf(m_scoreBuffer, sizeof(m_scoreBuffer) / sizeof(char), "%d", m_currentEatScore);
	m_scoreFont.Init(m_scoreBuffer, 10, 1);

	//GameOver�pSprite�������B
	int drawhandle = LoadGraph("Assets/inStageMessage.bmp");
	m_drawHandle = DerivationGraph(0, 0, 128, 24, drawhandle);
	
	//UI
	m_playerUI = new PlayerUI(this);

	//�X�e�[�W�𐶐��B
	LoadStage();
	CreateStage();	
}

void SceneGame::LoadStage()
{
	m_stageTable.resize(STAGE_TABLE_HEIGHT, std::vector<int>(STAGE_TABLE_WIDTH));
	m_stageLoader.Init(m_stageTable, STAGE_TABLE_WIDTH, STAGE_TABLE_HEIGHT, "Assets/pacMan_Stage_bg.csv", "Assets/pacMan_Stage_Item.csv", "Assets/pacMan_Stage_Obstacle.csv");
	int i = 0;
}

void SceneGame::CreateStage()
{
	int centerIndexX = STAGE_TABLE_WIDTH / 2;
	int centerIndexY = STAGE_TABLE_HEIGHT / 2;

	//���[�h���Ă����f�[�^��ϐ��Ƃ��ĕۑ��B
	for (int i = 0; i < STAGE_TABLE_WIDTH; i++)
	{
		for (int j = 0; j < STAGE_TABLE_HEIGHT; j++)
		{
			if (m_stageTable[i][j] == EnPlaceObjectType_None)
			{
				//�ݒu���Ȃ��B
				continue;
			}

			//���S����ǂꂭ�炢����Ă��邩�B
			Vector2 CenterDist;
			CenterDist.x = j - centerIndexX;
			CenterDist.y = i - centerIndexY;
			//���ۂɒu���ꏊ�B
			Vector2 PlaceObjectPos;
			PlaceObjectPos = CENTER_POSITION + Vector2(CenterDist.x * SPRITE_SIZE, CenterDist.y * SPRITE_SIZE);

			//Cookie.
			if (m_stageTable[i][j] == EnPlaceObjectType_Cookie)
			{
				Cookie* cookie = new Cookie(this);
				cookie->Init();
				cookie->SetPosition(PlaceObjectPos);
				m_leftCookieCount++;
				continue;
			}

			if (m_stageTable[i][j] == EnPlaceObjectType_PowerCookie)
			{
				PowerCookie* pCookie = new PowerCookie(this);
				pCookie->Init();
				pCookie->SetPosition(PlaceObjectPos);
				m_leftCookieCount++;
				continue;
			}

			if (m_stageTable[i][j] == EnPlaceObjectType_WarpPoint)
			{
				WarpPoint* warp = new WarpPoint(this);
				warp->Init();
				warp->SetPosition(PlaceObjectPos);
				continue;
			}

			if (m_stageTable[i][j] == EnPlaceObjectType_Gate)
			{
				//wall�ɂ��Ă͖��̂�ύX����B
				Gate* gate = new Gate(this);
				gate->Init();
				gate->SetPosition(PlaceObjectPos);
				m_obstacleList.push_back(gate);
				continue;
			}



			//�����܂ł����I�u�W�F�N�g�͂��ׂĕǁB
			Wall* wall = new Wall(this);
			wall->SetPosition(PlaceObjectPos);
			//�t�@�C���p�X���}�b�v�`�b�vID��芄��o���Ă���B
			//str�i�[�p�B
			char str[64];
			//ObjectID����t�@�C���p�X�ɕϊ�����BLevelObject<�s>-<��>.png
			sprintf(str, "Assets/LevelObjects/LevelObjects%d-%d.png", m_stageTable[i][j] % 15, (m_stageTable[i][j] / 15) % 3);
			wall->SetFilePath(str);
			m_obstacleList.push_back(wall);
			wall->Init();

		}
	}

	//�t���[�c�̈ʒu�B
	m_apperFruitPosition = { CENTER_POSITION.x - SPRITE_SIZE, CENTER_POSITION.y + SPRITE_SIZE * 1.5f };

}

void SceneGame::CreateEnemy()
{
	//Blinky.
	Enemy_BLINKY* enemy_blinky = new Enemy_BLINKY(this, m_pacMan, BLINKY_START_POS);
	enemy_blinky->Init();
	enemy_blinky->ChangeCurrentState(EnemyBase::ScatterMode);
	m_enemyList.push_back(enemy_blinky);

	//Pinky.
	Enemy_Pinky* enemy_pinky = new Enemy_Pinky(this, m_pacMan, PINKY_START_POS);
	enemy_pinky->Init();
	enemy_pinky->ChangeCurrentState(EnemyBase::InPrisonMode);
	m_enemyList.push_back(enemy_pinky);

	//INKY.
	Enemy_INKY* enemy_inky = new Enemy_INKY(this, m_pacMan, enemy_blinky, INKY_START_POS);
	enemy_inky->Init();
	enemy_inky->ChangeCurrentState(EnemyBase::InPrisonMode);
	m_enemyList.push_back(enemy_inky);

	//Clyde.
	Enemy_POKEY* enemy_pokey = new Enemy_POKEY(this, m_pacMan, CLYDE_START_POS);
	enemy_pokey->Init();
	enemy_pokey->ChangeCurrentState(EnemyBase::InPrisonMode);
	m_enemyList.push_back(enemy_pokey);

	for (auto* enemy : m_enemyList)
	{
		enemy->SetExcutionFlag(Actor::EnExcutionFlagType_Draw);
	}

}

void SceneGame::Update()
{
	//����Update�Ăяo���B
	__super::Update();

	//UI.
	m_playerUI->Update(m_score, m_lifePoint);

	m_sceneStartDeltaTime += GameTime()->GetDeltaTime();

	if (m_sceneStartDeltaTime > CHARACTER_SPAWN_TIME && m_pacMan == nullptr)
	{
		//�L�����N�^�[�𐶐��B
		m_pacMan = new PacMan(this);
		m_pacMan->Init();
		m_pacMan->SetExcutionFlag(Actor::EnExcutionFlagType_Draw);
		m_lifePoint--;
		//�G�B
		CreateEnemy();
	}

	if (m_sceneStartDeltaTime < START_GAME_TIME)
	{
		m_readySprite.Draw({ CENTER_POSITION.x - 64 , CENTER_POSITION .y + SPRITE_SIZE * 2}, m_drawHandle);
		return;
	}
	else
	{
		//ReadySprite��\���B
		m_pacMan->SetExcutionFlag(Actor::EnExcutionFlagType_Update);
		for (auto* enemy : m_actorList)
		{
			enemy->SetExcutionFlag(Actor::EnExcutionFlagType_Active);
		}
	}

	if (m_pacMan->IsDying())
	{
		//�v���C���[���S���B
		PlayerDeadEvent();
		return;
	}

	if (m_isCallDeadEventFlags)
	{
		//�G�l�~�[�ߐH���o�B
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
			//waitTime���I�����Ă��Ȃ��B
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

	if (m_leftCookieCount == 0)
	{
		m_sceneManagerPtr->ChangeScene(SceneID::EnSceneID_Game);
		NextRound();
	}
}

void SceneGame::PlayerDeadEvent()
{
	//�v���C���[���S�B�G�APlayer�̈ʒu�����Z�b�g�B
	for (int i = 0; i < m_enemyList.size(); i++)
	{
		m_enemyList[i]->SetExcutionFlag(Actor::EnExcutionFlagType_Dead);
		m_enemyList.erase(m_enemyList.begin() + i);
	}
	

	if (m_pacMan->PlayDeadAnim())
	{
		//�p�b�N�}�����폜�B
		delete m_pacMan;
		m_pacMan = nullptr;

		if (m_fruit != nullptr)
		{
			m_fruit->SetExcutionFlag(Actor::EnExcutionFlagType_Dead);
		}

		if (m_lifePoint == 0)
		{
			//�c�@0�B�V�[����؂�ւ��B
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
	//waitTime���I�����Ă��邽�߁A�S������o��B
	//bitTable(0000���S������ł�Enemy��1) : enemy[]�B
	if (m_sceneStartDeltaTime >= PINKY_WAIT_TIME && m_enemyList[1]->GetCurrentState() == EnemyBase::InPrisonMode)
	{
		m_enemyList[1]->ChangeCurrentState(EnemyBase::GetOutPrisonMode);
	}
	else if (m_sceneStartDeltaTime >= INKY_WAIT_TIME && m_enemyList[2]->GetCurrentState() == EnemyBase::InPrisonMode)
	{
		m_enemyList[2]->ChangeCurrentState(EnemyBase::GetOutPrisonMode);
	}
	else if (m_sceneStartDeltaTime >= CLYDE_WAIT_TIME && m_enemyList[3]->GetCurrentState() == EnemyBase::InPrisonMode)
	{
		m_enemyList[3]->ChangeCurrentState(EnemyBase::GetOutPrisonMode);
	}

	//�^�C�}�[�ɉ����āAChase/Scatter��؂�ւ��B
	if (m_enemyChaseTimer > m_isChaseToChageStateTimeAndMoveState[m_isChaseMode].first)
	{
		//�t���O�؂�ւ��B
		m_isChaseMode ^= true;
		m_enemyChaseTimer = 0.0f;
	}

	for (int i = 0; i < m_enemyList.size(); i++)
	{

		if (m_enemyList[i]->GetCurrentState() == EnemyBase::ChaseMode || m_enemyList[i]->GetCurrentState() == EnemyBase::ScatterMode)
		{
			//���t���[��Enemy��Chase/Scatter���[�h�ɕύX�B
			m_enemyList[i]->ChangeCurrentState(m_isChaseToChageStateTimeAndMoveState[m_isChaseMode].second);
		}

		if (m_enemyList[i]->GetCurrentState() == EnemyBase::ReturnPrisonMode && !m_enemyList[i]->IsCallDeadEvent())
		{
			//�G�����S��ԁB�Y��Enemy�̃t���O���グ��B
			m_isCallDeadEventFlags |= 1 << i;
			m_enemyList[i]->SetDeadEvent(true);
			//�X�R�A���X�V�B
			m_currentEatScore *= 2;
			m_score +=m_currentEatScore;
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
				enemy->ChangeCurrentState(EnemyBase::TweekMode);
			}
		}
		//�t���O�͂��Ƃɖ߂��B
		m_pacMan->SetPowerMode(false);
		m_currentEatScore = 100;
	}

	
}

void SceneGame::NextRound()
{
	delete this;
}

void SceneGame::FruitEvent()
{

	if (m_fruit == nullptr)
	{
		//�t���[�c���o�����Ă��Ȃ��B
		if (m_leftCookieCount == 84 || m_leftCookieCount == 167)
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
			else
			{
				//���łɍ폜����Ă����B
				m_fruit = nullptr;
			}
			m_fruitTimer = 0.0f;
		}
	}

}

