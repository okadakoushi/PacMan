#pragma once
class Sprite
{
private:
	int m_drawHandle = 0;					//描画ハンドル。
	int* m_animationHandle;					//アニメーションハンドル。
	bool m_transFlag = false;				//透明度を有効にするかのフラグ。
public:
	/// <summary>
	/// 初期化。
	/// </summary>
	/// <param name="filePath">Spriteのファイルパス。Assets....</param>
	void Init(const char* filePath);
	
	/// <summary>
	/// 描画。
	/// </summary>
	/// <param name="pos">描画位置。</param>
	/// <param name="spriteSize">スプライトのサイズ。</param>
	void Draw(Vector2 pos, double scale, double Angle, int drawHandle);
	void Draw(Vector2 pos, double scale, double Angle);
	void Draw(Vector2 pos, int drawHandle);
	void Draw(Vector2 pos);
	void Draw(float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4);
	void Draw(float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4, int drawHandle);

	/// <summary>
	/// 描画用ハンドルの取得。
	/// </summary>
	/// <returns></returns>
	int GetDrawHandle()
	{
		return m_drawHandle;
	}
};

