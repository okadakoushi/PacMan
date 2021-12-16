#pragma once

#include "StageObject/Wall.h"
#include "SceneGame.h"

class PacMan : public Actor
{
private:
	enum ANIMATION {
		moveAnimatiomEnd = 3,
		deadAnimatiomEnd = 12,
		AniamtionNum
	};

private:
	const float MOVE_SPEED = 2.00f;				//�ړ����x�B
	const Vector2 PLAYER_RESPAWN_POINT = { (float)SCREEN_WIDTH / 2 - SPRITE_SIZE / 2.0f +1 , (float)SCREEN_HEIGHT / 2 + SPRITE_SIZE * 8.0f };

	Vector2 m_movedVector;						//�������x�N�g���B
	Vector2 m_frontFrameMoved;					//�O�t���[�������Ă��������B
	int m_bufferedInput = 0;					//��s���́B
	bool m_powerMode = false;					//�p���[���[�h���ǂ����B
	bool m_isDying = false;						//���S���o���B
	SceneGame* m_sceneGamePtr = nullptr;		//�V�[���̃|�C���^�B
	
	//�A�j���[�V�����B
	const int AnimationSpeed = 1;					//�A�j���[�V�������x
	const int DEAD_ANIMATION_SPEED = 7;				//���S�A�j���[�V�������x
	const int DEAD_FIRST_EDN_ANIMATION_SPEED = 60;	//��[�ƏI�[�̑��x�B
	int m_drawHandle[AniamtionNum] = { 0 };			//�A�j���[�V�������̃n���h���B
	int m_animationIndex = 0;						//�C���f�b�N�X�B
	int m_frontFrameAnimIndex = 0;					//�O�t���[���̃A�j���[�V�����B
	int m_animationWaitFrame = 0;					//�A�j���[�V�����؂�ւ��̃t���[�����B

	//�T�E���h�B
	int m_deadSE = 0;								//���SSE�B
	int m_eatingSE = 0;								//Cookie�H�ׂ鉹�B

public:
	PacMan(SceneBase* sceneBase);
	virtual ~PacMan();

public:
	virtual void Init() override;
	virtual void OnCollision(Actor* actor) override;
	virtual void Update() override;
	virtual void Draw() override;

	/// <summary>
	/// �ړ��A�j���[�V�����̍X�V�B
	/// </summary>
	void MoveAnimationUpdate();

	/// <summary>
	/// ���S�����B
	/// </summary>
	void Death();

	/// <summary>
	/// ���S�A�j���[�V�������Đ��B
	/// </summary>
	/// <returns>�Đ����I�[�܂ōs������Atrue��Ԃ��B</returns>
	bool PlayDeadAnim();

	/// <summary>
	/// �p�����[�^�[�����Z�b�g�B
	/// </summary>
	void ResetParams();

public:
	/// <summary>
	/// �������擾�B
	/// </summary>
	/// <returns></returns>
	Vector2 GetDirection() 
	{
		return m_frontFrameMoved.Normalized();
	}
	
	/// <summary>
	/// �p���[���[�h���B
	/// </summary>
	/// <returns></returns>
	bool IsPowerMode() 
	{
		return m_powerMode;
	}

	/// <summary>
	/// ���S���o����.
	/// </summary>
	/// <returns></returns>
	bool IsDying()
	{
		return m_isDying;
	}
	
	/// <summary>
	/// �p���[�N�b�L�[������Ă��邩��ݒ�B
	/// </summary>
	/// <param name="isGet"></param>
	void SetPowerMode(bool isPowerMode)
	{
		m_powerMode = isPowerMode;
	}

private:
	/// <summary>
	/// ��Q���ƏՓ˂��Ă��Ȃ����m�F�B
	/// </summary>
	bool CheckHitObstacle();
};

