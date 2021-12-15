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
	static std::map<COLLISION_TYPE, int> m_collisionTypeToBitTable;	//�R���W�����^�C�v�ɉ����āA�r�b�g�e�[�u����ԋp�B

	const COLLISION_TYPE m_collisionType;							//�R���W�����^�C�v
	const int m_collisibleBitTable;									//�Փˉ\�ȃr�b�g�e�[�u���B
	Vector2	m_collisionSize = { SPRITE_SIZE, SPRITE_SIZE };			//�R���W�����̃T�C�Y�B

public:
	RectCollision(COLLISION_TYPE colType);
	~RectCollision();

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
	COLLISION_TYPE GetCollisionType()
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

	/// <summary>
	/// �R���W�����T�C�Y��ݒ�B
	/// </summary>
	/// <param name="size"></param>
	void SetCollisionSize(Vector2 size)
	{
		m_collisionSize = size;
	}

	/// <summary>
	/// �R���W�����T�C�Y���擾�B
	/// </summary>
	/// <returns>�R���W�����T�C�Y���擾�B</returns>
	Vector2 GetCollisionSize()
	{
		return m_collisionSize;
	}
	
private:
	/// <summary>
	/// AABB���v�Z�B
	/// </summary>
	/// <param name="vec"></param>
	void CalcMaxMinVert(const Vector2& vec, const Vector2& spriteSize, Vector2& max, Vector2& min);

};

