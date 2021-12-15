#include "stdafx.h"
#include "Enemy_INKY.h"
#include "PacMan.h"
#include "Enemy_BLINKY.h"
#include "Actor.h"

static const char* Enemy_Inky_FilePath = "Assets/bashful_div.bmp";

Enemy_INKY::Enemy_INKY(SceneBase* sceneBase, PacMan* pacManPtr, Enemy_BLINKY* blinkyPtr, Vector2 StartPos) : EnemyBase(sceneBase, "Enemy", 1, pacManPtr, StartPos)
{
	m_packManPtr = pacManPtr;
	m_blinkyPtr = blinkyPtr;
}

Enemy_INKY::~Enemy_INKY()
{
}

void Enemy_INKY::Init()
{
	__super::Init();
	LoadDivGraph(Enemy_Inky_FilePath, EnemyBase::AnimationNum, 4, 4, 24, 24, m_drawHandle);
}

void Enemy_INKY::Update()
{
	//モードに応じてTargetを決める。
	switch (m_currentState)
	{
	case EnemyBase::InPrisonMode:
		//ターゲットは牢獄の中。
		m_target = WAIT_POINT;
		m_currentMoveSpeed = STANDARD_MOVE_SPEED;
		break;

	case EnemyBase::GetOutPrisonMode:
		//牢獄の前
		m_target = PRISON_FRONT;
		m_currentMoveSpeed = GETOUT_PRISON_SPEED;
		if (m_position == m_target)
		{
			m_currentState = ScatterMode;
		}
		break;

	case EnemyBase::ScatterMode:
		//ターゲットは常にPower餌の回り。
		m_currentMoveSpeed = STANDARD_MOVE_SPEED;
		m_target = SCATTER_POINT;
		break;

	case EnemyBase::ChaseMode:
	{
		//ターゲットは常にPlayer。
		Vector2 toPacMan = m_blinkyPtr->GetPosition() - m_packManPtr->GetPosition();
		m_target = m_packManPtr->GetPosition() + toPacMan * -1;
		m_currentMoveSpeed = STANDARD_MOVE_SPEED;
		break;
	}

	case EnemyBase::ReturnPrisonMode:
		//食べられて、牢獄帰還。
		m_target = PRISON_POINT;
		m_currentMoveSpeed = RETURN_PRISON_SPEED;
		if (m_position == m_target)
		{
			m_currentState = GetOutPrisonMode;
		}
		break;
	default:
		break;
	}

	//移動処理呼び出し。
	__super::Update();
}

void Enemy_INKY::Draw()
{
#ifdef DEBUG
	DrawCircle(m_target.x, m_target.y, 12, GetColor(0, 60, 255), true);
#endif // DEBUG
	__super::Draw();
}
