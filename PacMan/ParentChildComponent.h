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
	/// �ǉ��B
	/// </summary>
	virtual void RegistChild(ParentChildComponent* child) {};

	/// <summary>
	/// �폜�B
	/// </summary>
	virtual void RemoveChild(ParentChildComponent* child) {};


	/// <summary>
	/// �ʒu��ݒ�B
	/// <para>�e��ݒ肵�Ă���ꍇ�́A���[�J�����W�������Ɏw��B</para>
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
	///// �q�����擾�B
	///// </summary>
	//virtual ParentChildComponent* GetChild() {};
};

