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
private:

public:
	StageLoader() {};
	~StageLoader() {};

	/// <summary>
	/// ステージデーターを初期化。
	/// </summary>
	/// <param name="stageWidth"></param>
	/// <param name="stageHeight"></param>
	/// <param name="bgFilePath"></param>
	/// <param name="obstacleFilePath"></param>
	/// <param name="itemFilePath"></param>
	void Init(std::vector<std::vector<int>>& outStageData, int w, int h, const char* bgFilePath, const char* obstacleFilePath, const char* itemFilePath);

private:
	/// <summary>
	/// stageDataをloadする。
	/// </summary>
	/// <param name="FilePath"></param>
	/// <param name="outStageData"></param>
	/// <param name="w"></param>
	/// <param name="h"></param>
	void LoadData(const char* FilePath, std::vector<std::vector<int>>& outStageData, int w, int h);
};

