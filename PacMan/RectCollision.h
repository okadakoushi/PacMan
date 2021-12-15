#pragma once

class Actor;

class RectCollision
{
public:
	enum COLLISION_TYPE
	{
		EnCollisionType_None =		0,
		EnCollisionType_Static =	1 << 0,
		EnCollisionType_Dynamic =	1 << 1,
	};

private:
	static std::map<COLLISION_TYPE, int> m_collisionTypeToBitTable;	//コリジョンタイプに応じて、ビットテーブルを返却。

	const COLLISION_TYPE m_collisionType;							//コリジョンタイプ
	const int m_collisibleBitTable;									//衝突可能なビットテーブル。
	Vector2	m_collisionSize = { SPRITE_SIZE, SPRITE_SIZE };			//コリジョンのサイズ。

public:
	RectCollision(COLLISION_TYPE colType);
	~RectCollision();

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
	COLLISION_TYPE GetCollisionType()
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

	/// <summary>
	/// コリジョンサイズを設定。
	/// </summary>
	/// <param name="size"></param>
	void SetCollisionSize(Vector2 size)
	{
		m_collisionSize = size;
	}

	/// <summary>
	/// コリジョンサイズを取得。
	/// </summary>
	/// <returns>コリジョンサイズを取得。</returns>
	Vector2 GetCollisionSize()
	{
		return m_collisionSize;
	}
	
private:
	/// <summary>
	/// AABBを計算。
	/// </summary>
	/// <param name="vec"></param>
	void CalcMaxMinVert(const Vector2& vec, const Vector2& spriteSize, Vector2& max, Vector2& min);

};

