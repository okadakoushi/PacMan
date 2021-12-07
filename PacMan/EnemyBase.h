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
		TweekMode,			//�������B
		ReturnPrisonMode,	//�S�����A�ҁB
	};

protected:
	enum Animation
	{
		LeftAnimation = 0,
		RightAnimation = 2,
		UpAnimation = 4,
		DownAnimatiom = 6,
		LeftEyeAnimatiton = 8,
		RightEyeAnimatiton,
		UpEyeAnimatiton,
		DownEyeAnimatiton,
		TweekAnimation = 12,
		NearEndTweekAnimation = 14,
		AnimationNum
	};

protected:
	//�萔�B
	const float			TWEEK_TIME			= 10.0f;	//���������[�h���ԁB
	const float			STANDARD_MOVE_SPEED = 2.0f;		//�ʏ펞�ړ����x�B
	const float			TWEEK_MOVE_SPEED	= 1.0f;		//���������ړ����x�B
	const float			RETURN_PRISON_SPEED = 6.0f;		//�S���A�Ҏ��̃X�s�[�h�B
	const float			GETOUT_PRISON_SPEED = 1.0f;		//�S������o��p�̃X�s�[�h�B
	const Vector2		START_POINT;					//�����ʒu�B
	const Vector2		PRISON_FRONT = { 504, 288 };	//�S���̑O�B

	//ptr.
	PacMan*				m_packManPtr = nullptr;					//�p�b�N�}���|�C���^�B
	SceneGame*			m_sceneGame = nullptr;

	//�A�j���[�V�����B
	const int AnimationSpeed = 5;								//�A�j���[�V�����̐؂�ւ����x�B
	int m_drawHandle[AnimationNum];								//�A�j���[�V�������ׂĂ�DrawHandle�B
	unsigned int m_animationIndex = 0;							//�A�j���[�V�����̃C���f�b�N�X�B������g�p���Ď��ɗ����A�j���[�V���������߂�B
	int m_currentAnimation = 0;									//�Đ�����A�j���[�V�����B
	int m_animationWaitFrame = 0;								//���t���[���A�j���[�V�����𗬂������B
	static std::map<std::pair<int, int>, Animation> m_directionToHandleIndex;

	//�ړ��p�B
	bool				m_isArrive = true;			//wayPoint�ɓ������Ă�H
	Vector2				m_direction = { 0, -1 };	//�����B
	Vector2				m_target = {504, 374};		//�^�[�Q�b�g�̈ʒu�B
	Vector2				m_nextWayPoint = START_POINT;				//����wayPoint�B
	float				m_currentMoveSpeed = STANDARD_MOVE_SPEED;
	EnemyState			m_currentState = InPrisonMode;
	EnemyState			m_fontState;

	//�c��̈ړ��\�s�N�Z���B
	int					m_restMovePixcel = 0;

	//���������[�h�p�B
	Sprite				m_tweekSprite;				//���������[�h�̃X�v���C�g�B
	float				m_tweekTimer = 0.0f;		//���������[�h�p�^�C�}�[�B
	bool				m_callTweekEvent = false;	//���������[�h�p�C�x���g���Ăяo�������B
	bool				m_callDeadEvent = false;	//���S�p�C�x���g
	int					m_nearEndTweekFrame = 2;

	//Sound
	int m_returnPrisonSE = 0;


public:
	EnemyBase(SceneBase* sceneBase, const char* tag, int prio, PacMan* packPtr, Vector2 startPos);
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
	/// ���݂̃X�e�[�g���擾�B
	/// </summary>
	/// <returns></returns>
	EnemyState GetCurrentState()
	{
		return m_currentState;
	}

	void SetFrontState(EnemyState state)
	{
		m_fontState = state;
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
	/// �^�[�Q�b�g��ݒ�B
	/// </summary>
	/// <param name="target"></param>
	void SetTarget(Vector2& target)
	{
		m_target = target;
	}

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
	/// ���������[�h���ȊO�̌o�H�����B
	/// </summary>
	void WayPointSerch();
	
	/// <summary>
	/// ���������[�h���p�̌o�H�����B
	/// </summary>
	void WayPointSerchForTweekMode();
	
	//�}�X�ڏ�Ƀ}�b�v���݂��Ƃ��ɂǂ��ɔz�u����Ă��邩�B�Q�Ƃ��Ȃ��B
	Vector2 GetPositionIndex(Vector2& pos)
	{
		Vector2 centerPos = { SCREEN_WIDTH / 2 , SCREEN_HEIGHT / 2 };
		Vector2 posIndex = pos - centerPos;
		return posIndex = { (posIndex.x / SPRITE_SIZE), (posIndex.y / SPRITE_SIZE) };
	}
private:
	void AnimationUpdate();
};

