#pragma once

class Actor;

class RectCollision
{
public:
	enum CollisionType
	{
		EnCollisionType_None =		0b0000,
		EnCollisionType_Static =	0b0001,
		EnCollisionType_Dynamic =	0b0010,
	};

private:
	static std::map<CollisionType, int> m_collisionTypeToBitTable;	//コリジョンタイプに応じて、ビットテーブルを返却。

	const CollisionType m_collisionType;							//コリジョンタイプ
	const int m_collisibleBitTable;									//衝突可能なビットテーブル。

public:
	RectCollision(CollisionType colType);

	/// <summary>
	/// 引数1のAABBが引数2のActorに当たっているかどうか。
	/// </summary>
	/// <param name="actor"></param>
	/// <param name="serchActor"></param>
	/// <returns></returns>
	bool CheckHitAABB(Actor* actor, Actor* serchActor);
	bool CheckHitAABB(const Vector2& actorPos, const Vector2& actorSize, const Vector2& serchActorPos, const Vector2& sercgActorSize);

	/// <summary>
	/// コリジョンタイプを取得。
	/// </summary>
	/// <returns></returns>
	CollisionType GetCollisionType()
	{
		return m_collisionType;
	}

	/// <summary>
	/// 衝突可能なオブジェクトをまとめたビットテーブルを取得。
	/// </summary>
	/// <param name="ActorType"></param>
	/// <returns></returns>
	int GetCollisionPossibleTable()
	{
		return m_collisibleBitTable;
	}
	
private:
	/// <summary>
	/// AABBを計算。
	/// </summary>
	/// <param name="vec"></param>
	void CalcMaxMinVert(const Vector2& vec, const Vector2& spriteSize, Vector2& max, Vector2& min);

};

