#pragma once

#include "Object.h"
#include "Sprite.h"
#include "RectCollision.h"

class Actor : public Object
{
public:

	enum ExcutionFlagType
	{
		EnExcutionFlagType_NotActive	= 1 << 0,	//�A�N�e�B�u�ł͂Ȃ��B
		EnExcutionFlagType_Update		= 1 << 1,	//�X�V
		EnExcutionFlagType_Draw			= 1 << 2,	//�`��B
		EnExcutionFlagType_Dead			= 1 << 3,	//�폜�B
		EnExcutionFlagType_Active		= EnExcutionFlagType_Update | EnExcutionFlagType_Draw,	//�A�N�e�B�u�i�X�V�A�`��)
	};

protected:
	Sprite				m_spirte;												//�X�v���C�g�B
	Vector2				m_position = { SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 };	//�ʒu�B
	Vector2				m_spriteSize = { SPRITE_SIZE,SPRITE_SIZE };				//�X�v���C�g�̃T�C�Y�B
	RectCollision		m_collision;											//�R���W�����B
	SceneBase*			m_sceneBasePtr;											//�V�[���x�[�X��Ptr�B
	ExcutionFlagType	m_actorExcutionFlag = EnExcutionFlagType_Active;		//�A�N�^�[�̎��s�t���O�B
	//Vector2			m_scale;												//�g��B
	//float				m_rotation = 0.0f;										//��]�B

private:
	size_t				m_hash = -1;											//�n�b�V���B


public:
	/// <summary>
	/// �R���X�g���N�^�B
	/// </summary>
	/// <param name="sceneBase"></param>
	/// <param name="tag"></param>
	/// <param name="prio"></param>
	Actor(SceneBase* sceneBase, std::string tag, int prio, RectCollision::CollisionType colType);
	
	/// <summary>
	/// �f�X�g���N�^�B
	/// </summary>
	virtual ~Actor();

	/// <summary>
	/// �������B
	/// </summary>
	virtual void Init() {};

	/// <summary>
	/// �X�V�B
	/// </summary>
	virtual void Update() {};

	/// <summary>
	/// �I���R���W�����B
	/// <para>�R���W��������Actor��Actor���Փ˂����ꍇ�ɌĂяo�������B</para>
	/// <para>�K�v�ɉ����āA�֐����I�[�o�[���C�h���ďՓˌ�̏�������������B</para>
	/// </summary>
	/// <param name="actor">�Փ˂����I�u�W�F�N�g�B</param>
	virtual void OnCollision(Actor* actor) {};

	/// <summary>
	/// �`��B
	/// </summary>
	virtual void Draw() {};

public://Getter_Setter
	//�ʒu�擾�B
	Vector2& GetPosition() 
	{
		return m_position;
	}
	
	//�X�v���C�g�̃T�C�Y���擾�B
	Vector2& GetSpriteSize()
	{
		return m_spriteSize;
	}

	//���s�t���O���擾�B
	ExcutionFlagType GetActorExcutionFlag()
	{
		return m_actorExcutionFlag;
	}

	//�R���W�������擾�B
	RectCollision& GetCollision()
	{
		return m_collision;
	}

	//�n�b�V�����擾�B
	const size_t GetHash() const 
	{
		return m_hash;
	}

	//���s�t���O��ݒ�B
	void SetExcutionFlag(ExcutionFlagType flagType)
	{
		m_actorExcutionFlag = flagType;
	}
	
	//�ʒu��ݒ�B
	void SetPosition(const Vector2& pos)
	{
		m_position = pos;
	}
	
	//�V�[����ݒ�B
	void SetSceneBase(SceneBase* sceneBase)
	{
		m_sceneBasePtr = sceneBase;
	}
};

