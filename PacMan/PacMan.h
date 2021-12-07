#pragma once

#include "Wall.h"
#include "SceneGame.h"

class PacMan : public Actor
{
private:
	enum animation {
		moveAnimatiomEnd = 3,
		deadAnimatiomEnd = 12,
		AniamtionNum
	};

private:
	const float MOVE_SPEED = 2.0f;				//�ړ����x�B
	const Vector2 RESPAWN_POINT = { 500, 432 };	//�����n�_�B
	const Vector2 PLAYER_RESPAWN_POINT = { (float)SCREEN_WIDTH / 2 - SPRITE_SIZE / 2.0f , (float)SCREEN_HEIGHT / 2 + SPRITE_SIZE * 8.0f };

	Vector2 m_movedVector;						//�������x�N�g���B
	Vector2 m_frontFrameMoved;					//�O�t���[�������Ă��������B
	int m_bufferedInput = 0;					//��s���́B
	bool m_powerMode = false;					//�p���[���[�h���ǂ����B
	bool m_isDying = false;						//���S���o���B
	SceneGame* m_sceneGamePtr = nullptr;		//�V�[���̃|�C���^�B
	
	//�A�j���[�V�����B
	const int AnimationSpeed = 1;
	const int DEAD_ANIMATION_SPEED = 7;
	const int DEAD_FIRST_EDN_ANIMATION_SPEED = 60;
	int m_drawHandle[AniamtionNum];
	int m_animationIndex = 0;
	int m_animationWaitFrame = 0;

public:
	PacMan(SceneBase* sceneBase);

public:
	virtual void Init() override;
	virtual void OnCollision(Actor* actor) override;
	virtual void Update() override;
	virtual void Draw() override;
	void MoveAnimationUpdate();
	void Death();
	bool PlayDeadAnim();
	void ResetParams();
public:

	/// <summary>
	/// �������擾�B
	/// </summary>
	/// <returns></returns>
	const Vector2& GetDirection() const 
	{
		return m_frontFrameMoved.Normalized();
	}
	
	/// <summary>
	/// �p���[�N�b�L�[����肵�Ă��邩�B
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

