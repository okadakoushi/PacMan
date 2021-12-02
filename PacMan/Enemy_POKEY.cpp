#include "stdafx.h"
#include "Enemy_POKEY.h"
#include "PacMan.h"

Enemy_POKEY::Enemy_POKEY(SceneBase* sceneBase, PacMan* pacManPtr) : EnemyBase(sceneBase, "Enemy", 1, pacManPtr)
{
	m_packManPtr = pacManPtr;
}

void Enemy_POKEY::Init()
{
	LoadDivGraph("Assets/pokey_div.bmp", EnemyBase::AnimationNum, 4, 4, 24, 24, m_drawHandle);
}

void Enemy_POKEY::Update()
{
	//���[�h�ɉ�����Target�����߂�B
	switch (m_currentState)
	{
	case EnemyBase::InPrisonMode:
		//�^�[�Q�b�g�͘S���̒��B
		m_target = RESPAWN_POINT;
		m_currentMoveSpeed = STANDARD_MOVE_SPEED;
		break;

	case EnemyBase::GetOutPrisonMode:
		//�S���̑O
		m_target = PRISON_FRONT;
		m_currentMoveSpeed = GETOUT_PRISON_SPEED;
		if ((m_position - m_target).Length() <= 3.0f)
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
		//�����Ƃ���Player�A�߂��͎U�J�|�C���g�B
		if ((m_position - m_packManPtr->GetPosition()).Length() <= SPRITE_SIZE * 15)
		{
			m_target = SCATTER_POINT;
		}
		else
		{
			m_target = m_packManPtr->GetPosition();
		}
		m_currentMoveSpeed = STANDARD_MOVE_SPEED;
		break;

	case EnemyBase::ReturnPrisonMode:
		//�H�ׂ��āA�S���A�ҁB
		m_target = PRISON_POINT;
		m_currentMoveSpeed = RETURN_PRISON_SPEED;
		if ((m_position - m_target).Length() <= 3.0f)
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

void Enemy_POKEY::Draw()
{
#ifdef DEBUG
	DrawCircle(m_target.x, m_target.y, 12, GetColor(255, 127, 39), true);
#endif // DEBUG
	__super::Draw();
}
