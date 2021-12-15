#include "stdafx.h"
#include "Enemy_BLINKY.h"
#include "PacMan.h"

static const char* Enemy_Blinky_FilePath = "Assets/shadow_div.png";

Enemy_BLINKY::Enemy_BLINKY(SceneBase* sceneBase, PacMan* pacManPtr, Vector2 StartPos) : EnemyBase(sceneBase, "Enemy", 1, pacManPtr, StartPos)
{

}

Enemy_BLINKY::~Enemy_BLINKY()
{
}

void Enemy_BLINKY::Init()
{
	__super::Init();
	LoadDivGraph(Enemy_Blinky_FilePath, EnemyBase::AnimationNum, 4, 4, 24, 24, m_drawHandle);
}

void Enemy_BLINKY::Update()
{
	//���[�h�ɉ�����Target�����߂�B
	switch (m_currentState)
	{
	case EnemyBase::InPrisonMode:
		//�^�[�Q�b�g�͘S���̒��B
		m_target = WAIT_POINT;
		m_currentMoveSpeed = STANDARD_MOVE_SPEED;
		break;

	case EnemyBase::GetOutPrisonMode:
		//�S���̑O
		m_target = PRISON_FRONT;
		m_currentMoveSpeed = GETOUT_PRISON_SPEED;
		if (m_position == m_target)
		{
			m_currentState = ScatterMode;
		}
		break;

	case EnemyBase::ScatterMode:
		//�^�[�Q�b�g�͏��Power�a�̉��B
		m_currentMoveSpeed = STANDARD_MOVE_SPEED;
		m_target = SCATTER_POINT;
		break;

	case EnemyBase::ChaseMode:
		//�^�[�Q�b�g�͏��Player�B
		m_target = m_packManPtr->GetPosition();
		m_currentMoveSpeed = STANDARD_MOVE_SPEED;
		break;

	case EnemyBase::ReturnPrisonMode:
		//�H�ׂ��āA�S���A�ҁB
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

	//�ړ������Ăяo���B
	__super::Update();
}

void Enemy_BLINKY::Draw()
{
	__super::Draw();
}
