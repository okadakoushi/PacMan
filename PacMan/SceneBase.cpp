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
			m_actorList.erase(std::find(m_actorList.begin(), m_actorList.end(), actor));
			delete actor;
			actor = nullptr;
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
		//������Ȃ�����
		return;
	}

	//���X�g����폜�B
	m_actorList.erase(it);
}

void SceneBase::CheckHitActorCollision()
{	
	for (int i = 0; i < m_actorList.size() - 1; i++)
	{
		for (int j = i + 1; j < m_actorList.size(); j++)
		{
			if ((m_actorList[i]->GetActorExcutionFlag() & Actor::EnExcutionFlagType_Update) 
				&& (m_actorList[j]->GetActorExcutionFlag() & Actor::EnExcutionFlagType_Update))
			{
				//�R���W�������Փˉ\�R���W�����e�[�u���Ŕ��肷��B
				if (m_actorList[i]->GetCollision().GetCollisionPossibleTable() & m_actorList[j]->GetCollision().GetCollisionType())
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
