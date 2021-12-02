#pragma once	

class Wall : public Actor
{
private:
	char m_filePath[64] = "Assets/wall_fix.png";
public:
	Wall(SceneBase* sceneBase);
	void Init() override;
	void Update() override;
	void Draw() override;
	/// <summary>
	/// ファイルパスを設定する。
	/// </summary>
	/// <param name="fp"></param>
	void SetFilePath(const char* filePath)
	{
		//コピー。
		strcpy(m_filePath, filePath);
	}
};

