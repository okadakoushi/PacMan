#include "stdafx.h"
#include "EnemyBase.h"
#include "PacMan.h"

std::map<EnemyBase::DIRECTION, EnemyBase::ANIMATION> EnemyBase::m_directionToNormalAnimHandleIndex
{
	//�����A�A�j���[�V�����n���h���C���f�b�N�X�B
	{ Direction_Left,	LeftAnimation },
	{ Direction_Right,	RightAnimation },
	{ Direction_Up,		UpAnimation },
	{ Direction_Down,	DownAnimation },
};

std::map<EnemyBase::DIRECTION, EnemyBase::ANIMATION> EnemyBase::m_directionToEyeAnimHandleIndex
{
	{ Direction_Left,	LeftEyeAnimation },
	{ Direction_Right,	RightEyeAnimation },
	{ Direction_Up,		UpEyeAnimation },
	{ Direction_Down,	DownEyeAnimation },
};


EnemyBase::EnemyBase(SceneBase* sceneBase, const char* tag, int prio, PacMan* packPtr, Vector2 startPos) : 
	Actor(sceneBase, tag, prio, RectCollision::EnCollisionType_Dynamic),
	m_packManPtr(packPtr),
	START_POINT(startPos)
{
	m_sceneGame = dynamic_cast<SceneGame*>(sceneBase);
}

EnemyBase::~EnemyBase()
{
}

void EnemyBase::Init()
{
	m_position = START_POINT;
	m_collision.SetCollisionSize({ 18,18 });
	//�ŏ��̃t���[���͂�����WayPoint���v�Z���Ă����B
	WayPointSerch();
	Vector2 direction = (m_nextWayPoint - m_position).Normalized();
	m_direction = EngineMath::ConvertToIntVec(direction);
}

void EnemyBase::Update()
{	
	//�����̈ʒu���玟��WayPoint�܂ł̋����B
	float pos2nextWayLen = (m_nextWayPoint - m_position).Length();

	if (pos2nextWayLen > SPRITE_SIZE)
	{
		m_restMovePixcel = 0;
	}

	if (m_isTweek)
	{
		//�^�C�}�[�����Z�B
		m_tweekTimer += GameTime()->GetDeltaTime();
		m_currentMoveSpeed = TWEEK_MOVE_SPEED;

		if (m_tweekTimer > TWEEK_TIME)
		{
			//���������[�h���I�����Ă���B
			m_currentMoveSpeed = STANDARD_MOVE_SPEED;
			m_tweekTimer = 0.0f;
			m_isTweek = false;
		}

	}

	if (m_restMovePixcel <= 0.0f)
	{
		//�w��pix���ړ������̂Ŏ���wayPoint���v�Z����B
		if (m_isTweek && (m_currentState != GetOutPrisonMode) )
		{
			//���������[�h���̈ړ������s�B
			WayPointSerchForTweekMode();
		}
		else
		{
			//�ʏ�ړ������s�B
			WayPointSerch();
		}
		//����wayPoint���X�V���ꂽ���߁A�i�s�������X�V�B
		Vector2 Direction = (m_nextWayPoint - m_position).Normalized();
		m_direction = EngineMath::ConvertToIntVec(Direction);
		//�c��ړ��s�N�Z�����������B
		m_restMovePixcel = SPRITE_SIZE;
	}
	
	//�c��̈ړ��\�ʂ��v�Z�B������s��Ȃ��ƈړ��ʂ�ύX�����ۂ̈ʒu���s���ɂȂ�(�O���b�h�^�񒆂Ŏ~�܂�Ȃ��j�B
	float move = std::clamp(m_currentMoveSpeed, 0.0f, (float)m_restMovePixcel);
	m_position += m_direction * move;
	//�ړ������������B
	m_restMovePixcel -= move;

	AnimationUpdate();
}

void EnemyBase::Draw()
{
	Vector2 drawPos = { m_position.x + 12, m_position.y + 12 };
	Actor::m_spirte.Draw(drawPos, 1.5f, 0, m_drawHandle[m_currentAnimation]);


#ifdef DEBUG
	DrawLine(m_position.x + 12, m_position.y + 12, m_position.x + 12 + m_direction.x * 100, m_position.y + 12 + m_direction.y * 100, GetColor(255, 0, 0));
#endif
}

