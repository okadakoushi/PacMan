#pragma once

#include "Object.h"

class Actor;
class SceneManager;

class SceneBase : public Object
{
public:
	/// <summary>
	/// SceneID.
	/// </summary>
	enum SceneID
	{
		EnSceneID_Title,
		EnSceneID_Game,
		EnSceneID_GameOver,
	};

protected:
	SceneID				m_nextStage = EnSceneID_Title;	//���̃V�[���B
	SceneManager*		m_sceneManagerPtr = nullptr;	//Manager�ւ�ptr�B	
	std::vector<Actor*>	m_actorList;					//�A�N�^�[���X�g�B

private:
	float				m_waitTime = 0.0f;				//wait�^�C���B
	float				m_currentWaitTime = 0.0f;		//���݂̑҂����ԁB

public:
	/// <summary>
	/// �R���X�g���N�^�B
	/// </summary>
	/// <param name="sceneManager">�V�[���}�l�[�W���[�B</param>
	SceneBase(SceneManager* sceneManager):
		Object::Object(0),
		m_sceneManagerPtr(sceneManager)
	{
	}
	/// <summary>
	/// �f�X�g���N�^�B
	/// </summary>
	virtual ~SceneBase()
	{

	}

public:
	/// <summary>
	/// �A�N�^�[��o�^�B
	/// </summary>
	/// <param name="actor">�o�^����A�N�^�[�B</param>
	void RegistActor(Actor* actor);

	/// <summary>
	/// �A�N�^�[���擾�B
	/// </summary>
	/// <param name="tag">�擾������Actor�̃^�O�B</param>
	Actor* GetActor(const char* tag);

	/// <summary>
	/// �o�^�����B
	/// </summary>
	/// <param name="actor"></param>
	void UnRegistActor(Actor* actor);

	/// <summary>
	/// �������B
	/// </summary>
	virtual void Init() = 0;

	/// <summary>
	/// �X�V�B
	/// </summary>
	virtual void Update();

private:
	///// <summary>
	///// �N���[���A�b�v�B
	///// </summary>
	//void CleanUp();

	/// <summary>
	/// �R���W�������m���������Ă��邩�̃`�F�b�N�B
	/// </summary>
	void CheckHitActorCollision();
};

