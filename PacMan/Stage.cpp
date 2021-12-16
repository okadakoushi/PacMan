#include "stdafx.h"
#include "Stage.h"
#include "StageLoader.h"
#include "Cookie.h"
#include "PowerCookie.h"
#include "Wall.h"
#include "Gate.h"
#include "WarpPoint.h"
#include "SceneGame.h"

<<<<<<< HEAD
<<<<<<< HEAD
static const char* StageBackGroundCSV_FilePath		= "Assets/StageData/pacMan_Stage_bg.csv";
static const char* StageItemCSV_FilePath			= "Assets/StageData/pacMan_Stage_Item.csv";
static const char* StageObstacleCSV_FilePath		= "Assets/StageData/pacMan_Stage_Obstacle.csv";
=======
static const char* StageBackGroundCSV_fp	= "Assets/pacMan_Stage_bg.csv";
static const char* StageItemCSV_fp			= "Assets/pacMan_Stage_Item.csv";
static const char* StageObstacleCSV_fp		= "Assets/pacMan_Stage_Obstacle.csv";
>>>>>>> parent of d0d8c4a (PACMAN)
=======
static const char* StageBackGroundCSV_fp	= "Assets/pacMan_Stage_bg.csv";
static const char* StageItemCSV_fp			= "Assets/pacMan_Stage_Item.csv";
static const char* StageObstacleCSV_fp		= "Assets/pacMan_Stage_Obstacle.csv";
>>>>>>> parent of d0d8c4a (PACMAN)

Stage::Stage(SceneGame* sceneGame)
{
	m_sceneGame = sceneGame;
}

void Stage::Init()
{
	//�X�e�[�W�f�[�^�[�����[�h�B
	m_stageTable.resize(STAGE_TABLE_HEIGHT, std::vector<int>(STAGE_TABLE_WIDTH));
	m_stageLoader.Init(m_stageTable, STAGE_TABLE_WIDTH, STAGE_TABLE_HEIGHT, StageBackGroundCSV_fp, StageItemCSV_fp, StageObstacleCSV_fp);

	//�ǂݍ���ł����f�[�^�[���Q�Ƃ��ăX�e�[�W�𐶐�����B
	CreateStage();
}

void Stage::BlinkingStage()
{
	//�_�Ńt���[������B
	if (++m_colorTriggerFrame > COLOR_TRIGGER_FRAME)
	{
		int fadeColor = 255 * m_colorTriggerFlag;
		SetDrawBright(fadeColor, fadeColor, fadeColor);
		m_colorTriggerFlag ^= true;
		m_colorTriggerFrame = 0;
	}
}

void Stage::CreateStage()
{
	//��������u���b�N�P�ʂłǂꂭ�炢����Ă��邩�B
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
				Cookie* cookie = new Cookie(m_sceneGame);
				cookie->Init();
				cookie->SetPosition(PlaceObjectPos);
				m_restCookieCount++;
			}
			else if (m_stageTable[i][j] == EnPlaceObjectType_PowerCookie)
			{
				PowerCookie* pCookie = new PowerCookie(m_sceneGame);
				pCookie->Init();
				pCookie->SetPosition(PlaceObjectPos);
				m_restCookieCount++;
			}
			else if (m_stageTable[i][j] == EnPlaceObjectType_WarpPoint)
			{
				WarpPoint* warp = new WarpPoint(m_sceneGame);
				warp->Init();
				warp->SetPosition(PlaceObjectPos);
			}
			else if (m_stageTable[i][j] == EnPlaceObjectType_Gate)
			{
				//wall�ɂ��Ă͖��̂�ύX����B
				Gate* gate = new Gate(m_sceneGame);
				gate->Init();
				gate->SetPosition(PlaceObjectPos);
				m_sceneGame->AddObstacle(gate);
			}
			else
			{
				//�����܂ł����I�u�W�F�N�g�͂��ׂĕǁB
				Wall* wall = new Wall(m_sceneGame);
				wall->SetPosition(PlaceObjectPos);
				//�t�@�C���p�X���}�b�v�`�b�vID��芄��o���Ă���B
				//str�i�[�p�B
				char str[64];
				//ObjectID����t�@�C���p�X�ɕϊ�����BLevelObject<�s>-<��>.png
				sprintf(str, "Assets/LevelObjects/LevelObjects%d-%d.png", m_stageTable[i][j] % 15, (m_stageTable[i][j] / 15) % 3);
				wall->SetFilePath(str);
				m_sceneGame->AddObstacle(wall);
				wall->Init();
			}
		}
	}
}
