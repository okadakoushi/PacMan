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
public:
	StageLoader() {};
	/// <summary>
	/// �X�e�[�W�f�[�^�[���������B
	/// </summary>
	/// <param name="stageWidth"></param>
	/// <param name="stageHeight"></param>
	/// <param name="bgfp"></param>
	/// <param name="obstaclefp"></param>
	/// <param name="itemfp"></param>
	void Init(std::vector<std::vector<int>>& outStageData, int w, int h, const char* bgfp, const char* obstaclefp, const char* itemfp);

private:
	/// <summary>
	/// stageData��load����B
	/// </summary>
	/// <param name="fp"></param>
	/// <param name="outStageData"></param>
	/// <param name="w"></param>
	/// <param name="h"></param>
	void LoadData(const char* fp, std::vector<std::vector<int>>& outStageData, int w, int h);
private:
};

