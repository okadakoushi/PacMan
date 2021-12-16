#pragma once

#include "Object.h"
#include "Sprite.h"
#include "RectCollision.h"

class Actor : public Object
{
public:

	enum ExcutionFlagType
	{
		EnExcutionFlagType_NotActive	= 1 << 0,	//アクティブではない。
		EnExcutionFlagType_Update		= 1 << 1,	//更新
		EnExcutionFlagType_Draw			= 1 << 2,	//描画。
		EnExcutionFlagType_Dead			= 1 << 3,	//削除。
		EnExcutionFlagType_Active		= EnExcutionFlagType_Update | EnExcutionFlagType_Draw,	//アクティブ（更新、描画)
	};

protected:
	Sprite				m_spirte;												//スプライト。
	Vector2				m_position = { SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 };	//位置。
	Vector2				m_spriteSize = { SPRITE_SIZE,SPRITE_SIZE };				//スプライトのサイズ。
	RectCollision		m_collision;											//コリジョン。
	SceneBase*			m_sceneBasePtr;											//シーンベースのPtr。
	ExcutionFlagType	m_actorExcutionFlag = EnExcutionFlagType_Active;		//アクターの実行フラグ。
	//Vector2			m_scale;												//拡大。
	//float				m_rotation = 0.0f;										//回転。

private:
	size_t				m_hash = -1;											//ハッシュ。


public:
	/// <summary>
	/// コンストラクタ。
	/// </summary>
	/// <param name="sceneBase"></param>
	/// <param name="tag"></param>
	/// <param name="prio"></param>
	Actor(SceneBase* sceneBase, std::string tag, int prio, RectCollision::CollisionType colType);
	
	/// <summary>
	/// デストラクタ。
	/// </summary>
	virtual ~Actor();

	/// <summary>
	/// 初期化。
	/// </summary>
	virtual void Init() {};

	/// <summary>
	/// 更新。
	/// </summary>
	virtual void Update() {};

	/// <summary>
	/// オンコリジョン。
	/// <para>コリジョンありActorとActorが衝突した場合に呼び出しされる。</para>
	/// <para>必要に応じて、関数をオーバーライドして衝突後の処理を実装する。</para>
	/// </summary>
	/// <param name="actor">衝突したオブジェクト。</param>
	virtual void OnCollision(Actor* actor) {};

	/// <summary>
	/// 描画。
	/// </summary>
	virtual void Draw() {};

public://Getter_Setter
	//位置取得。
	Vector2& GetPosition() 
	{
		return m_position;
	}
	
	//スプライトのサイズを取得。
	Vector2& GetSpriteSize()
	{
		return m_spriteSize;
	}

	//実行フラグを取得。
	ExcutionFlagType GetActorExcutionFlag()
	{
		return m_actorExcutionFlag;
	}

	//コリジョンを取得。
	RectCollision& GetCollision()
	{
		return m_collision;
	}

	//ハッシュを取得。
	const size_t GetHash() const 
	{
		return m_hash;
	}

	//実行フラグを設定。
	void SetExcutionFlag(ExcutionFlagType flagType)
	{
		m_actorExcutionFlag = flagType;
	}
	
	//位置を設定。
	void SetPosition(const Vector2& pos)
	{
		m_position = pos;
	}
	
	//シーンを設定。
	void SetSceneBase(SceneBase* sceneBase)
	{
		m_sceneBasePtr = sceneBase;
	}
};

