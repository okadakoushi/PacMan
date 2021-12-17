#pragma once

/// <summary>
/// Fontクラスの親。
/// Canvasを動かすと、子のFontも動く。
/// </summary>
class Canvas
{

private:
	std::vector<Canvas*> m_children;			//子供のリスト。
	Canvas* m_parent = nullptr;					//親。
	Vector2_Int m_position;						//キャンバスの位置。
	bool m_isDraw = true;

public:
	/// <summary>
	/// 親を設定。
	/// </summary>
	/// <param name="parent">親。</param>
	void SetParent(Canvas* parent)
	{
		m_parent = parent;
	}

	/// <summary>
	/// 位置を設定。
	/// </summary>
	/// <param name="pos"></param>
	void SetPosition(Vector2_Int pos);

	/// <summary>
	/// 位置を取得。
	/// </summary>
	/// <returns></returns>
	Vector2_Int GetPosition()
	{
		return m_position;
	}

	/// <summary>
	/// 描画フラグを設定。
	/// </summary>
	/// <param name="isDraw"></param>
	void SetDrawFlag(bool isDraw)
	{
		m_isDraw = isDraw;
	}

	/// <summary>
	/// 描画するか。
	/// </summary>
	/// <returns></returns>
	bool IsDraw()
	{
		return m_isDraw;
	}



};

