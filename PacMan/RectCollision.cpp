#include "stdafx.h"
#include "RectCollision.h"

//リストの初期化。
std::map<RectCollision::CollisionType, int> RectCollision::m_collisionTypeToBitTable = 
{
	//{コリジョンタイプ, 衝突テーブル}
	{EnCollisionType_None, EnCollisionType_None},
	{EnCollisionType_Static, EnCollisionType_Dynamic },
	{EnCollisionType_Dynamic, EnCollisionType_Static | EnCollisionType_Dynamic },
};

//コリジョンタイプとテーブルの初期化。
RectCollision::RectCollision(CollisionType colType) :
	m_collisionType(colType),
	m_collisibleBitTable(m_collisionTypeToBitTable.at(colType))
{
}

RectCollision::~RectCollision()
{
}

bool RectCollision::CheckHitAABB(Actor* actor, Actor* serchActor)
{
	return CheckHitAABB(actor->GetPosition(), actor->GetCollision().GetCollisionSize(), serchActor->GetPosition(), actor->GetCollision().GetCollisionSize());
}

bool RectCollision::CheckHitAABB(const Vector2& actorPos, const Vector2& actorSize, const Vector2& serchActorPos, const Vector2& serchActorSize)
{
	//AABB計算。
	Vector2 actorMax, actorMin;
	CalcMaxMinVert(actorPos, actorSize, actorMax, actorMin);

	//hit側AABB計算。
	Vector2 hitActorMax, hitActorMin;
	CalcMaxMinVert(serchActorPos, serchActorSize, hitActorMax, hitActorMin);

	//if ((actorMax.x > hitActorMin.x) && (actorMin.x < hitActorMax.x) &&
	//	(actorMax.y < hitActorMin.y) && (actorMin.y > hitActorMax.y)) {
	//	//衝突している。
	//	return true;
	//}
	//return false;

	if (actorMin.x >= hitActorMax.x) { return false; }
	if (actorMax.x <= hitActorMin.x) { return false; }
	if (actorMin.y <= hitActorMax.y) { return false; }
	if (actorMax.y >= hitActorMin.y) { return false; }
	return true;
}

void RectCollision::CalcMaxMinVert(const Vector2& vec, const Vector2& spriteSize, Vector2& max, Vector2& min)
{
	//max = { vec.x + spriteSize.x / 2 , vec.y - spriteSize.y / 2 };
	//min = { vec.x - spriteSize.x / 2 , vec.y + spriteSize.y / 2 };
	max = { vec.x + spriteSize.x , vec.y };
	min = { vec.x , vec.y + spriteSize.y};	
}
