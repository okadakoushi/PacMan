#pragma once

class Object {
private:
	int			m_priority;				//�D��x�Btodo:prio�ɂ��֐��Ăяo�����Ԃ̕ύX�B
public:
	/// <summary>
	/// �������B
	/// </summary>
	/// <param name="tag">�I�u�W�F�N�g�^�O�B</param>
	/// <param name="m_prio">�D��x�B</param>
	Object(int m_prio = 0);

	virtual ~Object();

public:
	///// <summary>
	///// �^�O���擾�B
	///// </summary>
	///// <returns>�^�O�B</returns>
	//const std::string& GetTag() const 
	//{
	//	return m_objectTag;
	//}
};