#include "stdafx.h"
#include "SceneBase.h"
#include "RectCollision.h"

void SceneBase::Update()
{
	//更新。
	for (auto* actor : m_actorList)
	{
		if (actor->GetActorExcutionFlag() & Actor::EnExcutionFlagType_Update)
		{
			actor->Update();
		}
	}

	//オンコリジョン。
	CheckHitActorCollision();

	//描画。
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
//		//Level配置されているActorを全削除。
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
	//actor検索。
	auto it = std::find(m_actorList.begin(), m_actorList.end(), actor);

	if (it == m_actorList.end())
	{
		//見つからなかった
		return;
	}

	//リストから削除。
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
				//コリジョンを衝突可能コリジョンテーブルで判定する。
				if (m_actorList[i]->GetCollision().GetCollisionPossibleTable() & m_actorList[j]->GetCollision().GetCollisionType())
				{
					if (m_actorList[i]->GetCollision().CheckHitAABB(m_actorList[i], m_actorList[j]))
					{
						//反対の組み合わせは存在しないため、ここで呼び出しておく。
						m_actorList[i]->OnCollision(m_actorList[j]);
						m_actorList[j]->OnCollision(m_actorList[i]);
					}
				}
			}
		}
	}

}
