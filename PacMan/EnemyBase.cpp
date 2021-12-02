#include "stdafx.h"
#include "EnemyBase.h"
#include "PacMan.h"

EnemyBase::EnemyBase(SceneBase* sceneBase, const char* tag, int prio, PacMan* packPtr) : 
	Actor(sceneBase, tag, prio, RectCollision::EnCollisionType_Dynamic),
	m_packManPtr(packPtr) 
{
	//tweekSprite�͋��ʂ̂��߁A�����ŏ��������Ă����B
	//m_tweekSprite.Init("Assets/weak.bmp");
	m_sceneGame = dynamic_cast<SceneGame*>(sceneBase);
}

void EnemyBase::Update()
{	
	if (m_isArrive) {

		if ((int)m_position.x % 24 + 12 != 0 || (int)m_position.y % 24 != 0)
		{
			m_position = { floor(m_position.x / 24) * 24 + 12, floor(m_position.y / 24) * 24 };
		}

		if (m_currentState != TweekMode)
		{
			//�E�F�C�|�C���g����������B
			WayPointSerch();
		}
		else
		{
			if (!m_callTweekEvent)
			{
				//���������[�h���A�ړ��p�����[�^�[��ύX����B
				m_direction *= -1;
				m_callTweekEvent = true;
				m_currentMoveSpeed = TWEEK_MOVE_SPEED;
			}

			//���������[�h�p�̈ړ��B
			WayPointSerchForTweekMode();

			//���������[�h���I�����Ă��邩�B
			if (m_tweekTimer > TWEEK_TIME)
			{
				m_currentState = ChaseMode;
				m_currentMoveSpeed = STANDARD_MOVE_SPEED;
				m_tweekTimer = 0.0f;
				m_callTweekEvent = false;
			}
		}

		//�������v�Z�B
		m_direction = (GetPositionIndex(m_nextWayPoint) - GetPositionIndex(GetPosition())).Normalized();
		m_isArrive = false;
	}

	//����wayPoint�܂ňړ�������B
	m_position += m_direction * m_currentMoveSpeed;

	if (m_nextWayPoint == m_position)
	{
		//�������Ă���B
		m_isArrive = true;
	}

	if (m_currentState == TweekMode)
	{
		m_tweekTimer += GameTime()->GetDeltaTime();
	}

	AnimationUpdate();
}

void EnemyBase::Draw()
{
	Actor::m_spirte.Draw({ m_position.x + 12, m_position.y + 12 }, 1.5, 0, m_drawHandle[m_currentAnimation]);


#ifdef DEBUG
	DrawLine(m_position.x + 12, m_position.y + 12, m_position.x + 12 + m_direction.x * 100, m_position.y + 12 + m_direction.y * 100, GetColor(255, 0, 0));
#endif
}

void EnemyBase::HitEffect(Actor* actor)
{
	if (m_currentState == TweekMode)
	{
		//������
		Death();
	}
	else
	{
		//����
		PacMan* pacman = dynamic_cast<PacMan*>(actor);
		if (pacman != nullptr && m_currentState != ReturnPrisonMode)
		{
			pacman->Death();
		}
	}
}

void EnemyBase::Death()
{
	m_currentState = ReturnPrisonMode;
	m_isArrive = true;
	m_tweekTimer = 0.0f;
	m_callDeadEvent = false;
	m_callTweekEvent = false;
	m_currentMoveSpeed = STANDARD_MOVE_SPEED;
}

