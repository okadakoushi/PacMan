#pragma once

/// <summary>
/// フォントクラス。
/// </summary>
class Font
{
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
	void Draw(const Vector2& pos);
	
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
	/// <param name="fontType"></param>
	void SetFontType(const char* fontType)
	{
		m_fontType = fontType;
	}
private:
	const char* m_fontType = "ＭＳ ゴシック";
	const char* m_dispChar = "表示する文字を初期化または、設定してください。";
	int m_fontHandle = 0;
	int m_size = 10;
	int m_thickness = 5;
};

