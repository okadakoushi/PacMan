#include "stdafx.h"
#include "Enemy_Pinky.h"
#include "PacMan.h"

static const char* Enemy_Pinky_fp = "Assets/speedy_div.bmp";

Enemy_Pinky::Enemy_Pinky(SceneBase* sceneBase, PacMan* pacManPtr, Vector2 StartPos) : EnemyBase(sceneBase, "Enemy", 1, pacManPtr, StartPos)
{

}

Enemy_Pinky::~Enemy_Pinky()
{
}

void Enemy_Pinky::Init()
{
	__super::Init();
	LoadDivGraph(Enemy_Pinky_fp, EnemyBase::AnimationNum, 4, 4, 24, 24, m_drawHandle);
}

void Enemy_Pinky::Update()
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
		//ターゲットはパックマンの方向*４タイル
		Vector2 travelDirection = m_packManPtr->GetDirection() * SPRITE_SIZE * 4;
		m_target = m_packManPtr->GetPosition() + travelDirection;
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

void Enemy_Pinky::Draw()
{
	__super::Draw();

#ifdef DEBUG
	DrawCircle(m_target.x, m_target.y, 12, GetColor(255, 120, 255), true);
#endif // DEBUG


}
