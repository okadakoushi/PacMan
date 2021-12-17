#pragma once

/// <summary>
/// Font�N���X�̐e�B
/// Canvas�𓮂����ƁA�q��Font�������B
/// </summary>
class Canvas
{

private:
	std::vector<Canvas*> m_children;			//�q���̃��X�g�B
	Canvas* m_parent = nullptr;					//�e�B
	Vector2_Int m_position;						//�L�����o�X�̈ʒu�B
	bool m_isDraw = true;

public:
	/// <summary>
	/// �e��ݒ�B
	/// </summary>
	/// <param name="parent">�e�B</param>
	void SetParent(Canvas* parent)
	{
		m_parent = parent;
	}

	/// <summary>
	/// �ʒu��ݒ�B
	/// </summary>
	/// <param name="pos"></param>
	void SetPosition(Vector2_Int pos);

	/// <summary>
	/// �ʒu���擾�B
	/// </summary>
	/// <returns></returns>
	Vector2_Int GetPosition()
	{
		return m_position;
	}

	/// <summary>
	/// �`��t���O��ݒ�B
	/// </summary>
	/// <param name="isDraw"></param>
	void SetDrawFlag(bool isDraw)
	{
		m_isDraw = isDraw;
	}

	/// <summary>
	/// �`�悷�邩�B
	/// </summary>
	/// <returns></returns>
	bool IsDraw()
	{
		return m_isDraw;
	}



};

