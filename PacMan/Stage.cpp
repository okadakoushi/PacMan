#include "stdafx.h"
#include "Stage.h"
#include "StageLoader.h"
#include "Cookie.h"
#include "PowerCookie.h"
#include "Wall.h"
#include "Gate.h"
#include "WarpPoint.h"
#include "SceneGame.h"

static const char* StageBackGroundCSV_FilePath		= "Assets/StageData/pacMan_Stage_bg.csv";
static const char* StageItemCSV_FilePath			= "Assets/StageData/pacMan_Stage_Item.csv";
static const char* StageObstacleCSV_FilePath		= "Assets/StageData/pacMan_Stage_Obstacle.csv";

Stage::Stage(SceneGame* sceneGame)
{
	m_sceneGame = sceneGame;
}

void Stage::Init()
{
	//ステージデーターをロード。
	m_stageTable.resize(STAGE_TABLE_HEIGHT, std::vector<int>(STAGE_TABLE_WIDTH));
	m_stageLoader.Init(m_stageTable, STAGE_TABLE_WIDTH, STAGE_TABLE_HEIGHT, StageBackGroundCSV_FilePath, StageItemCSV_FilePath, StageObstacleCSV_FilePath);

	//読み込んできたデーターを参照してステージを生成する。
	CreateStage();
}

void Stage::BlinkingStage()
{
	//点滅フレーム制御。
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
			Vector2_Int CenterDist;
			CenterDist.x = j - centerIndexX;
			CenterDist.y = i - centerIndexY;
			CenterDist *= SPRITE_SIZE;
			//実際に置く場所。
			Vector2 PlaceObjectPos;
			PlaceObjectPos = CENTER_POSITION + EngineMath::CovertToFloatVec(CenterDist);

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
				pCookie->SetExcutionFlag(Actor::EnExcutionFlagType_Draw);
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
				//wallについては名称を変更する。
				Gate* gate = new Gate(m_sceneGame);
				gate->Init();
				gate->SetPosition(PlaceObjectPos);
				m_sceneGame->AddObstacle(gate);
			}
			else
			{
				//ここまできたオブジェクトはすべて壁。
				Wall* wall = new Wall(m_sceneGame);
				wall->SetPosition(PlaceObjectPos);
				//ファイルパスをマップチップIDより割り出してくる。
				//str格納用。
				char str[64];
				//ObjectIDからファイルパスに変換する。LevelObject<行>-<列>.png
				sprintf(str, "Assets/LevelObjects/LevelObjects%d-%d.png", m_stageTable[i][j] % 15, (m_stageTable[i][j] / 15) % 3);
				wall->SetFilePath(str);
				m_sceneGame->AddObstacle(wall);
				wall->Init();
			}
		}
	}
}
