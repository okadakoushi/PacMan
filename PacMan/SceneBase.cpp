#include "stdafx.h"
#include "SceneBase.h"
#include "RectCollision.h"

void SceneBase::Update()
{
	//�X�V�B
	for (auto* actor : m_actorList)
	{
		if (actor->GetActorExcutionFlag() & Actor::EnExcutionFlagType_Update)
		{
			actor->Update();
		}
	}

	//�I���R���W�����B
	CheckHitActorCollision();

	//�`��B
	for (auto* actor : m_actorList)
	{
		if (actor->GetActorExcutionFlag() & Actor::EnExcutionFlagType_Draw)
		{
			actor->Draw();
		}
	}

	for (auto* actor : m_actorList)
	{
		if (actor->GetActorExcutionFlag() & Actor::EnExcutionFlagType_Dead)
		{
			auto it = std::find(m_actorList.begin(), m_actorList.end(), actor);
			if (it != m_actorList.end())
			{
				delete actor;
			}
		}
	}
}

//void SceneBase::CleanUp()
//{
//	for (auto* actor : m_actorList) 
//	{
//		//Level�z�u����Ă���Actor��S�폜�B
//		delete actor;
//	}
//	//m_sceneManagerPtr->ChangeScene()
//}

SceneBase::SceneBase(SceneManager* sceneManager) :
	Object::Object(0),
	m_sceneManagerPtr(sceneManager)
{
}

SceneBase::~SceneBase()
{
}

void SceneBase::RegistActor(Actor* actor)
{
	m_actorList.push_back(actor);
}

Actor* SceneBase::GetActor(const char* tag)
{
	for (auto* actor : m_actorList)
	{
		if (actor->GetHash() == std::hash<std::string>()(tag))
		{
			return actor;
		}
	}
}

void SceneBase::UnRegistActor(Actor* actor)
{
	//actor�����B
	auto it = std::find(m_actorList.begin(), m_actorList.end(), actor);

	if (it == m_actorList.end())
	{
		return;
	}

	//���X�g����폜�B
	m_actorList.erase(it);
}

void SceneBase::CheckHitActorCollision()
{	
	if (m_actorList.size() == 0)
	{
		return;
	}

	for (int i = 0; i < m_actorList.size() - 1; i++)
	{
		for (int j = i + 1; j < m_actorList.size(); j++)
		{
			//���݂���Update�t���O�������Ă��邩�B
			bool IsActorUpdate_i = m_actorList[i]->GetActorExcutionFlag() & Actor::EnExcutionFlagType_Update;
			bool IsActorUpdate_j = m_actorList[j]->GetActorExcutionFlag() & Actor::EnExcutionFlagType_Update;
			
			if (IsActorUpdate_i && IsActorUpdate_j)
			{
				//�Փˉ\�R���W�����^�C�v���܂Ƃ߂��r�b�g�e�[�u���B
				int CollisionPossibleType = m_actorList[i]->GetCollision().GetCollisionPossibleTable();
				//�����̃R���W�����^�C�v�B
				int CollisionType = m_actorList[j]->GetCollision().GetCollisionType();
				
				//�Փ˂��邩�̔�������B
				if (CollisionPossibleType & CollisionType)
				{
					if (m_actorList[i]->GetCollision().CheckHitAABB(m_actorList[i], m_actorList[j]))
					{
						//���΂̑g�ݍ��킹�͑��݂��Ȃ����߁A�����ŌĂяo���Ă����B
						m_actorList[i]->OnCollision(m_actorList[j]);
						m_actorList[j]->OnCollision(m_actorList[i]);
					}
				}
			}
		}
	}

}
