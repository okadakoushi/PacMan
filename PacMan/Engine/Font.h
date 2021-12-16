#pragma once

/// <summary>
/// フォントクラス。
/// </summary>
class Font
{
public:
	Font();
	virtual ~Font();

public:
	/// <summary>
	/// 初期化。
	/// </summary>
	/// <param name="dispStr">表示する文字列。</param>
	/// <param name="size">表示する文字のサイズ。</param>
	/// <param name="thickness">表示する文字の太さ。</param>
	void Init(const char* dispStr, int size, int thickness);
	
	/// <summary>
	/// 描画。
	/// </summary>
	/// <param name="pos">描画する位置。</param>
	void Draw(unsigned int color = GetColor(255,255,255));
	
	/// <summary>
	/// 表示する文字を設定。
	/// </summary>
	/// <param name="dispChar">表示する文字。</param>
	void SetDispStr(const char* dispChar)
	{
		m_dispChar = dispChar;
	}
	
	/// <summary>
	/// フォントタイプを設定。
	/// </summary>
	/// <param name="fontType">フォントのファイルパス or システムフォントの名前。</param>
	void SetFontType(const char* fontType)
	{
		m_fontType = fontType;
		m_fontHandle = LoadFontDataToHandle(fontType);
	}

	/// <summary>
	/// 位置を設定。
	/// <para>親を設定している場合は、ローカル座標を引数に指定。</para>
	/// </summary>
	/// <param name="position"></param>
	void SetPosition(Vector2_Int position)
	{
		m_position = position;
	}

	/// <summary>
	/// 位置を取得。
	/// </summary>
	/// <returns>ワールド座標を返却。</returns>
	Vector2_Int GetPosition()
	{
		if (m_parent != nullptr)
		{
			//ワールド座標を計算する。
			return m_position + m_parent->GetPosition();
		}
		else
		{
			return m_position;
		}
	}

	//Vector2 GetLocalPosition()
	//{

	//}

	/// <summary>
	/// 親を設定。
	/// </summary>
	/// <param name="parent"></param>
	void SetParent(Font& parent)
	{
		m_parent = &parent;
	}

	/// <summary>
	/// 親を解除。
	/// </summary>
	void RemoveParent()
	{
		m_parent = nullptr;
	}

private:
	Vector2_Int m_position;
	const char* m_fontType = nullptr;
	const char* m_dispChar = "表示する文字を初期化または、設定してください。";
	int m_fontHandle = 0;
	int m_size = 10;
	int m_thickness = 5;
	Font* m_parent = nullptr;
};

