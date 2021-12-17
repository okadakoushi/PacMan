#pragma once

#include "ParentChildComponent.h"

/// <summary>
/// フォントクラス。
/// </summary>
class Font : public ParentChildComponent
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

	//Vector2 GetLocalPosition()
	//{

	//}

private:
	const char* m_fontType = nullptr;
	const char* m_dispChar = "表示する文字を初期化または、設定してください。";
	int m_fontHandle = 0;
	int m_size = 10;
	int m_thickness = 5;
};

