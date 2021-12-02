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
	static std::map<CollisionType, int> m_collisionTypeToBitTable;	//�R���W�����^�C�v�ɉ����āA�r�b�g�e�[�u����ԋp�B

	const CollisionType m_collisionType;							//�R���W�����^�C�v
	const int m_collisibleBitTable;									//�Փˉ\�ȃr�b�g�e�[�u���B

public:
	RectCollision(CollisionType colType);

	/// <summary>
	/// ����1��AABB������2��Actor�ɓ������Ă��邩�ǂ����B
	/// </summary>
	/// <param name="actor"></param>
	/// <param name="serchActor"></param>
	/// <returns></returns>
	bool CheckHitAABB(Actor* actor, Actor* serchActor);
	bool CheckHitAABB(const Vector2& actorPos, const Vector2& actorSize, const Vector2& serchActorPos, const Vector2& sercgActorSize);

	/// <summary>
	/// �R���W�����^�C�v���擾�B
	/// </summary>
	/// <returns></returns>
	CollisionType GetCollisionType()
	{
		return m_collisionType;
	}

	/// <summary>
	/// �Փˉ\�ȃI�u�W�F�N�g���܂Ƃ߂��r�b�g�e�[�u�����擾�B
	/// </summary>
	/// <param name="ActorType"></param>
	/// <returns></returns>
	int GetCollisionPossibleTable()
	{
		return m_collisibleBitTable;
	}
	
private:
	/// <summary>
	/// AABB���v�Z�B
	/// </summary>
	/// <param name="vec"></param>
	void CalcMaxMinVert(const Vector2& vec, const Vector2& spriteSize, Vector2& max, Vector2& min);

};