void EnemyBase::HitEffect(Actor* actor)
{
	if (m_isTweek)
	{
		//������
		Death();
	}
	else
	{
		//����
		PacMan* pacman = dynamic_cast<PacMan*>(actor);
		if (pacman != nullptr && (m_currentState != ReturnPrisonMode) )
		{
			pacman->Death();
		}
	}
}

void EnemyBase::Turning()
{
	if (!m_isTweek)
	{
		m_direction *= -1;
		//���]�������A�c��ړ��\�s�N�Z�����ύX�B
		m_restMovePixcel = SPRITE_SIZE - m_restMovePixcel;
	}
}

void EnemyBase::TweekEvent()
{
	Turning();
	m_tweekTimer = 0.0f;
	m_isTweek = true;
}

void EnemyBase::Death()
{
	m_currentState = ReturnPrisonMode;
	m_isTweek = false;
	m_tweekTimer = 0.0f;
	m_callDeadEvent = false;
	m_currentMoveSpeed = STANDARD_MOVE_SPEED;
}

std::vector<Vector2> EnemyBase::CanMoveNextWayPoint()
{
	//�ǂꂩ4�_�B
	const Vector2_Int NEXT_POSITION_LIST[4] = { {1,0}, {-1,0}, {0,1}, {0,-1} };
	Vector2_Int inverseDir = m_direction * -1;

	//�i�ނR�_
	std::vector<Vector2_Int> nextPosIndexList;
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
		nextPosIndex += GetPositionIndex(m_position);

		bool isHit = false;

		const std::vector<Actor*>& obstacleList = m_sceneGame->GetObstacles();

		//��Q���Ɠ����蔻������B
		for (Actor* obstacle : obstacleList)
		{
			//�Q�[�g��ʂ��X�e�[�g��
			bool isPassGateState = (m_currentState == GetOutPrisonMode) || (m_currentState == ReturnPrisonMode);
			
			if (isPassGateState)
			{
				if (obstacle->GetHash() == std::hash<std::string>()("Gate")) 
				{ 
					//�S������o�鎞�ƁA�S���ɖ߂鎞�̓Q�[�g����Q���Ƃ��Ă͔��肵�Ȃ��B
					continue; 
				}
			}

			Vector2_Int obstaclePosIndex = GetPositionIndex(obstacle->GetPosition());
			if (obstaclePosIndex == nextPosIndex)
			{
				isHit = true;
				break;
			}

		}

		//�Փ˂��Ȃ������B
		if (!isHit)
		{
			Vector2 nextPos = { (float)nextPosIndex.x * SPRITE_SIZE , (float)nextPosIndex.y * SPRITE_SIZE };
			nextPos += {SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f};
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
		float target2nextPos = (nextPos - m_target).Length();
		if (target2nextPos == min)
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
	//�����C���f�b�N�X�B
	DIRECTION directionIndex;
	//�C���f�b�N�X�����߂�B
	if (m_direction == EngineMath::LEFT)
	{
		directionIndex = Direction_Left;
	}
	else if (m_direction == EngineMath::RIGHT)
	{
		directionIndex = Direction_Right;
	}
	else if (m_direction == EngineMath::UP)
	{
		directionIndex = Direction_Up;
	}
	else if (m_direction == EngineMath::DOWN)
	{
		directionIndex = Direction_Down;
	}

	//�C���f�b�N�X���グ��B
	if (++m_animationWaitFrame > AnimationSpeed)
	{
		m_animationWaitFrame = 0;
		m_animationIndex++;
	}

	//���݂ǂ���̃A�j���[�V�����𗬂��Ă��邩����B
	int animationFrame = m_animationIndex % 2;

	if (m_isTweek)
	{
		if (m_tweekTimer > TWEEK_TIME * 0.7f)
		{
			//�`�J�`�J�B
			m_currentAnimation = animationFrame + TweekAnimation + 1;
		}
		else
		{
			m_currentAnimation = animationFrame + TweekAnimation;
		}
	}
	else if (m_currentState == ReturnPrisonMode)
	{
		//�����ɉ����ăn���h���C���f�b�N�X��Ԃ��B
		m_currentAnimation = m_directionToEyeAnimHandleIndex[directionIndex];
	}
	else
	{
		m_currentAnimation = animationFrame + m_directionToNormalAnimHandleIndex[directionIndex];
	}
}

