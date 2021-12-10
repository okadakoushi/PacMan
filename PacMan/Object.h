#pragma once

class Object {
private:
	int			m_priority;				//優先度。todo:prioによる関数呼び出し順番の変更。
public:
	/// <summary>
	/// 初期化。
	/// </summary>
	/// <param name="tag">オブジェクトタグ。</param>
	/// <param name="m_prio">優先度。</param>
	Object(int m_prio = 0);

	virtual ~Object();

public:
	///// <summary>
	///// タグを取得。
	///// </summary>
	///// <returns>タグ。</returns>
	//const std::string& GetTag() const 
	//{
	//	return m_objectTag;
	//}
};