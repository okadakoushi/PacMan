#pragma once
class ParentChildComponent
{
protected:
	Vector2_Int m_localPosition;
	Vector2_Int m_worldPosition;

public:
	ParentChildComponent();
	virtual ~ParentChildComponent();


	/// <summary>
	/// 追加。
	/// </summary>
	virtual void RegistChild(ParentChildComponent* child) {};

	/// <summary>
	/// 削除。
	/// </summary>
	virtual void RemoveChild(ParentChildComponent* child) {};


	/// <summary>
	/// 位置を設定。
	/// <para>親を設定している場合は、ローカル座標を引数に指定。</para>
	/// </summary>
	/// <param name="position"></param>
	void SetLocalPosition(Vector2_Int position)
	{
		m_localPosition = position;
	}

	Vector2_Int GetLocalPosition()
	{
		return m_localPosition;
	}

	Vector2_Int GetWorldPosition()
	{
		return m_worldPosition;
	}

	///// <summary>
	///// 子供を取得。
	///// </summary>
	//virtual ParentChildComponent* GetChild() {};
};

