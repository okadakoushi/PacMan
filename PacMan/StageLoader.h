#pragma once

class SceneGame;

/// <summary>
/// �X�e�[�W���[�_�[�B
/// 1.�o�b�N�O���E���h
/// 2.��Q��
/// 3.�A�C�e��
/// </summary>
class StageLoader : public Object
{
private:

public:
	StageLoader() {};
	~StageLoader() {};

	/// <summary>
	/// �X�e�[�W�f�[�^�[���������B
	/// </summary>
	/// <param name="stageWidth"></param>
	/// <param name="stageHeight"></param>
	/// <param name="bgFilePath"></param>
	/// <param name="obstacleFilePath"></param>
	/// <param name="itemFilePath"></param>
	void Init(std::vector<std::vector<int>>& outStageData, int w, int h, const char* bgFilePath, const char* obstacleFilePath, const char* itemFilePath);

private:
	/// <summary>
	/// stageData��load����B
	/// </summary>
	/// <param name="FilePath"></param>
	/// <param name="outStageData"></param>
	/// <param name="w"></param>
	/// <param name="h"></param>
	void LoadData(const char* FilePath, std::vector<std::vector<int>>& outStageData, int w, int h);
};