std::vector<Vector2> EnemyBase::CanMoveNextWayPoint()
{
	//�ǂꂩ4�_�B
	const Vector2 NEXT_POSITION_LIST[4] = { {1,0}, {-1,0}, {0,1}, {0,-1} };
	Vector2 inverseDir = m_direction * -1;

	//�i�ނR�_
	std::vector<Vector2> nextPosIndexList;
	//���R�_���Z�o�B
	for (auto nextIndex : NEXT_POSITION_LIST) 
	{
		if (nextIndex == inverseDir) 
		{
			//���Ε����ƈꏏ�Ȃ̂ŃX�L�b�v�B
			continue;
		}
		nextPosIndexList.push_back(nextIndex);
	}
	
	std::vector<Vector2> nexPosList;
	//���R�_���i�s�\�ȃG���A�����ׂ�B
	for (auto& nextPosIndex : nextPosIndexList) 
	{
		//���ɐi�ޗ\��̃}�X�B
		nextPosIndex += Vector2(GetPositionIndex(GetPosition()).x, GetPositionIndex(GetPosition()).y);

		bool isHit = false;

		const std::vector<Actor*>& m_obstacleList = m_sceneGame->GetObstacles();

		//��Q���Ɠ����蔻������B
		for (Actor* obstacle : m_obstacleList)
		{
			if (m_currentState == GetOutPrisonMode || m_currentState == ReturnPrisonMode && obstacle->GetHash() == std::hash<std::string>()("Gate"))
			{
				continue;
			}

			Vector2 obstaclePosIndex = GetPositionIndex(obstacle->GetPosition());
			if (obstaclePosIndex == nextPosIndex)
			{
				isHit = true;
				break;
			}

		}

		//�Փ˂��Ȃ������B
		if (!isHit)
		{
			Vector2 nextPos = { nextPosIndex.x * SPRITE_SIZE , nextPosIndex.y * SPRITE_SIZE };
			nextPos += {SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2};
			//������Ƃ������W�ɖ߂��ă��X�g�ɐςށB

			nexPosList.push_back(nextPos);
		}

	}

	return nexPosList;
}

void EnemyBase::WayPointSerch()
{
	//���Ɍ������ʒu�̃��X�g������Ă���B
	std::vector<Vector2> nexPosList = CanMoveNextWayPoint();

	//��������āA���Player�Ƌ������������Ȃ���̂��̗p�B
	float lens[3];
	if (nexPosList.size() != 1)
	{
		for (int i = 0; i < nexPosList.size(); i++)
		{
			lens[i] = (nexPosList[i] - m_target).Length();
		}
	}
	else
	{
		m_nextWayPoint = nexPosList[0];
		return;
	}

	//��ԋ������߂�wayPoint�����������B
	float min = *std::min_element(lens, lens + nexPosList.size());

	//�Y����length�������Ă���v�f�������B
	for (auto nextPos : nexPosList)
	{
		if ((nextPos - m_target).Length() == min)
		{
			m_nextWayPoint = nextPos;
		}
	}

}

void EnemyBase::WayPointSerchForTweekMode()
{
	std::vector<Vector2> CanMoveList = CanMoveNextWayPoint();
	//�����_���Ŏ��ɐi�s����ꏊ��I�ԁB
	int nextMoveIndex = std::rand() % CanMoveList.size();
	//����B
	m_nextWayPoint = CanMoveList[nextMoveIndex];
}

void EnemyBase::AnimationUpdate()
{
	if (++m_animationWaitFrame > AnimationSpeed)
	{
		m_animationWaitFrame = 0;
		m_animationIndex++;
	}

	//�������� todo:���t�@�N�^�����O�B
	if (m_currentState == TweekMode)
	{
		if (m_tweekTimer > TWEEK_TIME * 0.8f)
		{
			m_currentAnimation = m_animationIndex % 2 + TweekAnimation + 1;
		}
		else
		{
			m_currentAnimation = m_animationIndex % 2 + TweekAnimation;
		}
	}
	else if (m_direction.x == -1)
	{
		if (m_currentState == ReturnPrisonMode)
		{
			m_currentAnimation = LeftEyeAnimatiton;
		}
		else
		{
			m_currentAnimation = m_animationIndex % 2 + LeftAnimation;
		}
	}
	else if (m_direction.x == 1)
	{
		if (m_currentState == ReturnPrisonMode)
		{
			m_currentAnimation = RightEyeAnimatiton;
		}
		else
		{
			m_currentAnimation = m_animationIndex % 2 + RightAnimation;
		}
	}
	else if (m_direction.y == -1)
	{
		if (m_currentState == ReturnPrisonMode)
		{
			m_currentAnimation = UpEyeAnimatiton;
		}
		else
		{
			m_currentAnimation = m_animationIndex % 2 + UpAnimation;
		}
	}
	else if (m_direction.y == 1)
	{
		if (m_currentState == ReturnPrisonMode)
		{
			m_currentAnimation = DownEyeAnimatiton;
		}
		else
		{
			m_currentAnimation = m_animationIndex % 2 + DownAnimatiom;
		}
	}

}

