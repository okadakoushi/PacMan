#pragma once

class PacMan;
class Wall;
class SceneGame;

class EnemyBase : public Actor
{
public:
	enum EnemyState
	{
		InPrisonMode = 1,	//�S�����B
		GetOutPrisonMode,	//�S������o��B
		ScatterMode,		//�U�J�B
		ChaseMode,			//�ǐՁB
		ReturnPrisonMode,	//�S�����A�ҁB
	};

protected:
	enum Animation
	{
		LeftAnimation = 0,
		RightAnimation = 2,
		UpAnimation = 4,
		DownAnimation = 6,
		LeftEyeAnimation = 8,
		RightEyeAnimation,
		UpEyeAnimation,
		DownEyeAnimation,
		TweekAnimation = 12,
		NearEndTweekAnimation = 14,
		AnimationNum
	};

	enum Direction
	{
		Direction_Left,
		Direction_Right,
		Direction_Up,
		Direction_Down
	};

protected:
	//�ړ����x�B
	const float			TWEEK_TIME			= 7.0f;		//���������[�h���ԁB
	const float			STANDARD_MOVE_SPEED = 2.0f;		//�ʏ펞�ړ����x�B
	const float			TWEEK_MOVE_SPEED	= 1.0f;		//���������ړ����x�B
	const float			RETURN_PRISON_SPEED = 6.0f;		//�S���A�Ҏ��̃X�s�[�h�B
	const float			GETOUT_PRISON_SPEED = 1.0f;		//�S������o��p�̃X�s�[�h�B
	
	//�ʒu�B
	const Vector2		START_POINT;												//�����ʒu�B
	const Vector2		PRISON_FRONT = { FIX_VALUE_X + 400.0f, FIX_VALUE_Y + 300.0f };	//�S���̑O�B
	const Vector2		PRISON_POINT = { FIX_VALUE_X + 400.0f, FIX_VALUE_Y + 360.0f };	//�S���̒��B

	//ptrs�B
	PacMan*				m_packManPtr = nullptr;					//�p�b�N�}���|�C���^�B
	SceneGame*			m_sceneGame = nullptr;					//�Q�[���B

	//�A�j���[�V�����B
	static std::map<Direction, Animation> m_directionToNormalAnimHandleIndex;	//�ʏ�A�j���[�V����
	static std::map<Direction, Animation> m_directionToEyeAnimHandleIndex;		//�ڋʂ̂݃A�j���[�V�����B
	const int AnimationSpeed = 5;								//�A�j���[�V�����̐؂�ւ����x(�t���[���j�B
	int m_drawHandle[AnimationNum];								//�A�j���[�V�������ׂĂ�DrawHandle�B
	unsigned int m_animationIndex = 0;							//�A�j���[�V�����̃C���f�b�N�X�B������g�p���Ď��ɗ����A�j���[�V���������߂�B
	int m_currentAnimation = 0;									//�Đ�����A�j���[�V�����B
	int m_animationWaitFrame = 0;								//���t���[���A�j���[�V�����𗬂������B

	//�ړ��p�B
	Vector2				m_direction = { 0, -1 };					//�����B
	Vector2				m_target = {504, 374};						//�^�[�Q�b�g�̈ʒu�B
	Vector2				m_nextWayPoint = START_POINT;				//����wayPoint�B
	float				m_currentMoveSpeed = STANDARD_MOVE_SPEED;	//���݂̈ړ����x�B
	EnemyState			m_currentState = InPrisonMode;				//���݂̃X�e�[�g�B
	int					m_restMovePixcel = SPRITE_SIZE / 2;			//�c��ړ��\�s�N�Z���B

	//���������[�h�p�B
	float				m_tweekTimer = 0.0f;		//���������[�h�p�^�C�}�[�B
	bool				m_isTweek = false;			//���������[�h���B
	int					m_nearEndTweekFrame = 2;	//�G�̓_�Ńt���[���B
	bool				m_callDeadEvent = false;	//���S�p�C�x���g

	//Sound
	int m_returnPrisonSE = 0;						//�S���A�ҁB

public:
	EnemyBase(SceneBase* sceneBase, const char* tag, int prio, PacMan* packPtr, Vector2 startPos);
	virtual ~EnemyBase();

public:
	virtual void Init() override;
	virtual void Update() override;
	virtual void Draw() override;
	virtual void OnCollision(Actor* actor) override {};
	
	/// <summary>
	/// �Փˌ��ʁB
	/// </summary>
	/// <param name="actor"></param>
	void HitEffect(Actor* actor);

	/// <summary>
	/// ���]�����B
	/// </summary>
	void Turning();

	/// <summary>
	/// ���������[�h���̃C�x���g�B
	/// </summary>
	void TweekEvent();
	
	/// <summary>
	/// ���݂̃X�e�[�g���擾�B
	/// </summary>
	/// <returns></returns>
	EnemyState GetCurrentState()
	{
		return m_currentState;
	}

	/// <summary>
	/// �f�b�h�C�x���g���Ă΂ꂽ���B
	/// </summary>
	/// <returns></returns>
	bool IsCallDeadEvent()
	{
		return m_callDeadEvent;
	}

	/// <summary>
	/// ���������[�h���B
	/// </summary>
	/// <returns></returns>
	bool IsTweek()
	{
		return m_isTweek;
	}

	/// <summary>
	/// �^�[�Q�b�g��ݒ�B
	/// </summary>
	/// <param name="target"></param>
	void SetTarget(Vector2& target)
	{
		m_target = target;
	}

	/// <summary>
	/// ���S�p�C�x���g��ݒ�B
	/// </summary>
	/// <param name="flag"></param>
	void SetDeadEvent(bool flag)
	{
		m_callDeadEvent = flag;
	}

	/// <summary>
	/// ���݂̃X�e�[�g��ύX�B
	/// </summary>
	/// <param name="state"></param>
	void ChangeCurrentState(EnemyState state)
	{
		m_currentState = state;
	}

protected:	
	//�}�X�ڏ�Ƀ}�b�v���݂��Ƃ��ɂǂ��ɔz�u����Ă��邩�B�Q�Ƃ��Ȃ��B
	Vector2 GetPositionIndex(Vector2& pos)
	{
		Vector2 centerPos = { SCREEN_WIDTH / 2 , SCREEN_HEIGHT / 2 };
		Vector2 posIndex = pos - centerPos;
		return posIndex = { (posIndex.x / SPRITE_SIZE), (posIndex.y / SPRITE_SIZE) };
	}

private:
	/// <summary>
	/// ���������[�h���ȊO�̌o�H�����B
	/// </summary>
	void WayPointSerch();

	/// <summary>
	/// ���������[�h���p�̌o�H�����B
	/// </summary>
	void WayPointSerchForTweekMode();

	/// <summary>
	/// ���S�������B
	/// </summary>
	void Death();

	/// <summary>
	/// ���̈ړ����n�_4�_�ɑ΂��āA�ړ��\�ȏꏊ��Ԃ��B
	/// <para>���[�J���ϐ���Ԃ����߁A�߂�l���Q�ƂɕύX���Ȃ��ł��������B</para>
	/// </summary>
	/// <returns></returns>
	std::vector<Vector2> CanMoveNextWayPoint();

	/// <summary>
	/// �A�j���[�V�����̍X�V�B
	/// </summary>
	void AnimationUpdate();
};
