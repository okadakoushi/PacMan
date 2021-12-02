#pragma once

class SceneGame;

/// <summary>
/// ステージローダー。
/// 1.バックグラウンド
/// 2.障害物
/// 3.アイテム
/// </summary>
class StageLoader : public Object
{
public:
	StageLoader() {};
	/// <summary>
	/// ステージデーターを初期化。
	/// </summary>
	/// <param name="stageWidth"></param>
	/// <param name="stageHeight"></param>
	/// <param name="bgfp"></param>
	/// <param name="obstaclefp"></param>
	/// <param name="itemfp"></param>
	void Init(std::vector<std::vector<int>>& outStageData, int w, int h, const char* bgfp, const char* obstaclefp, const char* itemfp);

private:
	/// <summary>
	/// stageDataをloadする。
	/// </summary>
	/// <param name="fp"></param>
	/// <param name="outStageData"></param>
	/// <param name="w"></param>
	/// <param name="h"></param>
	void LoadData(const char* fp, std::vector<std::vector<int>>& outStageData, int w, int h);
private:
};

