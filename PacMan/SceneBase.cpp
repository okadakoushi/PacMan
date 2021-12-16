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
//		//Level配置されているActorを全削除。
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
	//actor検索。
	auto it = std::find(m_actorList.begin(), m_actorList.end(), actor);

	if (it == m_actorList.end())
	{
		return;
	}

	//リストから削除。
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
			//お互いのUpdateフラグが立っているか。
			bool IsActorUpdate_i = m_actorList[i]->GetActorExcutionFlag() & Actor::EnExcutionFlagType_Update;
			bool IsActorUpdate_j = m_actorList[j]->GetActorExcutionFlag() & Actor::EnExcutionFlagType_Update;
			
			if (IsActorUpdate_i && IsActorUpdate_j)
			{
				//衝突可能コリジョンタイプをまとめたビットテーブル。
				int CollisionPossibleType = m_actorList[i]->GetCollision().GetCollisionPossibleTable();
				//自分のコリジョンタイプ。
				int CollisionType = m_actorList[j]->GetCollision().GetCollisionType();
				
				//衝突するかの判定を取る。
				if (CollisionPossibleType & CollisionType)
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
