#include "stdafx.h"
#include "Enemy_POKEY.h"
#include "Character/PacMan.h"

static const char* Enemy_Pokey_FilePath = "Assets/pokey_div.bmp";

Enemy_POKEY::Enemy_POKEY(SceneBase* sceneBase, PacMan* pacManPtr, Vector2 StartPos) : EnemyBase(sceneBase, "Enemy", 1, pacManPtr, StartPos)
{
	m_packManPtr = pacManPtr;
}

Enemy_POKEY::~Enemy_POKEY()
{
}

void Enemy_POKEY::Init()
{
	__super::Init();
	LoadDivGraph(Enemy_Pokey_FilePath, EnemyBase::AnimationNum, 4, 4, 24, 24, m_drawHandle);
}

void Enemy_POKEY::Update()
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
	{
		//�����Ƃ���Player�A�߂��͎U�J�|�C���g�B
		float toPacManLen = (m_packManPtr->GetPosition() - m_position).Length();
		if (toPacManLen <= SPRITE_SIZE * CHASE_TILED)
		{
			m_target = SCATTER_POINT;
		}
		else
		{
			m_target = m_packManPtr->GetPosition();
		}
		m_currentMoveSpeed = STANDARD_MOVE_SPEED;
		break;
	}

	case EnemyBase::ReturnPrisonMode:
	{
		//�H�ׂ��āA�S���A�ҁB
		m_target = PRISON_POINT;
		m_currentMoveSpeed = RETURN_PRISON_SPEED;
		float len = (m_position - m_target).Length();
		if (len < 3)
		{
			m_currentState = GetOutPrisonMode;
		}
		break;
	}
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
