#include "stdafx.h"
#include "Enemy_Pinky.h"
#include "PacMan.h"

Enemy_Pinky::Enemy_Pinky(SceneBase* sceneBase, PacMan* pacManPtr) : EnemyBase(sceneBase, "Enemy", 1, pacManPtr)
{

}

void Enemy_Pinky::Init()
{
	LoadDivGraph("Assets/speedy_div.bmp", EnemyBase::AnimationNum, 4, 4, 24, 24, m_drawHandle);
}

void Enemy_Pinky::Update()
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
		//�^�[�Q�b�g�̓p�b�N�}���̕���*�S�^�C��
		m_target = m_packManPtr->GetPosition() + m_packManPtr->GetDirection() * SPRITE_SIZE * 4;
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

void Enemy_Pinky::Draw()
{
	__super::Draw();

#ifdef DEBUG
	DrawCircle(m_target.x, m_target.y, 12, GetColor(255, 120, 255), true);
#endif // DEBUG


}
